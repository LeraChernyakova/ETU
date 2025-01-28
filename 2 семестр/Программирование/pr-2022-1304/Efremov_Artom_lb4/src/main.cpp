#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class CustomStack
{
public:
  CustomStack()
  {
    mData = new int[m_max_size];
  }

  ~CustomStack()
  {
    delete[] mData;
  }

  void push(int val)
  {
    if (m_size + 1 >= m_max_size)
      extend(10);
    mData[m_size++] = val;
  }

  void pop()
  {
    if (empty())
      throw 1;
    m_size--;
  }

  int top()
  {
    if (empty())
      throw 1;
    return mData[m_size - 1];
  }

  int size()
  {
    return m_size;
  }

  bool empty()
  {
    if (m_size)
      return false;
    else
      return true;
  }

  void extend(int n)
  {
    m_max_size += n;
    int *newData = new int[m_max_size];
    memcpy(newData, mData, m_size * sizeof(int));
    delete[] mData;
    mData = newData;
  }

private:
  int m_size = 0;
  int m_max_size = 100;

protected:
  int *mData;
};

int main()
{
  try
  {
    CustomStack stack;
    char input[100] = {0};
    fgets(input, 100, stdin);
    char *p = strtok(input, " \n");
    while (p != NULL)
    {
      if (!strcmp(p, "+"))
      {
        int top = stack.top();
        stack.pop();
        int bottom = stack.top();
        stack.pop();
        stack.push(top + bottom);
      }
      if (!strcmp(p, "-"))
      {
        int top = stack.top();
        stack.pop();
        int bottom = stack.top();
        stack.pop();
        stack.push(bottom - top);
      }
      if (!strcmp(p, "/"))
      {
        int top = stack.top();
        stack.pop();
        int bottom = stack.top();
        stack.pop();
        stack.push(bottom / top);
      }
      if (!strcmp(p, "*"))
      {
        int top = stack.top();
        stack.pop();
        int bottom = stack.top();
        stack.pop();
        stack.push(bottom * top);
      }
      if (atoi(p))
      {
        stack.push(atoi(p));
      }
      p = strtok(NULL, " \n");
    }
    if (stack.size() != 1)
      throw 1;
    else
      cout << stack.top() << endl;
  }
  catch (...)
  {
    cout << "error" << endl;
  }
  return 0;
}