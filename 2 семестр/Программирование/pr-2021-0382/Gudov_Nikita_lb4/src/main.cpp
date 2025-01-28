#include <iostream>
#include <cstring>

using namespace std;

class CustomStack {
public:
    CustomStack(){
        ssize = 0;
        mData = new int[0];
    }

    ~CustomStack(){
        delete[] mData;
    }

    void push(int val){
        extend(1);
        mData[ssize] = val;
        ssize++;
    }

    void pop(){
        cout << mData[ssize - 1] << endl;
        mData[ssize - 1] = 0;
        ssize--;
    }

    int top(){
        return mData[ssize - 1];
    }

    size_t size(){
        return ssize;
    }

    bool empty(){
        if(ssize == 0)
            return true;
        else
            return false;
    }

    
    void extend(int n){
        mData = (int*) realloc(mData, n * sizeof(int));
    }

private:
    int ssize;


protected:
    int* mData;
};

int main(){
    CustomStack stack;
    char com[20];
    while (true){
        cin >> com;
        if (strcmp(com,"cmd_push")==0){
            int val;
            cin >> val;
            stack.push(val);
            cout << "ok" << endl;
            continue;
        }
        if (strcmp(com,"cmd_pop")==0){
            if(stack.empty() == 1){
                cout << "error";
                exit(0);
            }
            stack.pop();
            continue;
        }
        if (strcmp(com,"cmd_top")==0){
            if(stack.empty() == 1){
                cout << "error";
                exit(0);
            }
            cout << stack.top() << endl;
            continue;
        }
        if (strcmp(com,"cmd_size")==0){
            cout << stack.size() << endl;
            continue;
        }
        if (strcmp(com,"cmd_exit")==0){
            cout << "bye" << endl;
            exit(0);
        }
    }
    return 0;
}