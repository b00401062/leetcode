#include <stdlib.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex1;
    pthread_mutex_t mutex2;
} Foo;

Foo* fooCreate() {
    Foo* obj = malloc(sizeof(Foo));
    pthread_mutex_init(&obj->mutex1, NULL);
    pthread_mutex_init(&obj->mutex2, NULL);
    pthread_mutex_lock(&obj->mutex1);
    pthread_mutex_lock(&obj->mutex2);
    return obj;
}

void first(Foo* obj) {
    printFirst();
    pthread_mutex_unlock(&obj->mutex1);
}

void second(Foo* obj) {
    pthread_mutex_lock(&obj->mutex1);
    printSecond();
    pthread_mutex_unlock(&obj->mutex2);
}

void third(Foo* obj) {
    pthread_mutex_lock(&obj->mutex2);
    printThird();
}

void fooFree(Foo* obj) {
    pthread_mutex_destroy(&obj->mutex1);
    pthread_mutex_destroy(&obj->mutex2);
    free(obj);
}
