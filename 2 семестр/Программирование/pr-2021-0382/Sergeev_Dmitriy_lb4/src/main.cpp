#include <iostream>
#include <cstring>

using namespace std;

struct ListNode {
    ListNode* mNext;
    int mData;
};

class CustomStack {

public:

    CustomStack()
    {
        mHead= nullptr;
    }

    ~CustomStack()
    {
        auto* cur=mHead;
        while (cur!= nullptr)
        {
            mHead=mHead->mNext;
            delete(cur);
            cur=mHead;
        }
    }

    void push(int val)
    {
        auto* node=new ListNode;
        node->mData=val;
        node->mNext=mHead;
        mHead=node;
    }

    void pop()
    {
        if (this->empty())
        {
            cout << "error" << endl;
            exit(0);
        }
        auto tmp=mHead;
        mHead=mHead->mNext;
        cout << tmp->mData << endl;
        delete tmp;
    }

    int top()
    {
        if (this->empty())
        {
            cout << "error" << endl;
            exit(0);
        }
        return mHead->mData;
    }

    size_t size()
    {
        size_t size=0;
        auto* cur=mHead;
        while (cur!= nullptr)
        {
            size++;
            cur=cur->mNext;
        }
        return size;
    }

    bool empty() {
        if (mHead == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:

// поля класса, к которым не должно быть доступа извне

protected:  // в этом блоке должен быть указатель на голову

    ListNode* mHead;
};

int main()
{
    CustomStack head;
    char comList[5][10]={"cmd_push","cmd_pop","cmd_top","cmd_size", "cmd_exit"};
    char com[15];
    while (true)
    {
        cin >> com;
        if (strcmp(com,comList[0])==0)
        {
            int val;
            cin >> val;
            head.push(val);
            cout << "ok" << endl;
            continue;
        }
        if (strcmp(com,comList[1])==0)
        {
            head.pop();
            continue;
        }
        if (strcmp(com,comList[2])==0)
        {
            cout << head.top() << endl;
            continue;
        }
        if (strcmp(com,comList[3])==0)
        {
            cout << head.size() << endl;
            continue;
        }
        if (strcmp(com,comList[4])==0)
        {
            cout << "bye" << endl;
            exit(0);
        }
    }
    return 0;
}