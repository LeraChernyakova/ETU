#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
int main(){

	printf("max amount of files that process can have open: %ld\n",sysconf(FOPEN_MAX));
	printf("PIPE_BUF: %d\n", PIPE_BUF);
	return 0;
}
