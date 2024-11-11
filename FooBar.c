#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t barLock;
    pthread_mutex_t fooLock;
} FooBar;

FooBar* fooBarCreate(int n) {
    FooBar* obj = malloc(sizeof(FooBar));
    obj->n = n;
    pthread_mutex_init(&obj->barLock, NULL);
    pthread_mutex_init(&obj->fooLock, NULL);
    pthread_mutex_lock(&obj->barLock);
    return obj;
}

void foo(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->fooLock);
        printFoo();
        pthread_mutex_unlock(&obj->barLock);
    }
}

void bar(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->barLock);
        printBar();
        pthread_mutex_unlock(&obj->fooLock);
    }
}

void fooBarFree(FooBar* obj) {
    pthread_mutex_destroy(&obj->barLock);
    pthread_mutex_destroy(&obj->fooLock);
    free(obj);
}
