#define BUF_SIZE 15
#define DEF_KEY_FILE "key"

struct sembuf waitNotFull[1] = {1,0, 0};
struct sembuf waitNotEmpty[1] ={0,0,0};

struct sembuf releaseFull[2] = {{1,-1, 0},{0,1,0}};
struct sembuf releaseEmpty[2] ={{0,-1, 0},{1,1,0}};

struct sembuf mem_lock[1] =  {2, -1, 0};
struct sembuf mem_unlock[1] = {2, 1, 0};

struct sembuf setFree[2] = {{0, BUF_SIZE, 0},{1,BUF_SIZE,0}};

