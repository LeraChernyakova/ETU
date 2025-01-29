
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  pid_t pid;
  int ret;
  int a=0;

  pid = fork();

  a+=5;

  //pid_t pid1 = fork();
  
  switch (pid){
    // весь код после fork() дважды:
    // в родительском процессе и в процессе потомке
    
  case -1: //неудачная попытка создать процесс-потомок
    exit(-1); //выход из родительского процесса
    
  case 0: //потомок
    std::cout<<"CHILD:: Hello, my pid = "<< getpid()<<"; my parent's pid (ppid) = "<<getppid()<<std::endl;
    a+=10;
    std::cout<<a<<std::endl;
    exit(ret);
      
  default: //родитель pid>0
    std::cout<<"PARENT:: Hello, my pid = "<< getpid()<<"; my child's pid = "<<pid<<std::endl;
    a+=20;
    std::cout<<a<<std::endl;
    wait(&pid);
  }
  
  return 0;
}
