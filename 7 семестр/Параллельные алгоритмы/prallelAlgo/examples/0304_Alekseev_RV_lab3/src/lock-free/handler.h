#ifndef HANDLER_H
#define HANDLER_H

#include <vector>
#include <mutex>
#include <atomic>
#include <unordered_set>

template <typename T>
class Handler {
private:
	// Узел
	struct Node {
		T data;
		std::atomic<Node*> next;
	};

	struct ThreadInfo {
		std::atomic<Node*> hp1;
		std::atomic<Node*> hp2;
		std::vector<Node*> dlist;
		int dcount = 0;
	};

	std::atomic<Node*> head;
	std::atomic<Node*> tail;

	std::vector<ThreadInfo> threadsInfo;

	void deleteRecursive(Node* elem) {
		if(elem != nullptr) {
			deleteRecursive(elem->next);
			delete elem;
		}
	}

	void retire(int threadNum, Node* ptrToDelete) {
		ThreadInfo& curTI = threadsInfo[threadNum];
		curTI.dlist[curTI.dcount++] = ptrToDelete;

		if(curTI.dcount == curTI.dlist.size()) {
			scan(threadNum);
		}
	}

	void scan(int threadNum) {
		std::unordered_set<Node*> hps;

		for(const auto& info : threadsInfo) {
			hps.insert(info.hp1);
			hps.insert(info.hp2);
		}

		int newDcount = 0;
		auto& myDlist = threadsInfo[threadNum].dlist;

		for(int i = 0; i < myDlist.size(); i++) {
			if(hps.count(myDlist[i])) {
				Node* ptr = myDlist[i];
				myDlist[i] = nullptr;
				myDlist[newDcount++] = ptr;
			} else {
				delete myDlist[i];
				myDlist[i] = nullptr;
			}
		}
		threadsInfo[threadNum].dcount = newDcount;
	}

public:
	Handler(int threadCount): threadsInfo(threadCount) {
		Node *dummy = new Node;
		head = dummy;
		tail = dummy;

		for(ThreadInfo& ti : threadsInfo) {
			ti.dlist.resize(4 * threadCount);
		}
	}

	~Handler(){
		for(const auto& info : threadsInfo) {
			for(Node* ptr : info.dlist) {
				delete ptr;
			}
		}

		deleteRecursive(head);
	}

	void push(const T& data, int threadNum) {
		Node* newTail = new Node{data};

		while(true) {
			Node* tmp = nullptr;
			Node* tail_ = tail.load();
			threadsInfo[threadNum].hp1.store(tail_);

			if(tail_ != tail.load())
				continue;

			if(tail_->next.compare_exchange_strong(tmp, newTail)) {
				tail.compare_exchange_strong(tail_, newTail);
				break;
			}

			tail.compare_exchange_strong(tail_, tail_->next.load());
		}
		threadsInfo[threadNum].hp1.store(nullptr);
	}

	bool pop(T& data, int threadNum) {
		while(true) {
			Node* head_ = head.load();
			threadsInfo[threadNum].hp1.store(head_);

			if(head_ != head.load())
				continue;

			Node* tail_ = tail.load();
			Node* nextHead = head_->next.load();
			threadsInfo[threadNum].hp2.store(nextHead);

			if(nextHead != head_->next.load())
				continue;

			// Очередь пуста
			if(nextHead == nullptr) {
				threadsInfo[threadNum].hp1.store(nullptr);
				return false;
			}

			if(head_ == tail_) {
				tail.compare_exchange_strong(tail_, nextHead);
			} else {
				if(head.compare_exchange_strong(head_, nextHead)) {
					data = nextHead->data;
					threadsInfo[threadNum].hp1.store(nullptr);
					threadsInfo[threadNum].hp2.store(nullptr);
					retire(threadNum, head_);

					break;
				}
			}
		}

		return true;
	}
};

#endif