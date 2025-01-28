/*#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;*/
class CustomStack {
public:
	CustomStack()
	{	mHead=NULL;
	}
	void push(int val)
	{	ListNode *m=new ListNode;
		m->mData=val;
		m->mNext=mHead;
		mHead=m;
	}
	void pop()
	{	ListNode *m=mHead;
		mHead=mHead->mNext;
		delete m;
	}
	int top()
	{	return mHead->mData;
	}
	size_t size()
	{	ListNode *m=mHead;
		int kol=0;
		while (m)
		{	m=m->mNext;
			kol++;
		}
		return kol;
	}
	bool empty()
	{	if (size())
			return false;
		else
			return true;
	}
	~CustomStack(){
		ListNode *m=mHead;
		while (mHead)
		{	mHead=mHead->mNext;
			delete m;
			m=mHead;
		}
	}


private:
	/*struct ListNode {
    		ListNode* mNext;
    		int mData;
		};*/
protected:
    ListNode* mHead;
};

int main() {
    char *s=new char[40];
    CustomStack stack;
    int n;
    int err=0;
    fgets(s,40,stdin);
    s[strlen(s)-1]='\0';
    while (strcmp(s,"cmd_exit"))
    {	if (!strncmp(s,"cmd_push",sizeof(char)*8))
	{	n=atoi(s+8);
		stack.push(n);
		puts("ok");
	}
	if (!strcmp(s,"cmd_pop"))
	{	if (stack.empty())
		{	puts("error");
			err=1;
			break;
		}
		cout<<stack.top()<<endl;
		stack.pop();
	}
	if (!strcmp(s,"cmd_top"))
	{	if (stack.empty())
		{	puts("error");
			err=1;
			break;
		}
		cout<<stack.top()<<endl;
	}
	if (!strcmp(s,"cmd_size"))
		cout<<stack.size()<<endl;
	fgets(s,40,stdin);
    	s[strlen(s)-1]='\0';
    }
    if (!err)
    	cout<<"bye"<<endl;
    return 0;
}
