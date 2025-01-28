class CustomStack{
        public:
            CustomStack(){
              mHead = nullptr;
            }

            void push(const char* tag){
                struct ListNode* new_el = new struct ListNode;
                new_el -> mData = new char[strlen(tag)];
                strcpy(new_el -> mData,tag);
                new_el -> mNext = mHead;
                mHead = new_el;
            }

            void pop(){
                if(size() == 0){
                    cout << "wrong" << endl;
                    exit(0);
                }

                struct ListNode* tmp = mHead;
                delete mHead -> mData;
                mHead = mHead -> mNext;
                delete tmp;
            }

            char* top(){
                if(size() == 0){
                    cout << "wrong" << endl;
                    exit(0);
                }
                return mHead -> mData;
            }

            size_t size(){
                size_t size = 0;
                struct ListNode* end = mHead;
                while(end != nullptr){
                    size++;
                    end = end -> mNext;
                }
                return size;
            }

            bool empty(){
                if(size() == 0){
                    return true;
                }
                return false;
            }

        protected:
            struct ListNode* mHead;
};

int main(){
    char* text = new char[3000];
    fgets(text, 3000, stdin);
    CustomStack stack;
    int i = 0;
    int help = 0;
    
    while(help <= strlen(text)){
        
        if(text[help] == '<'){
            char* buff = new char[30];
            while(text[help] != '>'){
                i++;
                help++;
            }
            strncpy(buff, text+help - i +1, i-1);
            if(strcmp(buff, "br") && strcmp(buff, "hr")){
              if(buff[0]!='/'){
                stack.push(buff);
              }
              else{
                if(!strcmp(stack.top(), buff+1)) stack.pop();
                else{
                  cout << "wrong" << endl;
                  return 0;
                }
              }
            }
            buff = nullptr;
            i = 0;
        }
        help++;
    }
    if(stack.empty()) cout << "correct" << endl;
    else cout << "wrong" << endl;

    return 0;
}
