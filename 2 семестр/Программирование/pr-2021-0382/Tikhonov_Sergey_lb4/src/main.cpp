#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class CustomStack {
public:
    explicit CustomStack(int initialSize = 10) {               
        size_d = 0;
        size_max = initialSize;
        mData = new char* [size_max];
    };

    ~CustomStack() {                                           
        for (size_t i = 0; i < size_d; i++) {
            delete [] mData[i];
        }
        delete [] mData;
    }

    void push(const char* val) {
        if (size_d >= size_max) {
            extend(size_plus);
        }
        mData[size_d] = new char;
        strcpy(mData[size_d], val);
        size_d++;
    }

    void pop() {
        if (size_d == 0) {
            return;
        }
        delete [] mData[size_d-1];
        size_d--;
    }

    char* top() {
        if (empty()) {
            return nullptr;
        }
        return mData[size_d-1];
    }

    size_t size() {
        return size_d;
    }

    bool empty() {
        return (size_d == 0);
    }

    void extend(int n) {
        size_max += n;
        mData = new char* [size_max];
    }

private:
    size_t size_d;
    size_t size_max;

protected:
    const size_t size_plus = 20;
    char** mData;
};

int main() {
    CustomStack stack(100);
    char* elem = new char [100];
    size_t index = 0;
    bool flag = false;
    char c = cin.get();

    while (c != '\n') {
        if (c == '<') {
            flag = true;
        }
        else if (c == '>') {
            elem[index] = '\0';
            flag = false;
            index = 0;
            if (strcmp(elem, "br") != 0 && strcmp(elem, "hr") != 0) {
                if (!stack.empty() && strcmp(elem+1, stack.top()) == 0) {
                    stack.pop();
                }
                else {
                    stack.push(elem);
                }
            }
        }
        else if (flag) {
            elem[index++] = c;
        }
        c = cin.get();
    }

    if (stack.empty()) {
        cout << "correct" << endl;
    }
    else {
        cout << "wrong" << endl;
    }
    return 0;
}
