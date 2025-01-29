#define BUF_SIZE 5
#define DEF_KEY_FILE "key"

// Semaphore operations
struct sembuf setFree[] = {{0, -1, 0}};
struct sembuf setBusy[] = {{1, -1, 0}};
struct sembuf waitNotEmpty[] = {{1, 1, 0}, {0, -1, 0}};
struct sembuf releaseEmpty[] = {{0, 1, 0}};
struct sembuf mem_lock[] = {{2, -1, 0}};
struct sembuf mem_unlock[] = {{2, 1, 0}};
struct sembuf releaseFull[] = {{0, 1, 0}};
struct sembuf waitNotFull[] = {{0, 1, 0}, {1, -1, 0}};

