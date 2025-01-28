#include <cstring>
#include <iostream>

using namespace std;

class CustomStack {

public:
    CustomStack() {
        mData = new int[ch_max_size];
    }

    void extend(int n) {
        ch_max_size += n;
        int *new_Data = new int[ch_max_size];
        memcpy(new_Data, mData, ch_size * sizeof(int));
        delete[] mData;
        mData = new_Data;
    }

    void push(int a) {
        if (ch_size + 1 >= ch_max_size) {
            extend(10);
        }
        mData[ch_size] = a;
        ch_size++;
    }

    int pop() {
        if (empty()) {
            throw "error";
        }
        ch_size--;
        return mData[ch_size];
    }

    bool empty() {
        if (ch_size == 0) {
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
        return mData[ch_size-1];
    }

    int size() {
        return ch_size;
    }

    ~CustomStack() {
        delete[] mData;
    }

private:
    int ch_size = 0;
    int ch_max_size = 100;

protected:
    int* mData;
};


bool try_stoi(const string &s, int &i){
    try {
        i = stoi(s);
        return true;
    }
    catch (const std::invalid_argument&) {
        return false;
    }
}


int main() {
    CustomStack stack;
    string token ;
    int value;
    int left_num , right_num;

    while (cin >> token) {
        if (try_stoi(token,value)) {
            stack.push(value);
        } else {
            try{
                right_num = stack.pop();
                left_num = stack.pop();
            }
            catch(const char* error_str) {
                cout << error_str;
                return 0;
            }

            if (token == "+") {
                stack.push(left_num + right_num);
            }
            if (token == "-") {
                stack.push(left_num - right_num);
            }
            if (token == "*") {
                stack.push(left_num * right_num);
            }

            if (token == "/") {
                stack.push(left_num / right_num);
            }

        }

    }

    if (stack.size() != 1) {
        cout << "error";
        return 0;

    } else {
        cout << stack.pop();
        return 0;
    }

}
