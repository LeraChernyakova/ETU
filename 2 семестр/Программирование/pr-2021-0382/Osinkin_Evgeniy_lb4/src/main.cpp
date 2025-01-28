#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;

typedef struct ListNode {
	ListNode *mNext;
	int mData;
} ListNode;

class CustomStack {

public:

	CustomStack() {
		mHead = nullptr;
	}

	void push(int value) {
		auto *node = new ListNode;
		node->mNext = mHead;
		node->mData = value;
		mHead = node;
	}

	void pop() {
		if (this->empty()) {
			cout << "error" << endl;
			exit(-1);
		}
		auto tmp = mHead;
		mHead = mHead->mNext;
		delete tmp;
	}

	int top() {
		if (this->empty()) {
			cout << "error" << endl;
			exit(-1);
		}
		return mHead->mData;
	}

	size_t size() {
		size_t size = 0;
		ListNode *curr = mHead;
		while (curr != nullptr) {
			size += 1;
			curr = curr->mNext;
		}
		return size;
	}

	bool empty() {
		if (mHead == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

protected:
	ListNode *mHead;
};

int main() {

	char chr;
	string number;
	cin >> noskipws >> chr;
	CustomStack stack;
	while (chr != '\n') {
		if (chr == '-') {
			cin >> noskipws >> chr;
			if (isdigit(chr)) {
				number = number + '-';
				while (isdigit(chr)) {
					number = number + chr;
					cin >> noskipws >> chr;
				}
				stack.push(stoi(number));
				number = "";
			}
			else {
				int right = stack.top();
				stack.pop();
				int left = stack.top();
				stack.pop();
				stack.push(left - right);
			}
		}
		else if (isdigit(chr)) {
			while (isdigit(chr)) {
				number = number + chr;
				cin >> noskipws >> chr;
			}
			stack.push(stoi(number));
			number = "";
		}
		else {
			if (chr == '+') {
				int right = stack.top();
				stack.pop();
				int left = stack.top();
				stack.pop();
				stack.push(left + right);
			}
			if (chr == '*') {
				int right = stack.top();
				stack.pop();
				int left = stack.top();
				stack.pop();
				stack.push(left * right);
			}
			if (chr == '/') {
				int right = stack.top();
				if (right == 0) { 
					cout << "error" << endl; 
					exit(-1); 
				}
				stack.pop();
				int left = stack.top();
				stack.pop();
				stack.push(left / right);
			}
			cin >> noskipws >> chr;
		}
	}
	if (stack.size() > 1) {
		cout << "error" << endl;
	}
	else {
		cout << stack.top();
	}

}