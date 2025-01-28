#include <stdio.h> 

void index_first_negative(){
 int a, index_a;
 index_a=-1;
 for (int i=0; i<20; i++){
  scanf("%d", &a);
  if (a<0){
  index_a=i;
  }
  if ((a<0)||(getchar()=='\n')){
  break;
 }
}
if (index_a>-1){
printf("%d\n", index_a);
}
}

void index_last_negative(){
 int a, index_a;
 index_a=-1;
 for (int i=0; i<20; i++){
  scanf("%i", &a);
  if (a<0){
   index_a=i;
  }
  if (getchar()=='\n'){
   break;
  }
}
if (index_a>-1){
printf("%d\n", index_a);
}
}

void multi_between_negative(){
 int a, pointer = 0 ,min = 0 , max = 1;
 for (int i=0; i<20; i++){
  scanf("%i", &a);
  if (a<0){  
   if (pointer==0){
    min=a;
   }
   else{
    min=max;
   }
  pointer=-1; 
  }
  if (pointer==-1){
   max=max*a;
  }
  if (getchar()=='\n'){
   break;
  }
}
printf("%i\n", min);
}

void multi_before_and_after_negative(){
 int a, pointer = 0 ,min = 1 , max = 1;
 for (int i=0; i<20; i++){
  scanf("%i", &a);
  max=max*a;
  if(a<0){
   pointer=-1;
   max=a;
  } 
  if (pointer==0){
   min=min*a;
  }
  if (getchar()=='\n'){
   break;
  }
}
if (pointer==-1){
 min=min*max;
}
printf("%i\n", min);
}
int main()
{
 int n;
 scanf("%d", &n);
 switch(n){
  case 0: 
   index_first_negative();
  break;
  case 1:
   index_last_negative();
  break;
  case 2:
   multi_between_negative();
  break;
  case 3:
   multi_before_and_after_negative();
  break;
  default:
   printf( "Данные некорректны\n" );
 }
 return 0;
 }
