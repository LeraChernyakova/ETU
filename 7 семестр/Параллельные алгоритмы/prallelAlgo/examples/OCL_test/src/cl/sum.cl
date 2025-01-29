#define WORK_GROUP_SIZE 128

//#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable


__kernel void sum(__global const int* input, int n,
                  volatile __global int* res){

    int localID = get_local_id(0);
    int globalID = get_global_id(0);

    __local int input_local[WORK_GROUP_SIZE];
    input_local[localID] = input[globalID];

    barrier(CLK_LOCAL_MEM_FENCE);

    for (int n_val = WORK_GROUP_SIZE; n_val>1; n_val/=2){
        if(2*localID < n_val){
            input_local[localID]+=input_local[localID+n_val/2];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    if(localID==0){
        atom_add(res, input_local[localID]);
    }
    
}