
#include <iostream>
#include <thread>

void my_thread_func(){
  std::cout<<"Hello from my thread! "<<std::endl;
}

int main(){

  std::thread my_t(my_thread_func);//запуск потока

  std::cout<<"Hello from main! "<<std::endl;

  return 0;
}
