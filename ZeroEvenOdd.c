#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t locks[3];
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    for (int i = 0; i < 3; i++) {
        pthread_mutex_init(&obj->locks[i], NULL);
        pthread_mutex_lock(&obj->locks[i]);
    }
    pthread_mutex_ulock(&obj->locks[2]);
    return obj;
}

void zero(ZeroEvenOdd* obj) {
    for (int i = 1; i <= obj->n; i++) {
        pthread_mutex_lock(&obj->locks[2]);
        printNumber(0);
        pthread_mutex_unlock(&obj->locks[i % 2]);
    }
}

void even(ZeroEvenOdd* obj) {
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->locks[0]);
        printNumber(i);
        pthread_mutex_unlock(&obj->locks[2]);
    }
}

void odd(ZeroEvenOdd* obj) {
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->locks[1]);
        printNumber(i);
        pthread_mutex_unlock(&obj->locks[2]);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    for (int i = 0; i < 3; i++) {
        pthread_mutex_destroy(&obj->locks[i]);
    }
    free(obj);
}
