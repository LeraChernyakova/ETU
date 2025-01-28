#include <iostream>
#include <cstdlib>
#include <cstring>
#define N 20
#define M 100
using std::cout;
class CustomStack
{
public:
	CustomStack()
	{
		buffer_size = 0;
		elements_count = 0;
		mData = NULL;
	}

	~CustomStack()
	{
		delete[] mData;
	}

	void push(int val)
	{
		if (elements_count == buffer_size)
			extend(100);
		mData[elements_count] = val;
		elements_count++;
	}

	void pop()
	{
		/*if (empty())
		{
			throw 1;
			return;
		}*/
		elements_count--;
	}

	int top()
	{
		/*if (empty())
		{
			throw 1;
			return 0;
		}*/
		return mData[elements_count-1];
	}

	size_t size()
	{
		return elements_count;
	}

	bool empty()
	{
		if (!elements_count) return true;
		return false;
	}

private:
	void extend(int n)
	{
		int *tmp = new int [buffer_size + n];
		memcpy(tmp, mData, sizeof(int)*elements_count);
		delete[] mData;
		mData = tmp;
		buffer_size += n;
	}

	int buffer_size;

	int elements_count;

protected:
	int *mData;

};
void FreeAll(char** Arr,int n)
{
    for(int i=0;i<n;i++)
        free(Arr[i]);
    free(Arr);
}
int main()
{
    CustomStack();
    CustomStack stack;
    char** Cmd_Arr= (char**)malloc(N*sizeof(char*));
    char* Inp_s = (char*)malloc(M*sizeof(char));
    fgets(Inp_s,M,stdin);
    int n=0;
    while(strcmp(Inp_s,"cmd_exit\n\0"))
    {
        Cmd_Arr[n]=(char*)malloc(M*sizeof(char));
        strcpy(Cmd_Arr[n],Inp_s);
        n++;
        fgets(Inp_s,M,stdin);
    }
    Cmd_Arr[n]=(char*)malloc(M*sizeof(char));
    strcpy(Cmd_Arr[n],Inp_s);
    n++;
    free(Inp_s);
    for(int i=0;i<n;i++)
    {

        char* p= strtok(Cmd_Arr[i]," \n\0");
        if(!strcmp(p,"cmd_push"))
        {
            char* p=strtok(NULL," \n\0");
            int numb = atoi(p);
            stack.push(numb);
            cout<<"ok\n";
            continue;
        }
        if(!strcmp(Cmd_Arr[i],"cmd_pop"))
        {
            if(stack.empty())
            {
                cout<<"error\n";
                return 0;
            }

            cout<<stack.top()<<"\n";
            stack.pop();
            continue;
        }
        if(!strcmp(Cmd_Arr[i],"cmd_top"))
        {
             if(stack.empty())
            {
                cout<<"error\n";
                return 0;
            }
            cout<<stack.top()<<"\n";
            continue;
        }
        if(!strcmp(Cmd_Arr[i],"cmd_size"))
        {
            cout<<stack.size()<<"\n";
            continue;
        }
        if(!strcmp(Cmd_Arr[i],"cmd_exit"))
        {
            cout<<"bye\n";
            break;
        }
    }
    FreeAll(Cmd_Arr,n);
    return 0;
}
