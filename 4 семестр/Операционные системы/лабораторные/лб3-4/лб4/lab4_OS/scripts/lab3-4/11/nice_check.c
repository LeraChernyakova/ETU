
#include <stdio.h>
#include <unistd.h>
int main()
{
	int nice_val = 0;
	nice_val = nice(0);
	printf("start priority: %d\n", nice_val);
	nice_val = nice(5);
	printf("Let's add 5 to our priority. New priority: %d\n", nice_val);
	nice_val = nice(1000);
	printf("Let's add 1000 to our priority. New priority: %d\n", nice_val);
	nice_val = nice(-1000);
	printf("Lets subtract 1000 from our priority. New priority: %d\n", nice_val);
	
        return 0;
}
