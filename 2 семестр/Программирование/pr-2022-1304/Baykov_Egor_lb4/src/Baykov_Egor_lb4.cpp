#include <iostream>
using namespace std;

struct ListNode {
    ListNode* mNext;
    int mData;
};

class CustomStack{
    public:
        void push(int val){
            struct ListNode* node = new ListNode();
            node->mNext = mHead;
            node->mData = val;
            mHead = node;
            mSize++;
        };
        void pop(){ 
            ListNode* p = mHead->mNext;
            delete(mHead);
            if(mSize < 1){
                cout << "error";
                exit(0);
            }
            else if(mSize == 1) mHead = NULL;
            else mHead = p;
            mSize--;
        };
        int top(){
            if(mSize < 1){
                cout << "error";
                exit(0);
            }
            return mHead->mData;
        };
        size_t size() { return mSize; };
        bool empty() { return !mSize; };
        CustomStack() { return; };
        ~CustomStack(){  delete(mHead); };
    protected:
        ListNode* mHead = NULL;
        size_t mSize = 0;
};

int main(){
    int num;
    char operation, ch;
    CustomStack stack;
    for(int i = 0; i < 100; i++){
        operation = getc(stdin);
        ch = getc(stdin);
        if(isdigit(operation) || (operation == '-' && isdigit(ch))){
            cin.putback(ch);
            cin.putback(operation);
            cin >> num;
            stack.push(num);
        }
        else if((operation == '+' || operation == '-' || operation == '*' || operation == '/') && isspace(ch)){
            cin.putback(ch);
            int second = stack.top(), first = (stack.pop(), stack.top());
            stack.pop();
            switch(operation){
                case '+':
                    stack.push(second+first);
                    break;
                case '-':
                    stack.push(first-second);
                    break;
                case '*':
                    stack.push(second*first);
                    break;
                case '/':
                    if(second == 0){cout << "error" << endl; exit(0);}
                    stack.push(first/second);
                    break;
            }
        }
        else cout << "error" << endl;
        if(getc(stdin) == '\n') break;
        else if((operation = getc(stdin)) == '\n') break;
        else cin.putback(operation);
    }

    if(stack.size() == 1) cout << stack.top() << endl;
    else cout << "error" << endl;;

    return 0;
}