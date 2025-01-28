    #include <iostream>
    #include <cstdlib>

    using namespace std;

    class CustomStack
    {

    public:
        int k = 0;
        CustomStack()
        {
            mData = (int *)malloc(sizeof(int));
        }
        ~CustomStack()
        {
                free(mData);
        }

        size_t size()
        {
            return k;
        }
        void push(int val)
        {
            mData[k] = val;
            k += 1;
            extend(1);
        }

        void pop()
        {
            if (this->empty())
            {
                cout << "error" << endl;
                exit(0);
            }
            // free(mData + (k - 1) * sizeof(int));
            k -= 1;
        }

        int top()
        {
            if (this->empty())
            {
                cout << "error" << endl;
                exit(0);
            }
            return mData[k - 1];
        }

        bool empty()
        {
            if (k == 0)
            {
                return 1;
            }
            return 0;
        }

        void extend(int n)
        {
            mData = (int *)realloc(mData, sizeof(int) * (k + n));
        }

    private:
        // поля класса, к которым не должно быть доступа извне

    protected: // в этом блоке должен быть указатель на массив данных
        int *mData;
    };

    int main()
    {
        CustomStack MyStack;
        string s;
        char h[100];
        int i, j=0;
        for (j = 0; j < 100; j++)
        {
            h[j] = '\0';
        }
        int counter = 0;
        getline(cin, s, '\n');
        s.insert(s.length(), 1, '!');
        for (i = 0; i < s.length(); i++)
        {
            // cout << s[i] << endl;
            if ((s[i] != ' ') and (s[i] != '!') and (s[i] != '+') and (s[i - 1] != '*') and (s[i] != '/'))
            {
                h[counter] = s[i];
                counter += 1;
            }
            if ((s[i] == ' ' or s[i]=='!') and (s[i - 1] != '+') and (s[i - 1] != '/') and (s[i - 1] != '*') and (s[i - 1] != '-'))
            {
                // cout << h << endl;
                MyStack.push(atoi(h));
                counter = 0;
                for (j = 0; j < 100; j++)
                {
                    h[j] = '\0';
                }
            }
            if (s[i] == '+' and s[i-1]==' ')
            {
                int a = MyStack.top();
                MyStack.pop();
                int b = MyStack.top();
                MyStack.pop();
                // cout << a << ", " << b << endl;
                MyStack.push(a + b);
                counter = 0;
                for (j = 0; j < 100; j++)
                {
                    h[j] = '\0';
                }
            }

            if (s[i] == '-' and (s[i + 1] == ' ' or s[i + 1] == '!') and s[i-1]==' ')
            {
                int a = MyStack.top();
                MyStack.pop();
                int b = MyStack.top();
                MyStack.pop();
                // cout << a << ", " << b << endl;
                MyStack.push(b - a);
                counter = 0;
                for (j = 0; j < 100; j++)
                {
                    h[j] = '\0';
                }
            }

            if (s[i] == '*' and s[i-1]==' ')
            {
                int a = MyStack.top();
                MyStack.pop();
                int b = MyStack.top();
                MyStack.pop();
                // cout << a << ", " << b << endl;
                MyStack.push(b * a);
                counter = 0;
                for (j = 0; j < 100; j++)
                {
                    h[j] = '\0';
                }
            }
            if (s[i] == '/' and s[i-1]==' ')
            {
                int a = MyStack.top();
                MyStack.pop();
                int b = MyStack.top();
                MyStack.pop();
                // cout << a << ", " << b << endl;
                MyStack.push(a / b);
                counter = 0;
                for (j = 0; j < 100; j++)
                {
                    h[j] = '\0';
                }
            }
        }
        if (MyStack.empty()==1 or MyStack.size()>1 ){
            cout << "error" << endl;
        }
        else{
            cout << MyStack.top();
        }
    }
