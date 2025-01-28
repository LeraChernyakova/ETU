using namespace std;

class CustomStack {
public:
    CustomStack(){
        stack_size = 0;
        mData = new int[0];
    }

    void push(int val){
        extend(1);
        mData[stack_size] = val;
        stack_size += 1;
    }

    void pop(){
        mData[stack_size - 1] = 0;
        stack_size -= 1;
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



int main() {

    CustomStack stack;

    int n;
    string command = "a";

    while (true){
        cin >> command;

        if (command == "cmd_exit"){
            cout << "bye\n";
            return 0;
        }
        else if (command == "cmd_push"){
            cin >> n;
            stack.push(n);
            cout << "ok\n";
        }
        else if (command == "cmd_pop"){
            
            if (stack.empty() == false){
                cout << stack.top() << endl;
                stack.pop();
            }
            else{
                cout << "error\n";
                return 0;
            }
        }
        else if (command == "cmd_top"){
            if (stack.empty() == false) {
                cout << stack.top() << endl;
            }
            else{
                cout << "error\n";
                return 0; 
            }
        }
        else if (command == "cmd_size"){
            cout << stack.size() << endl;
        }
    }
    return 0;
}
