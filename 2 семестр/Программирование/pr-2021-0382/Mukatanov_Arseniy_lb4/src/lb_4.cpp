#include <cstring>
#include <iostream>

using namespace std;

class CustomStack {

public:
    CustomStack() {
        mData = new int[max_size];
    }

    ~CustomStack() {
        delete[] mData;
    }

    void extend(int n) {
        max_size += n;
        int *new_Data = new int[max_size];
        memcpy(new_Data, mData, d_size * sizeof(int));
        delete[] mData;
        mData = new_Data;
    }

    void push(int a) {
        if (d_size + 1 >= max_size) {
            extend(10);
        }
        mData[d_size] = a;
        d_size++;
    }

    int pop() {
        if (isempty()) {
            throw "error";
        }
        d_size--;
        return mData[d_size];
    }

    bool isempty() {
        if (d_size == 0) {
            return  true;
        }
        else {
            return false;
        }
    }

    int top() {
        if (isempty()) {
            throw "error";
        }
        return mData[d_size-1];
    }

    int size() {
        return d_size;
    }


private:
    int d_size = 0;
    int max_size = 100;

protected:
    int* mData;
};


bool try_stoi(const string &s, int &i){
    try {
        i = stoi(s);
        return true;
    }
    catch (const invalid_argument&) {
        return false;
    }
}


int main() {
    CustomStack my_stack;
    string tok ;
    int value;
    int left_num , right_num;

    while (cin >> tok) {
        if (try_stoi(tok,value)) {
            my_stack.push(value);
        } else {
            try{
                right_num = my_stack.pop();
                left_num = my_stack.pop();
            }
            catch(const char* error_str) {
                cout << error_str;
                return 0;
            }

            if (tok == "+") {
                my_stack.push(left_num + right_num);
            }
            if (tok == "-") {
                my_stack.push(left_num - right_num);
            }
            if (tok == "*") {
                my_stack.push(left_num * right_num);
            }

            if (tok == "/") {
                my_stack.push(left_num / right_num);
            }
        }
    }

    if (my_stack.size() != 1) {
        cout << "error";
        return 0;

    } else {
        cout << my_stack.pop();
        return 0;
    }

}