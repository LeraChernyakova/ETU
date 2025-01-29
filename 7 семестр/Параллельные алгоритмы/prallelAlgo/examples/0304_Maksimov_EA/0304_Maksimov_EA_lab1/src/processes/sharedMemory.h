#pragma once

#include <iostream>
#include <sys/shm.h>
#include <vector>

void* getSharedMemoryPointer();
void writeToSharedPointer(int* sharedPointer, std::vector<int> buffer);
std::vector<int> readFromSharedPointer(int* sharedPointer);
