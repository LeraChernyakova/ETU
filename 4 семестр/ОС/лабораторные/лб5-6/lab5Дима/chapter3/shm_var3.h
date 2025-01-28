#define BUF_SIZE 3
#define DEF_KEY_FILE "key"

struct sembuf waitNotFull[] = {{0, 0, 0}, {0, -1, 0}};
struct sembuf waitNotEmpty[] = {{1, 0, 0}, {1, -1, 0}};

struct sembuf releaseFull[] = {{1, 1, 0}};
struct sembuf releaseEmpty[] = {{0, 1, 0}};

struct sembuf mem_lock[] = {{2, 0, 0}, {2, 1, 0}};
struct sembuf mem_unlock[] = {{2, -1, 0}};

struct sembuf setFree[] = {{0, BUF_SIZE, 0}};