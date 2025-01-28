#include <iostream>
#include <sstream>
#include <cstring>

struct ListNode {
    ListNode *mNext;
    int mData;
};

class CustomStack {

public:
    CustomStack() {
        mHead = static_cast<ListNode *>(malloc(sizeof(ListNode)));
        lastNode = NULL;
        mHead = NULL;
    }

    ~CustomStack() {
        ListNode *current = mHead;
        while (current != NULL) {
            mHead = mHead->mNext;
            free(current);
            current = mHead->mNext;


        }
    }

    void push(int num) {
        if (mHead == NULL) {
            mHead = static_cast<ListNode *>(malloc(sizeof(ListNode)));
            mHead->mData = num;
            mHead->mNext = NULL;
            lastNode = mHead;
            return;
        }
        lastNode->mNext = static_cast<ListNode *>(malloc(sizeof(ListNode)));
        lastNode = lastNode->mNext;
        lastNode->mNext = NULL;
        lastNode->mData = num;
    }


    void pop() {
        if (mHead == NULL) {
            std::cout << "error" << std::endl;
            exit(0);
        }
        if (mHead->mNext == NULL) {
            std::cout << mHead->mData << std::endl;
            free(mHead);
            mHead = NULL;

            return;
        }
        ListNode *current = mHead;
        while (current->mNext->mNext != NULL) {
            current = current->mNext;
        }
        std::cout << current->mNext->mData << std::endl;
        free(current->mNext);
        lastNode = current;
        current->mNext = NULL;
    }

    int top() {
        if (mHead == NULL) {
            std::cout << "error" << std::endl;
            exit(0);
        }

        return lastNode->mData;
    }

    size_t size() {
        ListNode *current = mHead;
        size_t size = 0;
        while (current != NULL) {
            size++;
            current = current->mNext;
        }
        return size;
    }


    bool empty() {
        return mHead == NULL;
    }


private:
    ListNode *lastNode;


protected:
    ListNode *mHead;
};

int main() {
    CustomStack Stack;
    const int input_length = 10;
    char commands[5][input_length] = {"cmd_push", "cmd_pop", "cmd_top", "cmd_size", "cmd_exit"};
    int option;
    char what_to_push[20];
    char input[input_length];
    while (true) {
        std::cin >> input;
        if (!strcmp(input, commands[0])) {
            std::cin >> what_to_push;
            option = 1;
        }
        for (int j = 1; j < 5; j++) {
            if (!strcmp(input, commands[j])) {
                option = j + 1;
            }
        }
        switch (option) {
            case 1:
                Stack.push(atoi(what_to_push));
                std::cout << "ok\n";
                break;
            case 2:
                Stack.pop();
                break;
            case 3:
                std::cout << Stack.top() << std::endl;
                break;
            case 4:
                std::cout << Stack.size() << std::endl;
                break;
            case 5:
                std::cout << "bye\n";
                exit(0);
            default:
                std::cout << "non-existent command\n";
        }
        option = 0;
    }
    return 0;
}