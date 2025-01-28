class CustomStack {
public:
    CustomStack(){
        stack_size = 0;
        mData = new int[0];
    }
    
    ~CustomStack(){
        delete[] mData;
    }

    void push(int val){
        extend(1);
        mData[stack_size] = val;
        stack_size++;
    }

    void pop(){
        cout << mData[stack_size - 1] << endl;
        mData[stack_size - 1] = 0;
        stack_size--;
    }

    int top(){
        return mData[stack_size - 1];
    }

    size_t size(){
        return stack_size;
    }

    bool empty(){
        if(stack_size == 0)
            return true;
        else
            return false;
    }

private:
    int stack_size;
    
    void extend(int n){
        mData = (int*) realloc(mData, n * sizeof(int));
    }

protected:
    int* mData;
};

int main(){
    int n;
    char choice[100];
    CustomStack Stack;

    while(true){
        choice[0] = '\0';
        cin >> choice;
        if(!strcmp(choice, "cmd_push")){
            cin >> n;
            Stack.push(n);
            cout << "ok" << endl;
        }else if(!strcmp(choice, "cmd_size")){
            cout << Stack.size() << endl;
        }else if(!strcmp(choice, "cmd_pop")){
            if(Stack.empty() == 1){
                cout << "error";
                exit(0);
            }
            Stack.pop();
        }else if(!strcmp(choice, "cmd_top")){
            if(Stack.empty() == 1){
                cout << "error";
                exit(0);
            }
            cout << Stack.top() << endl;
        }else if(!strcmp(choice, "cmd_exit")){
            cout << "bye";
            exit(0);
        }else{
            continue;
        }
    }
}
