#include <iostream>
#include <string.h>

using namespace std;


class CustomStack {
        private:
            unsigned int capacity;
            int n;
        public:
            CustomStack(){
                int c = 100;
                capacity = c;
                mData = new int[capacity];
                n = -1;
            }

            ~CustomStack(){
                delete[] mData;
            }

            void push(int val){
                n++;
                mData[n] = val;
            }

            void pop(){
                n--;
            }

            int top(){
                return mData[n];
            }

            size_t size(){
                return n+1;
            }

            bool empty(){
                return n == -1;
            }

            void extend(int n){
                int new_capacity = capacity + n;
                int *tmp = new int[new_capacity];
                for(int i=0; i<n; ++i){
                    tmp[i] = mData[i];
                }
                delete[] mData;
                mData = tmp;
                capacity = new_capacity;
            }
        protected:
            int* mData;
        };

        int main() {
            CustomStack s;

            char *str = new char[20];


            while(cin.getline(str, 20)){
                try{
                    char (*tmp_str)[10] = new char[2][10];
                    int n = 0;
                    char* pch;
                    pch = strtok(str, " \n");
                    while(pch != NULL){
                        char tmp[strlen(pch)];
                        strcpy(tmp, pch);
                        strcpy(tmp_str[n], tmp);
                        n++;
                        pch = strtok(NULL, " \n");
                    }

                    if(!(strcmp(tmp_str[0], "cmd_push"))){
                        s.push(atoi(tmp_str[1]));
                        cout<<"ok"<<endl;
                    } else {
                        throw 1;
                    }
                }
                catch(int a){
                    if(!(strcmp(str, "cmd_top"))){
                        if(s.empty() == 1){
                            cout<<"error"<<endl;
                            return 0;
                        }
                        cout<<s.top()<<endl;
                    }

                    if(!(strcmp(str, "cmd_pop"))){
                        if(s.empty() == 1){
                            cout<<"error"<<endl;
                            return 0;
                        }
                        cout<<s.top()<<endl;
                        s.pop();
                    }

                    if(!(strcmp(str, "cmd_size"))){
                        cout<<s.size()<<endl;
                    }

                    if(!(strcmp(str, "cmd_exit"))){
                        cout<<"bye"<<endl;
                        return 0;
                    }
                }
            }


            return 0;
        }