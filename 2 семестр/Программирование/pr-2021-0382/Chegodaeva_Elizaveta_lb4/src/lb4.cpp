#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>

typedef struct ListNode {
    ListNode *mNext;
    int mData;
} ListNode;

using namespace std;

class CustomStack {
    public:
        CustomStack(){
            mHead = nullptr;
        }
    
        void push(int val){
            ListNode* elem = new ListNode{mHead, val};
            mHead = elem;
        }
        
        void check(){
                if(empty()){
                cout << "error" << endl;
                exit(0);
            }
        }
    
        void pop(){
            check();
            ListNode* temp = mHead;
            mHead = mHead->mNext;
            delete temp;
        }
    
        int top(){
            check();
            return mHead->mData;
        }
    
        size_t size(){
            ListNode* val = mHead;
            size_t size = 0;
            while (val!=nullptr){
                val = val->mNext;
                size=size+1;
            }
            return size;
        }
    
        bool empty(){
            if (mHead==nullptr){
                return true;
            }
            else{
                return false;
            }
        }
    
    protected:
        ListNode *mHead;
};

int main() {
    CustomStack* stack = new CustomStack();
    char val;
    int first;
    int next;
    string m;
    val=cin.get();
    while (val!='\n') {
        if (val=='-'){
            val=cin.get();
            if (isdigit(val)){
                m=m+'-';
            }
            else{
                first = stack->top();
                stack->pop();
                next = stack->top();
                stack->pop();
                stack->push(next-first);
            }

        }
        else if (isdigit(val)){
            while(isdigit(val)){
                m=m+val;
                val=cin.get();
            }
            stack->push(stoi(m));
            m="";
        }
        else {
            if (val== '+'){
                next = stack->top();
                stack->pop();
                first = stack->top();
                stack->pop();
                stack->push(first+next);
            }
            if (val=='*'){
                next = stack->top();
                stack->pop();
                first = stack->top();
                stack->pop();
                stack->push(first*next);
            }
            if (val=='/'){
                next = stack->top();
                stack->pop();
                first = stack->top();
                stack->pop();
                if (next== 0) {
                    cout << "error" << endl;
                    exit(0);
                }
                stack->push(first/next);
            }
            val=cin.get();
        }
    }
    if(stack->size()>1){
        cout << "error" << endl;
        exit(0);
    }
    cout << stack->top();
    return 0;
}

