#define MAX 100

class CustomStack { public:
~CustomStack(){ while (mHead){
pop();}}


void throw_error(){ printf("error\n"); delete this; exit(0);}


void check(){
if (empty()){
throw_error();}}


void push(int val){
ListNode* new_elem = new ListNode{mHead, val}; mHead = new_elem;}
void pop(){
check();
ListNode* temp = mHead; mHead = mHead->mNext; delete temp;}
int top(){
check();
return mHead->mData;}
size_t size(){
ListNode* cur = mHead; size_t num;
for (num = 0; cur; num++){ cur = cur->mNext;}
return num;}

bool empty(){
return !((bool)mHead);}

int is_number(char* str){ int len = strlen(str);
if (len == 1 && !isdigit(str[0])){ return 0;}
return 1;}

protected:
ListNode* mHead;};

int main(){
CustomStack* stack = new CustomStack(); char cur[MAX], a;
int first, second; scanf("%s", cur); while (!feof(stdin)){
if (stack->is_number(cur)){ stack->push(atoi(cur));
} else {
first = stack->top(); stack->pop();
second = stack->top(); stack->pop();

if (!strcmp(cur, "+")){
stack->push(first + second);
} else if (!strcmp(cur, "-")){ stack->push(second - first);
} else if (!strcmp(cur, "*")){ stack->push(first * second);
} else if (!strcmp(cur, "/")){ 
	stack->push(second / first);}}
scanf("%s", cur);}


if (stack->size() != 1){ 
	stack->throw_error();}
first = stack->top(); printf("%d\n", first); return 0;}