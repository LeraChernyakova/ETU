#include <iostream>
#include <cstring> #include <cstdlib> using namespace std;
class CustomStack { public:
    CustomStack()
    {         extend(10);     }
    ~CustomStack()
    {        free(mData);        mData = nullptr;     } public:
    void push(int val)
    {
        if( Size + 1 >= Capasity )
        {
            Capasity *= 2;
            extend(Capasity);         }
        mData[Size] = val;
        ++Size;
    }
    void pop()
    {
        if( Size > 0 )
        {
            --Size;
        }         else         {             cout << "error";             exit(0);
        }
    }
    int top()
    {
        if( Size > 0 )
        {
            return mData[Size - 1];
        }         else         {
            cout << "error";             exit(0);
        }
    }
    size_t size()
    {
        return Size;     }
    bool empty()
    {
        return Size == 0;     }
    void extend(int n)
    {
        Capasity += n;         int* NewData = (int*)malloc(sizeof(int) * Capasity);
        if( mData != nullptr )
        {
            memcpy(NewData, mData, Size * sizeof(int));
            free(mData);         }
        mData = NewData;     }
private:
    size_t Size = 0;     size_t Capasity = 0;
protected:
    int* mData = nullptr;
};
int main()
{
    CustomStack LStack;
    string Str;     getline(cin, Str, '\n');
    int LNumber = 0;     int LNumberSign = 1;     bool IsNewNumber = false;
    for( int i = 0; i < Str.length(); ++i )
    {
        if( Str[i] == '*' )
        {
            int RValue = LStack.top();
            LStack.pop();
            int LValue = LStack.top();             LStack.pop();
            LStack.push(LValue * RValue);
            continue;
        }
        if( Str[i] == '/' )
        {
            int RValue = LStack.top();
            LStack.pop();
            int LValue = LStack.top();             LStack.pop();
            LStack.push(LValue / RValue);
            continue;
        }
        if( Str[i] == '+' )
        {
            int RValue = LStack.top();
            LStack.pop();
            int LValue = LStack.top();             LStack.pop();
            LStack.push(LValue + RValue);
            continue;
        }
        if( Str[i] == '-' )
        {
            if( i < Str.length() - 1 && isdigit(Str[i + 1]) )
            {
                LNumberSign = -1;
            }             else             {
                int RValue = LStack.top();
                LStack.pop();
                int LValue = LStack.top();
                LStack.pop();
                LStack.push(LValue - RValue);
            }
            continue;         }
        if( Str[i] == ' ' )
        {
            if( IsNewNumber )
            {
                LStack.push(LNumber * LNumberSign);
                LNumber = 0;
                LNumberSign = 1;
                IsNewNumber = false;
            }
            continue;         }
        IsNewNumber = true;
        LNumber = LNumber * 10 + (int)(Str[i] - '0');
    }
    if( IsNewNumber )
    {
        LStack.push(LNumber * LNumberSign);
    }
    if( LStack.size() != 1 )
    {         cout<<"error";         exit(0);
    }
    cout << LStack.top();
    return 0;
}

