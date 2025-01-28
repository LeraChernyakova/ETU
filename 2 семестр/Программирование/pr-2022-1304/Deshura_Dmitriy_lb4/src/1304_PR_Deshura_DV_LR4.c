#include <iostream>
#include <cstring>

using namespace std;

class CustomStack {
public:
    CustomStack(){
        mData = new char*[4];
        sizeOfStack = 4;
    }
    
    void push(const char* val){
        if(numEl + 1 > sizeOfStack){
            extend(4);
        }
        mData[numEl] = (char *)val;
        numEl ++;
    }
    
    void pop(){
        if(!empty()){
            mData[--numEl] = NULL;
        }
    }
    
    char* top(){
        if(!empty()){
            return mData[numEl - 1];
        }
        return NULL;
    }
    
    size_t size(){
        return numEl;
    }
    
    bool empty(){
        return !numEl;
    }
    
    void extend(int n){
        char** buf;
        buf = new char*[sizeOfStack + n];
        for(int i = 0; i < sizeOfStack; i++){
            buf[i] = mData[i];
        }
        sizeOfStack += (size_t)n;
        delete[] mData;
        mData = buf;
    }
    
    ~CustomStack(){
        delete[] mData;
    }
    
private:
    size_t sizeOfStack, numEl = 0;
    
protected:
    char** mData;
};

int main() {
    
    CustomStack mData = CustomStack();
    char str[3001], *s, *f;
    int errorFlag = 0;
    cin.getline(str, 3001);
    
    s = strchr(str, '<');
    while(s){
        
        f = strchr(s, '>');
        if(!f){
            errorFlag = 1;
            break;
        }
        
        *f = '\0';
        if(*(s + 1) == '/'){
            if(!mData.top()){errorFlag = 1; break;}
            if(!strcmp(s + 2, mData.top()))
                mData.pop();
            else {errorFlag = 1; break;}
        } else if(strcmp(s + 1, "br") && strcmp(s + 1, "hr"))
            mData.push(s+1);

        s = f + 1;
        s = strchr(s, '<');
    
    }

    if(errorFlag || !mData.empty())
        cout << "wrong";
    else
        cout << "correct";

    return 0;
}
