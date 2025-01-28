class CustomStack {
public:
    CustomStack(){
        maxcount=100;
        mData=(int*)calloc(maxcount,sizeof(int));
        count=0;
    }
    void push(int val){
        if(count==maxcount)
            extend(5);
        *(mData+count)=val;
        count++;
    }
    bool empty(){
        if(count==0)
            return true;
        else
            return false;
    }
    void pop(){
        if(!empty()){
            *(mData+count-1)=0;
            count--;
        }
        else {
            cout << "error";
        }
    }
    int top(){
        if(!empty()){
            int res=*(mData+count-1);
            return res;
        }
        else
            cout << "error";
        return 0;
    }
    size_t size(){
        size_t s=(size_t)count;
        return s;
    }
    void extend(int n){
        maxcount+=n;
        mData=(int*)realloc(mData,maxcount*sizeof(int));
    }

protected:
    int* mData;        //стек
    int count;
    int maxcount;
};

int main() {
    CustomStack obj;
    char* str=(char*)calloc(100,sizeof(char));
    int num,res=0;
    fgets(str,100,stdin);
    char* pch=strtok(str," ");
    while(pch!=NULL){
        num=atoi(pch);
        if(num)
            obj.push(num);
        else{
            int num_r=obj.top();
            if(!num_r)
                return 0;
            obj.pop();

            int num_l=obj.top();
            if(!num_l)
                return 0;
            obj.pop();

            if((*pch)=='+'){
                res=num_l+num_r;
                obj.push(res);
            }
            if((*pch)=='-'){
                res = num_l - num_r;
                obj.push(res);
            }
            if((*pch)=='*'){
                res = num_l * num_r;
                obj.push(res);
            }
            if((*pch)=='/'){
                res=num_l/num_r;
                obj.push(res);
            }
        }
        pch=strtok(NULL," ");
    }
    if(obj.size()==1)
        cout << obj.top();
    else
        cout << "error"<<endl;
    return 0;
}
