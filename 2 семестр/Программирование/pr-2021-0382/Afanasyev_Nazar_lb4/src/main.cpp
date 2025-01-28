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
    char op, ch;
    CustomStack stack;
    for(int i = 0; i < 100; i++){
        op = getc(stdin);
        ch = getc(stdin);
        if(isdigit(op) || (op == '-' && isdigit(ch))){
            cin.putback(ch);
            cin.putback(op);
            cin >> num;
            stack.push(num);
        }
        else if((op == '+' || op == '-' || op == '*' || op == '/') && isspace(ch)){
            cin.putback(ch);
            int a = stack.top(), b = (stack.pop(), stack.top());
            stack.pop();
            switch(op){
                case '+':
                    stack.push(a+b);
                    break;
                case '-':
                    stack.push(b-a);
                    break;
                case '*':
                    stack.push(a*b);
                    break;
                case '/':
                    if(a == 0){cout << "error" << endl; exit(0);}
                    stack.push(b/a);
                    break;
            }
        }
        else cout << "error" << endl;
        if(getc(stdin) == '\n') break;
        else if((op = getc(stdin)) == '\n') break;
        else cin.putback(op);
    }

    if(stack.size() == 1) cout << stack.top() << endl;
    else cout << "error" << endl;;

    return 0;
}