class CustomStack
{
public:
    ~CustomStack()
    {
        while (mHead)
        {
            pop();
        }
    }
    void error()
    {
        printf("error\n");
        delete this;
        exit(0);
    }
    void check()
    {
        if (empty())
        {
            error();
        }
    }
    int NumCheck(char *s)
    {
        int len = strlen(s);
        if (len == 1 && !isdigit(s[0]))
        {
            return 0;
        }
        return 1;
    }
    void push(int val)
    {
        ListNode *upd = new ListNode{mHead, val};
        mHead = upd;
    }
    void pop()
    {
        check();
        ListNode *temp = mHead;
        mHead = mHead->mNext;
        delete temp;
    }
    int top()
    {
        check();
        return mHead->mData;
    }
    size_t size()
    {
        ListNode *cur = mHead;
        size_t n;
        for (n = 0; cur; n++)
        {
            cur = cur->mNext;
        }
        return n;
    }
    bool empty()
    {
        return !((bool)mHead);
    }

protected:
    ListNode *mHead;
};

int main()
{
    CustomStack *stack = new CustomStack();
    char cur[100];
    int first, secound;
    scanf("%s", cur);
    while (!feof(stdin))
    {
        if (stack->NumCheck(cur))
        {
            stack->push(atoi(cur));
        }
        else
        {
            first = stack->top();
            stack->pop();
            secound = stack->top();
            stack->pop();
            if (!strcmp(cur, "+"))
            {
                stack->push(first + secound);
            }
            else if (!strcmp(cur, "-"))
            {
                stack->push(secound - first);
            }
            else if (!strcmp(cur, "*"))
            {
                stack->push(first * secound);
            }
            else if (!strcmp(cur, "/"))
            {
                stack->push(secound / first);
            }
        }
        scanf("%s", cur);
    }
    if (stack->size() != 1)
    {
        stack->error();
    }
    first = stack->top();
    printf("%d\n", first);
    return 0;
}

