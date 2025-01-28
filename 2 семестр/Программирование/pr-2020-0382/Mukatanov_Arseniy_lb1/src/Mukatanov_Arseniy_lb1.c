#include <stdio.h>
int index_first_negative(int a[], int a_size);
int index_last_negative(int a[], int a_size);
int multi_between_negative(int a[], int a_size);
int multi_before_and_after_negative(int a[], int a_size);

int main(){
    int command ;
    scanf("%d\n", &command);
    int a[20];
    int a_size = 0;
    char sym = ' ';
    while(a_size < 20 && sym == ' '){
	    scanf("%d%c",&a[a_size++], &sym);
}

switch(command){
    case 0:
        printf("%d\n", index_first_negative(a,a_size));
        break;
    case 1:
        printf("%d\n", index_last_negative(a,a_size));
        break;
    case 2:
        printf("%d\n", multi_between_negative(a,a_size));
        break;
    case 3:
        printf("%d\n", multi_before_and_after_negative(a,a_size));
        break;
    default:
        printf("Данные некорректны\n");
        break;
}

return 0;
}

int index_first_negative(int a[], int a_size){
    int fn = -1;
    for (int i = 0; i < a_size; i++){
    if(a[i] < 0){
        fn = i;
        break;}}
return fn;}

int index_last_negative(int a[], int a_size){
    int ln = -1;
    for( int i = a_size - 1; i >= 0; i--){
    if(a[i] < 0){
        ln = i;
        break;}}
return ln;}

int multi_between_negative(int a[], int a_size){
    int fn = index_first_negative(a, a_size);
    int ln = index_last_negative(a, a_size);
    int res = 1;
    for (int i = fn; i < ln; i++)
        res *= a[i];
return res;}

int multi_before_and_after_negative(int a[], int a_size){
    int fn = index_first_negative(a, a_size);
    int ln = index_last_negative(a, a_size);
    int res1 = 1, res2 = 1, m_res = 0;
    for(int i = 0; i < fn; i++)
        res1 *= a[i];
    for(int i = ln; i < a_size; i++){
        res2 *=a[i];
    }
    m_res = res1 * res2;
return m_res;   
}
