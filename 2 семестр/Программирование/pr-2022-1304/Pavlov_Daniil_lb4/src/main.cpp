class CustomStack{
    public:
        CustomStack(){
            id = 0;
            mData = (int*)malloc(sizeof(int));
        }

        ~CustomStack(){
            free(mData);
        }

        void push(int val){
            mData[id] = val;
            id++;
        }

        void pop(){
            if (this->empty() == false){
                id--;
            }
            else{
                cout<<"error";
                exit(0);
            }
        }

        int top(){
            if (this->empty() == false){
                return mData[id-1];
            }else{
                cout<<"error";
                exit(0);
            }
        }

        int size(){
            return id;
        }

        bool empty(){
            return id == 0;
        }

        void extend(int n){
            mData = (int*)realloc(mData, n * sizeof(int));
        }

    size_t id;
    protected:
        int *mData;
};


int main(){
    string input;
    getline(cin, input, '\n');
    int numb = 0, a, b, sign = 1, n = 0;
    int check = 0;
    int i;
    CustomStack Stack;
    for(i = 0; i<input.length(); i++){
        if (input[i] == '+'){
            a = Stack.top();
            Stack.pop();
            b = Stack.top();
            Stack.pop();
            Stack.push(a + b);
            continue;
        }

        if (input[i] == '*'){
            a = Stack.top();
            Stack.pop();
            b = Stack.top();
            Stack.pop();
            Stack.push(a * b);
            continue;
        }

        if (input[i] == '/'){
            a = Stack.top();
            Stack.pop();
            b = Stack.top();
            Stack.pop();
            Stack.push(a / b);
            continue;
        }
        if (input[i] == '-'){
            if (i < input.length() - 1 && isdigit(input[i + 1])){
                sign = -1;
            }else{
                a = Stack.top();
                Stack.pop();
                b = Stack.top();
                Stack.pop();
                Stack.push(b - a);
            }
            continue;
        }

        if (input[i] == ' '){
            if (check == 1){
                n++;
                Stack.extend(n);
                Stack.push(numb*sign);
                numb = 0;
                sign = 1;
                check = 0;
            }
            continue;
        }
        check = 1;
        numb = 10 * numb + (int)(input[i] - '0');
    }
    if (check == 1){
        n++;
        Stack.extend(n);
        Stack.push(numb*sign);
    }
    if (Stack.size() > 1){
        cout<<"error";
    }else{
        cout<<Stack.top();
    }
    return 0;
}
