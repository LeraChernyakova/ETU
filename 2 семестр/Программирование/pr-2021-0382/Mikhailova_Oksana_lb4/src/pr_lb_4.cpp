#include <iostream>
#include <cstring>
using namespace std;

class CustomStack {
public:
    CustomStack(){
        mDataSize = 0;
        mDataMaxSize = 10;
        mData = (char**)malloc(mDataMaxSize*sizeof(char *));
    };

    ~CustomStack(){
        for (size_t i=0; i<mDataSize; i++){
            free(mData[i]);
        }
        free(mData);
    }

    void push(const char* val){
        if (mDataSize >= mDataMaxSize){
            extend(mDataMaxSize);
        }
        mData[mDataSize] = (char*)malloc(strlen(val)*sizeof(char));
        strcpy(mData[mDataSize], val);
        mDataSize++;
    }

    void pop(){
        if (empty()){
            return;
        }
        free(mData[mDataSize-1]);
        mDataSize--;
    }

    char* top(){
        if (empty()){
            return nullptr;
        }
        return mData[mDataSize-1];
    }

    size_t size(){
        return mDataSize;
    }

    bool empty(){
        return (mDataSize == 0);
    }

    void extend(int n){
        mDataMaxSize += n;
        mData = (char**)realloc(mData, mDataMaxSize*sizeof(char*));
    }

private:
    size_t mDataSize;
    int mDataMaxSize;

protected:
    char** mData;
};

int main() {
    CustomStack stack;
    char* tag = (char*)malloc(100*sizeof(char));
    size_t index = 0;
    size_t flag = 0;
    char c = cin.get();
    while(c != '\n'){
        if (c == '<') {
            flag = 1;
        }
        else if(c == '>') {
            tag[index] = '\0';
            index = 0;
            flag = 0;

            if (strcmp(tag, "br")!=0 && strcmp(tag, "hr")!=0){
                if (!stack.empty() && strcmp(tag+1, stack.top())==0){
                    stack.pop();
                }
                else{
                    stack.push(tag);
                }
            }
        }
        else if(flag){
            tag[index++] = c;
        }
        c = cin.get();
    }

    if (stack.empty()){
        cout << "correct" << endl;
    } else {
        cout << "wrong" << endl;
    }
    return 0;
}
