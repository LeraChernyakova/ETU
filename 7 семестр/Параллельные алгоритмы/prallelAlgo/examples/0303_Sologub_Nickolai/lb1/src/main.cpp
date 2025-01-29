#include "process.h"
#include "thread.h"
#include <iostream>
using namespace std;
int main(){
    bool flag = true;
    int choice = 0;
    while(flag){
       cout << "Введите:\n0 для программы через процессы\n1 для программы через потоки\n2 для программы через потоки для умножения по P потоков\n3 для выхода\n";
       cin >> choice;
       switch(choice){
        case 0:
	{
            Process();
            break;
	}
        case 1:
		{
            Thread obj = Thread();
	    obj.proceedThreads(1);
            break;
		}
        case 2:
		{
            Thread obj = Thread();
	    obj.threadsCount = 7;
	    obj.proceedThreads(2);
            break;
		}
        case 3:
		{
            flag = false;
            break;
		}
       }
    }
   return 0;
}
