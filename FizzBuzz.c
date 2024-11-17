#include <stdbool.h>
#include <pthread.h>

#define lockID(i) (\
    ((i) % 3 == 0) +\
    ((i) % 5 == 0 ? 2 : 0)\
)

typedef struct {
    int n;
    int i;
    pthread_mutex_t locks[4];
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->i = 1;
    for (int i = 0; i < 4; i++) {
        pthread_mutex_init(&obj->locks[i], NULL);
        pthread_mutex_lock(&obj->locks[i]);
    }
    pthread_mutex_unlock(&obj->locks[lockID(1)]);
    return obj;
}

void unlockNext(FizzBuzz* obj) {
    if (++obj->i <= obj->n) {
        pthread_mutex_unlock(&obj->locks[lockID(obj->i)]);
    } else for (int i = 0; i < 4; i++) {
        pthread_mutex_unlock(&obj->locks[i]);
    }
}

void fizz(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->locks[1]);
        if (obj->i > obj->n) break;
        printFizz();
        unlockNext(obj);
    }
}

void buzz(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->locks[2]);
        if (obj->i > obj->n) break;
        printBuzz();
        unlockNext(obj);
    }
}

void fizzbuzz(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->locks[3]);
        if (obj->i > obj->n) break;
        printFizzBuzz();
        unlockNext(obj);
    }
}

void number(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->locks[0]);
        if (obj->i > obj->n) break;
        printNumber(obj->i);
        unlockNext(obj);
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    for (int i = 0; i < 4; i++) {
        pthread_mutex_destroy(&obj->locks[i]);
    }
    free(obj);
}
