class CustomStack{
    public:
        ~CustomStack(){
            while (mHead){
                pop();
            }
        }
        void appear_error(){
            printf("error\n");
            delete this;
            exit(0);
        }
        void check(){
            if (empty()){
                appear_error();
            }
        }
        void push(int val){
            ListNode* newe = new ListNode{mHead, val};
            mHead = newe;
        }
        void pop(){
            check();
            ListNode* t = mHead;
            mHead = mHead->mNext;
            delete t;
        }
        int top(){
            check();
            return mHead->mData;
        }
        size_t size(){
            ListNode* actual = mHead;
            size_t n;
            for (n = 0; actual; n++){
                actual = actual->mNext;
            }
            return n;
        }
        bool empty(){
            return !((bool)mHead);
        }
        int check_number(char* s){
            int l = strlen(s);
            if (l == 1 && !isdigit(s[0])){
                    return 0;
            }
            return 1;
        }
        protected:
            ListNode* mHead;
};

int main(){
    CustomStack* stack = new CustomStack();
    char actual[100];
    int f, s;
    scanf("%s", actual);
    while (!feof(stdin)){
        if (stack->check_number(actual)){
            stack->push(atoi(actual));
        }
        else {
            f = stack->top();
            stack->pop();
            s = stack->top();
            stack->pop();
            if (!strcmp(actual, "+")){
                    stack->push(f + s);
            }
            else if (!strcmp(actual, "-")){
                    stack->push(s - f);
            }
            else if (!strcmp(actual, "*")){
                    stack->push(f * s);
            }
            else if (!strcmp(actual, "/")){
                    stack->push(s / f);}
        }
        scanf("%s", actual);
    }
    if (stack->size() != 1){
        stack->appear_error();
    }
    f = stack->top();
    printf("%d\n", f);
    return 0;
}
