#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <sys/mman.h>

#define THREADS_AMOUNT 10
#define OPERATIONS_AMOUNT 100000
#define OPERATIONS_CHANGES THREADS_AMOUNT*OPERATIONS_AMOUNT

int *free_index;
int *shared_memory;

/*
 * РџР°РјСЏС‚СЊ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РёРЅРґРµРєСЃРѕРІ РїСЂРѕС†РµСЃСЃРѕРІ, СЃРјРµРЅСЏСЋС‰РёС… РґСЂСѓРі РґСЂСѓРіР°
 */
int *index_proc;
int *shared_memory_proc;

/*
 * Р¤СѓРЅРєС†РёСЏ СЃРѕР·РґР°РЅРёСЏ СЂР°Р·РґРµР»СЏРµРјРѕР№ РїР°РјСЏС‚Рё СЃ РїРѕРјРѕС‰СЊСЋ mmap
 */
void* create_shared_memory(size_t size) 
{   
    int protection = PROT_READ | PROT_WRITE;
    
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL, size, protection, visibility, -1, 0);
}

void *thread_fifo_schedule(void *attr)
{
    for (int i = 0; i < OPERATIONS_AMOUNT; i++)
    {
        /*
         * Р•СЃР»Рё С‚РµРєСѓС‰РёР№ РІС‹РїРѕР»РЅСЏСЋС‰РёР№СЃСЏ РїСЂРѕС†РµСЃСЃ СЃРјРµРЅРёР»СЃСЏ, РЅРµРѕР±С…РѕРґРёРјРѕ Р·Р°РЅРµСЃС‚Рё СЃРІРµРґРµРЅРёСЏ РѕР± СЌС‚РѕРј РІ РїР°РјСЏС‚СЊ
         */
        if (shared_memory_proc[(*index_proc) - 1] != *((int*)attr))
        {
            shared_memory_proc[(*index_proc)++] = *((int*)attr);
        } 
    }
    /*
     * РЈРєР°Р·С‹РІР°РµРј, С‡С‚Рѕ РїСЂРѕС†РµСЃСЃ Р·Р°РІРµСЂС€РёР»СЃСЏ
     */
    shared_memory[(*free_index)++] = *((int*)attr);
}

void *thread_rr_schedule(void *attr)
{
    for (int i = 0; i < OPERATIONS_AMOUNT; i++)
    {
        /*
         * Р•СЃР»Рё С‚РµРєСѓС‰РёР№ РІС‹РїРѕР»РЅСЏСЋС‰РёР№СЃСЏ РїСЂРѕС†РµСЃСЃ СЃРјРµРЅРёР»СЃСЏ, РЅРµРѕР±С…РѕРґРёРјРѕ Р·Р°РЅРµСЃС‚Рё СЃРІРµРґРµРЅРёСЏ РѕР± СЌС‚РѕРј РІ РїР°РјСЏС‚СЊ
         */
        if (shared_memory_proc[(*index_proc) - 1] != *((int*)attr))
        {
            shared_memory_proc[(*index_proc)++] = *((int*)attr);
        } 
    }
    /*
     * РЈРєР°Р·С‹РІР°РµРј, С‡С‚Рѕ РїСЂРѕС†РµСЃСЃ Р·Р°РІРµСЂС€РёР»СЃСЏ
     */
    shared_memory[(*free_index)++] = *((int*)attr);
}

int main()
{
    free_index = create_shared_memory(sizeof(int));
    index_proc = create_shared_memory(sizeof(int));
    *free_index = 0;
    *index_proc = 1;
    shared_memory = create_shared_memory(sizeof(int) * THREADS_AMOUNT);
    shared_memory_proc = create_shared_memory(sizeof(int) * OPERATIONS_CHANGES);

    /*
     * РРЅРёС†РёР°Р»РёР·РёСЂСѓРµРј РІС‹РґРµР»РµРЅРЅСѓСЋ РїР°РјСЏС‚СЊ
     */
    for (int i = 0; i < THREADS_AMOUNT; i++)
    {
        shared_memory[i] = -1;
    }

    for (int i = 0; i < OPERATIONS_CHANGES; i++)
    {
        shared_memory_proc[i] = -1;
    }
    pthread_t threads[THREADS_AMOUNT];
    pthread_attr_t threads_attrs[THREADS_AMOUNT];
    struct sched_param params[THREADS_AMOUNT];
    int priorityFIFO = 50;
    int priorityRR = 50;
    int thread_id[THREADS_AMOUNT];
    for (int i = 0; i < THREADS_AMOUNT; i++)
    {
        pthread_attr_init(&threads_attrs[i]);

        pthread_attr_setinheritsched(&threads_attrs[i], PTHREAD_EXPLICIT_SCHED);
        if (i % 2 == 0)
        {
            params[i].sched_priority = priorityRR;
            pthread_attr_setschedpolicy(&threads_attrs[i], SCHED_RR);
        }
        else
        {
            params[i].sched_priority = priorityFIFO;
            pthread_attr_setschedpolicy(&threads_attrs[i], SCHED_FIFO);
        }
        pthread_attr_setschedparam(&threads_attrs[i], &params[i]);
        thread_id[i] = i;
        if(pthread_create(&threads[i], &threads_attrs[i], (i % 2 == 0) ? thread_rr_schedule : thread_fifo_schedule, &thread_id[i]))
        {
            fprintf(stderr, "Error creating thread %d\n", i);
        }
    }
    for (int i = 0; i < THREADS_AMOUNT; i++) 
    {
        pthread_join(threads[i], NULL);
    }
    /*
     * Р’С‹РІРѕРґРёРј РїРѕР»СѓС‡РµРЅРЅСѓСЋ РЅС„РѕСЂРјР°С†РёСЋ
     */
    for (int i = 1; i < OPERATIONS_CHANGES; i++)
    {
        if (shared_memory_proc[i] == -1)
            break;
        printf("%d ", shared_memory_proc[i]);
    }
    for (int i = 0; i < THREADS_AMOUNT; i++)
    {
        printf("%s thread no %d complited\n", (shared_memory[i] % 2 == 0) ? "RR" : "FIFO", shared_memory[i]);
    }

    printf("All threads finished\n");

    return 0;
}
