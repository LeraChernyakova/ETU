#include <cstring>
#include <iostream>

using namespace std;

class CustomStack {
    public:
        CustomStack() {
            mData = new int[mAvailable];
        }
        ~CustomStack() {
            delete[] mData;
        }
        void extend(int n) {
            mAvailable += n;
            int *new_Data = new int[mAvailable];
            memcpy(new_Data, mData, mSize * sizeof(int));
            delete[] mData;
            mData = new_Data;
        }
        void push(int a) {
            if (mSize + 1 >= mAvailable) {
                extend(10);
            }
            mData[mSize] = a;
            mSize++;
        }
        int pop() {
            if (empty()) {
                throw "error";
            }
            mSize--;
            return mData[mSize];
        }
        bool empty() {
            if (mSize == 0) {
                return  true;
            }
            else {
                return false;
            }
        }
        int top() {
            if (empty()) {
                throw "error";
            }
            return mData[mSize - 1];
        }
        int size() {
            return mSize;
        }

    private:
        int mSize = 0;
        int mAvailable = 100;

    protected:
        int* mData;
};

bool tryStoi(const string &s, int &i){
    try {
        i = stoi(s);
        return true;
    }
    catch (const std::invalid_argument&) {
        return false;
    }
}

int main() {
    CustomStack myStack;
    string tok ;
    int value;
    int leftNum , rightNum;
    while (cin >> tok) {
        if (tryStoi(tok, value)) {
            myStack.push(value);
        } else {
            try{
                rightNum = myStack.pop();
                leftNum = myStack.pop();
            }
            catch(const char* error_str) {
                cout << error_str;
                return 0;
            }
            if (tok == "+")
                myStack.push(leftNum + rightNum);
            if (tok == "-")
                myStack.push(leftNum - rightNum);
            if (tok == "*")
                myStack.push(leftNum * rightNum);
            if (tok == "/")
                myStack.push(leftNum / rightNum);
        }
    }
    if (myStack.size() != 1) {
        cout << "error";
        return 0;
    } else {
        cout << myStack.pop();
        return 0;
    }
}

