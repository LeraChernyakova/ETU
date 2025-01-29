#include "common_funcs.h"
#include<thread>
#include <future>



void matrixMult(promise<vector<vector<int>>>&& prom, vector<vector<int>>& m1, vector<vector<int>>& m2);