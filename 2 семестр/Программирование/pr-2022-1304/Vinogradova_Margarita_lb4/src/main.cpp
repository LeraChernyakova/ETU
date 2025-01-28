/*#include<iostream>
using namespace std;
#include<cstring>
struct ListNode {
    ListNode* mNext;
    char* mData;
};
*/
struct Teg{
    int open;
    int close;
    char* type;
};
class CustomStack {

public:
    CustomStack(){
        mHead=new ListNode;
        mHead=NULL;
        size_st=0;
    }

    void push(const char * el){
        
        ListNode* new_el=new ListNode;
        new_el->mData=new char[strlen(el)];
        strcpy(new_el->mData,el);
        if(mHead==NULL){
            mHead=new_el;
        }
        else{
        new_el->mNext=mHead;
        mHead=new_el;
        }
        size_st++;
       
    }
   char*top(){
       return mHead->mData;
   }
    void print(){
        while(mHead!=NULL){
            puts(mHead->mData);
            mHead=mHead->mNext;

        }
    }
    size_t size(){
        // size_t kol=0;
        // while(mHead!=NULL){
        //     kol++;
        //     mHead=mHead->mNext;

        // }
        return size_st;
    }
    void pop() {
        ListNode* buff = mHead;
        mHead = mHead->mNext;
        size_st--;
        
    }
    bool empty(){
        if(mHead==NULL)return true;
        else return false;
    }
    
    void  html_check(char * s){
        char one_el[3000];
        int kol,check=0;
        
        for(int i=0;i< strlen(s);i++){
            if(s[i]=='<' && check==0){
                kol=0;
                check=1;
                continue;
            }
            if(check==1&&s[i]!='>'){
                one_el[kol]=s[i];
                kol++;
            }
            if(s[i]=='>'){
                one_el[kol]='\0';
                kol=0;
                check=0;
                
                push(one_el);
    
            }
    
        }
        
        
        char answer[1000][1000];
        int kol_teg=0;
       
        //cout<<"ok";
        while(size_st>0){
           
            if(strcmp(top(),"hr")==0 || strcmp(top(),"br")==0){
              //  size_st--;
                pop();
            }else{
                strcpy(answer[kol_teg],top());
                pop();
                //size_st--;
                kol_teg++;
            }
        }
        
         if(kol_teg%2!=0 || kol_teg<0){
             cout<< "wrong"<<endl;
             
         }else{
             
             struct Teg teg[kol_teg];
             for(int i=0;i<kol_teg;i++){
                 if(answer[i][0]=='/'){
                     
                     teg[i].type=new char[strlen(answer[i])];
                     strcpy(teg[i].type,&answer[i][1]);
                     teg[i].open=0;
                     teg[i].close=1;
                 }else{
                     
                     teg[i].type=new char[strlen(answer[i])];
                     strcpy(teg[i].type,answer[i]);
                     teg[i].open=1;
                     teg[i].close=0;
                 }
             }
             int kol_checked=0;
            for(int i=0;i<kol_teg;i++){
                int kol_ins_o=0;
                int kol_ins_c=0;
                for(int j=kol_teg-1;j>i;j--){
                    
                    if(strcmp(teg[i].type,teg[j].type)==0 && teg[i].close==1 && teg[i].open==0 && teg[j].close==0 && teg[j].open==1){
                        //cout<<"okok"<<endl;
                        for(int q=i;q<=j;q++){
                            if(teg[q].close==1)kol_ins_c++;
                            if(teg[q].open==1)kol_ins_o++;
                        }
                      // cout<<kol_ins_o<<" "<<kol_ins_c<<endl;
                        if(kol_ins_o==kol_ins_c){
                            teg[i].open=1;
                            teg[j].close=1;
                            kol_checked++;
                        }
                        
                    }
                }
                
            }
            if(kol_teg/2==kol_checked)cout<<"correct"<<endl;
            else cout<<"wrong"<<endl;
        }
        
    }
    

protected:
    ListNode* mHead;
    size_t size_st;
    
};

//<html><head><title>HTML Document</title></head><body><p><b>This text is bold,<br><i>this is bold and italics</i></b></p></body></html>
int main(){
    CustomStack st;
    
    char* s= new char[3000] ;
    cin.getline(s,3000,'\n');
    st.html_check(s);
    //cout<<"wrong";
    //st.push("qwe");
    //st.print();
    //cout<<st.top();
    return 0;
}
