class CustomStack {
public:
CustomStack(){
    size_stack = 0;
    mData = new int[0];
}

void pop(){
    if (size()<=0) {
        cout << "error";
        exit(0);
    }
    else {
        cout << *(mData + size_stack - 1) << endl;
        *(mData + size_stack - 1) = 0;
        size_stack--;
    }

}


void push (int val)
{  extend(1);
    size_stack++;
    *(mData+size_stack-1) = val;
    //cout << "ok" << endl;
}

int top(){
    if (size()<=0) {
        cout << "error";
        exit(0);
    }
    else
    return *(mData+size_stack-1);
}

size_t size(){
    return size_stack;
}

bool empty(){
    if(size_stack == 0) return true;
    else return false;
}
// методы size, empty + конструкторы, деструктор

private:
int size_stack = 0;
// поля класса, к которым не должно быть доступа извне
void extend(int n){
        count+=n;
        mData=(int*)realloc(mData,count*sizeof(int));
}
protected:  // в этом блоке должен быть указатель на массив данных

int* mData;
    int count=100;
};



int main (){
    CustomStack Stack;
    char comands[5][10] = {"cmd_push", "cmd_pop", "cmd_top",
                                  "cmd_size", "cmd_exit"};
    int count;
    char el_push[20];
    char input_str[10];
    while (1) {
        cin >> input_str;
        if (!strcmp(input_str, comands[0])) {
            cin >> el_push;
            count = 1;
        }
        for (int k = 1; k < 5; k++) {
            if (!strcmp(input_str, comands[k])) {
                count = k + 1;
            }
        }
        switch (count) {
            case 1:
                Stack.push(atoi(el_push));
                cout << "ok\n";
                break;
            case 2:
                Stack.pop();
                break;
            case 3:
                cout << Stack.top() << endl;
                break;
            case 4:
                cout << Stack.size() << endl;
                break;
            case 5:
                cout << "bye";
                exit(0);
            default:;
        }
        count = 0;
    }
    return 0;
}


/* cmd_push 1
cmd_top
cmd_push 2
cmd_top
cmd_pop
cmd_size
cmd_pop
cmd_size
cmd_exit*/
