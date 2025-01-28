	class CustomStack {
		public:
		CustomStack(){
		mHead = NULL;
		};

	CustomStack(){
	while(mHead){
	ListNode* deleting = mHead;
	mHead = mHead->mNext;
	free(deleting);
		};
	};

	void push(int val){
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	if(mHead == NULL){
	newNode->mNext = NULL;
			}else{
	newNode->mNext = mHead;
	}

	newNode->mData = val;
	mHead = newNode;
	};

	int pop(){
		if(mHead == NULL){
		printf("error");
	exit(0);
	}	

	ListNode* temp = mHead;
	int tempD = temp->mData;
	mHead = mHead->mNext;
	free (temp);
	return tempD;
	};


int top(){
	if(this->empty()){
	printf("error\n");
	exit(0);
	}
	return mHead->mData;
	};
	size_t size() {
	if (mHead == NULL) {
	return 0;
			} else {
	int counter = 1;
	struct ListNode *temp = mHead;
	while (temp->mNext != NULL) {
	counter++;
	temp = temp->mNext;
	}
	return counter;
	}
	}
	bool empty(){
	return mHead==NULL;
	};
	protected:
	ListNode* mHead = NULL;
	};
	int main() {
	char option[10];
	CustomStack Stack;
	while (1) {
	fgets(option, 10, stdin);
	option[strcspn(option, "\n ")] = 0;
	if (!strcmp(option, "cmd_push")) {
	int count;
	scanf("%d", &count);
	Stack.push(count);
	cout<<"ok"<<endl;
	} else if (!strcmp(option, "cmd_pop")) {
	int poppedEl = Stack.pop();
	cout<<poppedEl<<endl;
	} else if (!strcmp(option, "cmd_top")) {
	int topEl = Stack.top();
	cout<<topEl<<endl;
	} else if (!strcmp(option, "cmd_size")) {
	cout<<Stack.size()<<endl;
	} else if (!strcmp(option, "cmd_exit")) {
	cout<<"bye";
	exit(0);
	}
	}
		}	 
