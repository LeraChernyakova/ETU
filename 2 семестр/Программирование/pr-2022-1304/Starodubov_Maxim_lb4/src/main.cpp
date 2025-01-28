#include <iostream>
#include <cstring>

using namespace std;

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
		for (int i = 0; i < elements_count; i++)
			delete[] mData[i];
		delete[] mData;
	}

	void push(const char *val)
	{
		if (elements_count == buffer_size)
			extend(100);
		mData[elements_count] = new char [strlen(val)+1];
		strcpy(mData[elements_count++], val);
	}

	void pop()
	{
		if (empty())
		{
			throw 1;
			return;
		}
		elements_count--;
		delete[] mData[elements_count];
	}

	char *top()
	{
		if (empty())
		{
			throw 1;
			return NULL;
		}
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
		char **tmp = new char* [buffer_size + n];
		memcpy(tmp, mData, sizeof(char*)*elements_count);
		delete[] mData;
		mData = tmp;
		buffer_size += n;
	}

	int buffer_size;
	int elements_count;

protected:
	char **mData;

};

bool isPair(char *left_bkt, char *right_bkt)
{
	if (!strcmp(left_bkt+1, right_bkt+2)) return true;
	return false;
}

int main()
{
	char input[3000];
	cin.getline(input, 3000);
	
	char *left_bkt = strstr(input, "<");
	char *right_bkt = strstr(left_bkt, ">");

	CustomStack stack;
	
	char *cur_bkt;
	while (left_bkt && right_bkt)
	{
		cur_bkt = new char [right_bkt - left_bkt + 2];
		memcpy(cur_bkt, left_bkt, right_bkt - left_bkt + 1);
		cur_bkt[right_bkt - left_bkt + 1] = '\0';

		if (strcmp(cur_bkt, "<br>") && strcmp(cur_bkt, "<hr>"))
		{
			if (cur_bkt[1] != '/')
			{
				stack.push(cur_bkt);
			} else
			{
				if (stack.empty() || !isPair(stack.top(), cur_bkt))
				{
					cout << "wrong";
					delete[] cur_bkt;
					return 0;
				}
				
				stack.pop();
			}
		}

		delete[] cur_bkt;
		left_bkt = strstr(right_bkt, "<");
		if (left_bkt)
			right_bkt = strstr(left_bkt, ">");
	}

	if (stack.empty()) cout << "correct";
	else cout << "wrong";

	return 0;
}
