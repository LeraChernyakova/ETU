// #define BUF_SIZE 5
// #define DEF_KEY_FILE "key"

// // Semaphore operations
// struct sembuf setFree[] = {{0, -1, 0}};
// struct sembuf setBusy[] = {{1, -1, 0}};
// struct sembuf waitNotEmpty[] = {{1, 1, 0}, {0, -1, 0}};
// struct sembuf releaseEmpty[] = {{0, 1, 0}};
// struct sembuf mem_lock[] = {{2, -1, 0}};
// struct sembuf mem_unlock[] = {{2, 1, 0}};
// struct sembuf releaseFull[] = {{0, 1, 0}};
// struct sembuf waitNotFull[] = {{0, 1, 0}, {1, -1, 0}};

#define DEF_KEY_FILE "key"
#define BUF_SIZE 5
typedef struct {
	long type;
	char buf[100];
} Message;

static struct sembuf readEna[1] = {0,-1,0};
static struct sembuf writeEna[1] = {1,-1,0};
static struct sembuf setReadEna[1] = {0,1,0};
static struct sembuf setWriteEna[1] = {1,1,0};

static struct sembuf mem_lock[1] = {2,-1,0};
static struct sembuf mem_unlock[1] = {2,1,0};
static struct sembuf setFree[1] = {0,BUF_SIZE,0};
static struct sembuf waitNotEmpty[1] = {1,-1,0};
static struct sembuf releaseEmpty[1] = {0,1,0};
static struct sembuf waitNotFull[1] = {0,-1,0};
static struct sembuf releaseFull[1] = {1,1,0};