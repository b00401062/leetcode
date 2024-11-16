#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t hLock;
    pthread_mutex_t oLock;
    pthread_barrier_t barrier;
} H2O;

H2O* h2oCreate() {
    H2O* obj = malloc(sizeof(H2O));
    sem_init(&obj->hLock, 0, 2);
    pthread_mutex_init(&obj->oLock, NULL);
    pthread_barrier_init(&obj->barrier, NULL, 3);
    return obj;
}

void hydrogen(H2O* obj) {
    sem_wait(&obj->hLock);
    releaseHydrogen();
    pthread_barrier_wait(&obj->barrier);
    sem_post(&obj->hLock);
}

void oxygen(H2O* obj) {
    pthread_mutex_lock(&obj->oLock);
    releaseOxygen();
    pthread_barrier_wait(&obj->barrier);
    pthread_mutex_unlock(&obj->oLock);
}

void h2oFree(H2O* obj) {
    sem_destroy(&obj->hLock);
    pthread_mutex_destroy(&obj->oLock);
    pthread_barrier_destroy(&obj->barrier);
    free(obj);
}
