#pragma once
#include <iostream>
#include "MultipleProcesses.h"
#include "MultipleThreads.h"
#include "MoreMultipleThreads.h"

#define TASK_INDEX 3

int lab1() {
    switch (TASK_INDEX) {
        case 1: MultipleProcesses(); break;
        case 2: MultipleThreads(); break;
        case 3: MoreMultipleThreads(); break;
        default: log("Choose correct task number");
    }
    return 0;
}
