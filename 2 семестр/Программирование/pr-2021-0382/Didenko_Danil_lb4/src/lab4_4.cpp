#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


struct ListNode {
    ListNode* mNext;
    int mData;
};

class CustomStack {

private:    // поля класса, к которым не должно быть доступа извне

    int size_stack = 0;

protected:  // в этом блоке должен быть указатель на голову
    ListNode* mHead = NULL;

public:
    ~CustomStack(){
        delete mHead;
    }
    void push(int val){
        ListNode* B = new ListNode;
        B->mData = val;
        B->mNext = mHead;
        mHead = B;
        size_stack++;
        cout << "ok\n";
    };                              //  добавляет новый элемент в стек
    void pop(){
        if(size_stack == 0){
            cout << "error" << endl;
            exit(0);
        }
        cout << mHead->mData << endl;
        ListNode* ptr;
        ptr = mHead->mNext;
        delete mHead;
        mHead = ptr;
        size_stack--;
    };                     //  удаляет из стека последний элемент
    int top(){
       if(mHead != NULL)
           return mHead->mData; //  доступ к верхнему элементу
        else{
           cout << "error" << endl;
           exit(0);
       }
    };

    size_t size(){
        return size_stack;
    };                  //  возвращает количество элементов в стеке
    bool empty(){
        if(size_stack == 0){
            return true;
        }else return false;
    };                  //  проверяет отсутствие элементов в стеке
};


int main()
{
    const int len_input = 10;
    CustomStack Stack;
    char comands[5][len_input] = {"cmd_push","cmd_pop","cmd_top",
                                  "cmd_size","cmd_exit"};
    int choice;
    char el_push[20];
    char input[len_input];
    while(true){
        cin >> input;
        if(!strcmp(input,comands[0])){
            cin >> el_push;
            choice = 1;
        }
        for(int j = 1;j<5;j++){
            if(!strcmp(input,comands[j])){
                choice = j+1;
            }
        }
        switch (choice) {
            case 1:
                Stack.push(atoi(el_push));
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
                cout << "bye\n";
                exit(0);
            default:
                cout << "try again\n";
        }
        choice = 0;
    }
    return 0;
}
