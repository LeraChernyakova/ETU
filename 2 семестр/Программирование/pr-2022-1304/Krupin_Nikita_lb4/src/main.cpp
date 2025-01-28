#include <iostream>
#include <cstring>

using namespace std;

/*
Using:
CustomStack(); - саморасширяющийся стек с буфером 4 без нижнего предела ёмкости.
CustomStack(n); - стек, ограниченный ёмкостью n.
CustomStack(n, k); - если k > 0: саморасширяющийся стек с буфером k и нижним пределом ёмкости n;
					 если k = 0: стек, ограниченный ёмкостью n.
push(item); - добавление элемента item.
pop(); - удаление верхнего элемента.
size(); - количество элементов в стеке.
empty(); - проверка на пустоту.
top(); - возврат значения верхнего элемента.
extend(n); - увеличение нижнего предела ёмкости на n, для уменьшения может быть отрицательным.

Error codes:
1 - Not enough memory.
2 - Stack overflow.
3 - Empty stack error.
*/
class CustomStack{
public:
	CustomStack(size_t init_size, size_t buf_size):
		mStackSize(init_size), mReservedSize(init_size), mBufSize(buf_size){
		mData = new char*[init_size];
		if (init_size && !mData) throw 1; // Not enough memory.
	}
	CustomStack(size_t init_size): CustomStack(init_size, 0) {}
	CustomStack(): CustomStack(0, 4) {}
	
	void push(const char* val){
		if (mBufSize && mDataSize >= mStackSize)
			addStackSize(mBufSize);
		if (mDataSize >= mStackSize) throw 2; // Stack overflow.
		mData[mDataSize++] = (char*)val;
	}
	
	void pop(){
		if (empty()) throw 3; // Empty stack error.
		mDataSize--;
		if (mBufSize && mDataSize+2*mBufSize < mStackSize)
			if (mStackSize >= mReservedSize + mBufSize)
				addStackSize((int)mReservedSize-(int)mStackSize);
			else addStackSize((int)mBufSize*(-1));
	}
	
	size_t size(){
		return mDataSize;
	}
	
	bool empty(){
		return !mDataSize;
	}
	
	char* top(){
		if (empty()) throw 3; // Empty stack error.
		return mData[mDataSize-1];
	}
	
	void extend(int n){
		if ((int)mStackSize+n < (int)mDataSize) throw 2; // Stack overflow.
		mReservedSize += n;
		if (mStackSize < mReservedSize)
			addStackSize((int)mReservedSize-(int)mStackSize);
	}
	
	~CustomStack(){
		delete[] mData;
	}

private:
	size_t mStackSize, mDataSize = 0;
	size_t mReservedSize, mBufSize;
	
	void addStackSize(int n){
		char** tmpData;
		mStackSize += n;
		tmpData = new char*[mStackSize];
		if (mStackSize && !tmpData) throw 1; // Not enough memory.
		memcpy(tmpData, mData, mDataSize*sizeof(char*));
		delete[] mData;
		mData = tmpData;
		tmpData = NULL;
	}
	
protected:
	char** mData;
};

int main() {
	CustomStack stack = CustomStack();
	char str[3001], *s = str, *f;
	int errStatus = 0;
	
	cin.getline(str, 3001);
	
	while(s = strchr(s, '<')){
		if (!(f = strchr(s, '>'))){
			errStatus = 1; break;
		}
		*f = '\0';
		if (*(s+1) == '/')
			if (stack.empty() || strcmp(stack.top(), s+2)){
				errStatus = 1; break;
			} else stack.pop();
		else if (strcmp("br", s+1) && strcmp("hr", s+1))
			stack.push(s+1);
		s = f+1;
	}
	
	if (!errStatus && stack.empty()) cout << "correct";
	else cout << "wrong";
	return 0;
}
