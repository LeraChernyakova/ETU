#include <stdio.h>
#include <signal.h>

void sig_handler(int sig) {
    printf("Signal %d ignored.\n", sig);
}

int main() {

    for (int i = 34; i <= 40; i++) {
        signal(i, sig_handler);
    }

    while (1) {
        sleep(1);
    }

    return 0;
}
