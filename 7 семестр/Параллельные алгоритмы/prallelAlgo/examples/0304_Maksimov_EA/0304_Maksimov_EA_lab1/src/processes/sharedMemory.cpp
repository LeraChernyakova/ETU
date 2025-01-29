#include "sharedMemory.h"

void* getSharedMemoryPointer() {
    const size_t size = 1024;   // Объём сегмента памяти
    const key_t key = 1;        // Ключ сегмента памяти

    int id = shmget(key, size, 0644 | IPC_CREAT);
    if (id == -1) {
        throw std::runtime_error("Error! Cannot find suitable memory segment.");
    }
    void* pointer = shmat(id, nullptr, 0);
    if (pointer == (void*)-1) {
        throw std::runtime_error("Error! Cannot attach memory segment.");
    }

    return pointer;
}

void writeToSharedPointer(int* sharedPointer, std::vector<int> buffer) {
    int size = buffer.size();

    *sharedPointer = size;
    sharedPointer++;
    for (int i = 0; i < size; i++) {
        *sharedPointer = buffer[i];
        sharedPointer++;
    }

    return;
}

std::vector<int> readFromSharedPointer(int* sharedPointer) {
    std::vector<int> buffer;
    int size = *sharedPointer;
    sharedPointer++;

    for(int i = 0; i < size; i++) {
        buffer.push_back(*sharedPointer);
        sharedPointer++;
    }

    return buffer;
}
