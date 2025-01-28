#include <iostream>
#include <cstring>
#include <cstdlib>
#define BASE_SIZE 100


using std::cout;
using std::endl;


class CustomStack{
	public:
		CustomStack(){
			this->mData = NULL;
			this->buffer_size = 0;
			this->count_elem = 0;
		}

		~CustomStack(){
			delete[] this->mData;
		}

		void push(int val){
			if (this->count_elem == this->buffer_size){
				extend(BASE_SIZE);
			}
			this->mData[this->count_elem++] = val;
		}

		void pop(){
			this->count_elem--;
		}

		int top(){
			return this->mData[count_elem-1];
		}

		size_t size(){
			return this->count_elem;
		}

		bool empty(){
			return this->count_elem == 0;
		}

	private:
		void extend(int n){
			this->buffer_size += n;
			int *tmp = new int [this->buffer_size];
			memcpy(tmp, this->mData, sizeof(int)*this->count_elem);
			delete[] this->mData;
			mData = tmp;
		}
		int buffer_size;
		int count_elem;

	protected:
		int *mData;
};

void free_all(char **cmd_arr, int n){
	for (int i = 0; i < n; i++){
		delete[] cmd_arr[i];
	}
}

int main(){
	CustomStack stack;
	char **cmd_arr = new char* [BASE_SIZE];
	char *inp_str = new char [BASE_SIZE];
	fgets(inp_str, BASE_SIZE, stdin);
	int i = 0;
	while (strcmp(inp_str, "cmd_exit\n\0")){
		cmd_arr[i] = (char *)malloc(BASE_SIZE*sizeof(char));
		strcpy(cmd_arr[i++], inp_str);
		fgets(inp_str, BASE_SIZE, stdin);
	}
	cmd_arr[i] = (char *)malloc(BASE_SIZE*sizeof(char));
	strcpy(cmd_arr[i++], inp_str);
	delete[] inp_str;
	for (int j = 0; j < i; j++){
		char *p = strtok(cmd_arr[j], " \n\0");
		if (!strcmp(p, "cmd_push")){
			char *p = strtok(NULL, " \n\0");
			int n = atoi(p);
			stack.push(n);
			cout << "ok" << endl;
			continue;
		}
		if (!strcmp(cmd_arr[j], "cmd_pop")){
			if (stack.empty()){
				cout << "error" << endl;
				return 0;
			}
			cout << stack.top() << endl;
			stack.pop();
			continue;
		}
		if (!strcmp(cmd_arr[j], "cmd_top")){
			if (stack.empty()){
				cout << "error" << endl;
				return 0;
			}
			cout << stack.top() << endl;
			continue;
		}
		if (!strcmp(cmd_arr[j], "cmd_size")){
			cout << stack.size() << endl;
			continue;
		}
		if (!strcmp(cmd_arr[j], "cmd_exit")){
			cout << "bye" << endl;
			break;
		}
	}
	free_all(cmd_arr, i);
	return 0;
}
