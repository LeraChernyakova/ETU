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

    void push(int val) {
        auto *node = new ListNode;
        node->mNext = mHead;
        node->mData = val;
        mHead = node;
    }

    void pop() {
        if (this->empty()) {
            cout << "error" << endl;
            exit(0);
        }
        auto tmp = mHead;
        mHead = mHead->mNext;
        delete tmp;
    }

    int top() {
        if (this->empty()) {
            cout << "error"<< endl;
            exit(0);
        }
        return mHead->mData;
    }

    size_t size() {
        size_t size = 0;
        ListNode *cur = mHead;
        while (cur != nullptr) {
            size += 1;
            cur = cur->mNext;
        }
        return size;
    }

    bool empty() {
        if (mHead == nullptr) return true;
        else return false;
    }

protected:
    ListNode *mHead;
};

int main() {
    char c;
    string num;
    cin >> noskipws >> c;
    CustomStack stack;
    while (c != '\n') {
        if (c == '-') {
            cin >> noskipws >> c;
            if (isdigit(c)) {
                num += '-';
                while (isdigit(c)) {
                    num += c;
                    cin >> noskipws >> c;
                }
                stack.push(stoi(num));
                num = "";
            } else {
                int right = stack.top();
                stack.pop();
                int left = stack.top();
                stack.pop();
                stack.push(left - right);
            }
        } else if (isdigit(c)) {
            while (isdigit(c)) {
                num += c;
                cin >> noskipws >> c;
            }
            stack.push(stoi(num));
            num = "";
        } else {
            if (c == '+') {
                int right = stack.top();
                stack.pop();
                int left = stack.top();
                stack.pop();
                stack.push(left + right);
            }
            if (c == '*') {
                int right = stack.top();
                stack.pop();
                int left = stack.top();
                stack.pop();
                stack.push(left * right);
            }
            if (c == '/') {
                int right = stack.top();
                if (right == 0) {cout << "error" << endl; exit(0);}
                stack.pop();
                int left = stack.top();
                stack.pop();
                stack.push(left / right);
            }
            cin >> noskipws >> c;
        }
    }
    if (stack.size() > 1) cout << "error" << endl;
    else cout << stack.top();
}
