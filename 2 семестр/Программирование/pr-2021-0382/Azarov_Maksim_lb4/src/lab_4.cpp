#include <cstring>
#include <iostream>

using namespace std;

class CustomStack {

public:
    CustomStack() {
        mData = new int[m_max_size];
    }

    ~CustomStack() {
        delete[] mData;
    }

    void extend(int n) {
        m_max_size += n;
        int *new_Data = new int[m_max_size];
        memcpy(new_Data, mData, m_size * sizeof(int));
        delete[] mData;
        mData = new_Data;
    }

    void push(int a) {
        if (m_size + 1 >= m_max_size) {
            extend(10);
        }
        mData[m_size] = a;
        m_size++;
    }

    int pop() {
        if (empty()) {
            throw "error";
        }
        m_size--;
        return mData[m_size];
    }

    bool empty() {
        if (m_size == 0) {
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
        return mData[m_size-1];
    }

    int size() {
        return m_size;
    }


private:
    int m_size = 0;
    int m_max_size = 100;

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
    CustomStack my_stack;
    string token ;
    int value;
    int left_num , right_num;
    //cin >> token;//считывает до пробела

    while (cin >> token) {
        if (try_stoi(token,value)) {
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

            if (token == "+") {
                my_stack.push(left_num + right_num);
            }
            if (token == "-") {
                my_stack.push(left_num - right_num);
            }
            if (token == "*") {
                my_stack.push(left_num * right_num);
            }

            if (token == "/") {
                my_stack.push(left_num / right_num);
            }


        }


        //cin >> token;
    }

    if (my_stack.size() != 1) {
        cout << "error";
        return 0;

    } else {
        cout << my_stack.pop();
        return 0;
    }

}

