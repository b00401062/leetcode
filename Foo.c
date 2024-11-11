#include <stdlib.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t lock1;
    pthread_mutex_t lock2;
} Foo;

Foo* fooCreate() {
    Foo* obj = malloc(sizeof(Foo));
    pthread_mutex_init(&obj->lock1, NULL);
    pthread_mutex_init(&obj->lock2, NULL);
    pthread_mutex_lock(&obj->lock1);
    pthread_mutex_lock(&obj->lock2);
    return obj;
}

void first(Foo* obj) {
    printFirst();
    pthread_mutex_unlock(&obj->lock1);
}

void second(Foo* obj) {
    pthread_mutex_lock(&obj->lock1);
    printSecond();
    pthread_mutex_unlock(&obj->lock2);
}

void third(Foo* obj) {
    pthread_mutex_lock(&obj->lock2);
    printThird();
}

void fooFree(Foo* obj) {
    pthread_mutex_destroy(&obj->lock1);
    pthread_mutex_destroy(&obj->lock2);
    free(obj);
}
