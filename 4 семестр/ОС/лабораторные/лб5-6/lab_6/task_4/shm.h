#define DEF_KEY_FILE "key"
typedef struct {
    long type;
    char buf[100];
} Message;
static struct sembuf readEna[1] = {0,-1,0};
static struct sembuf writeEna[1] = {1,-1,0};
static struct sembuf setReadEna[1] = {0,1,0};
static struct sembuf setWriteEna[1] = {1,1,0};