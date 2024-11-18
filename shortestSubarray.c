#include <limits.h>
#include <stdlib.h>

#define DEQUE_CAPACITY 100000

#define min(a, b) ({\
    __typeof__(a) _a = (a);\
    __typeof__(b) _b = (b);\
    _a < _b ? _a : _b;\
})

typedef struct {
    long prefixSum;
    int endID;
} DequeEntry;

typedef struct {
    DequeEntry* data[DEQUE_CAPACITY];
    int size;
    int headID;
    int tailID;
} Deque;

Deque* dequeInit() {
    Deque* self = calloc(sizeof(Deque), 1);
    return self;
}

DequeEntry dequePeekFront(Deque* self) {
    return *self->data[self->headID];
}

DequeEntry dequePeekBack(Deque* self) {
    return *self->data[self->tailID - 1];
}

void dequePushBack(Deque* self, DequeEntry entry) {
    self->data[self->tailID] = malloc(sizeof(DequeEntry));
    *self->data[self->tailID] = entry;
    self->tailID++;
    self->size++;
}

DequeEntry dequePopFront(Deque* self) {
    DequeEntry entry = *self->data[self->headID];
    free(self->data[self->headID]);
    self->data[self->headID] = NULL;
    self->headID++;
    self->size--;
    return entry;
}

DequeEntry dequePopBack(Deque* self) {
    DequeEntry entry = *self->data[self->tailID - 1];
    free(self->data[self->tailID - 1]);
    self->data[self->tailID - 1] = NULL;
    self->tailID--;
    self->size--;
    return entry;
}

void dequeFree(Deque* self) {
    for (int i = self->headID; i < self->tailID; i++) {
        free(self->data[i]);
    }
    free(self);
}

int shortestSubarray(int* nums, int numsSize, int k) {
    int res = INT_MAX;
    long curSum = 0;
    Deque* deque = dequeInit();
    for (int i = 0; i < numsSize; i++) {
        curSum += nums[i];
        if (curSum >= k) {
            res = min(res, i + 1);
        }
        while (deque->size > 0 && curSum - dequePeekFront(deque).prefixSum >= k) {
            res =  min(res, i - dequePopFront(deque).endID);
        }
        while (deque->size > 0 && dequePeekBack(deque).prefixSum >= curSum) {
            dequePopBack(deque);
        }
        DequeEntry entry = {curSum, i};
        dequePushBack(deque, entry);
    }
    dequeFree(deque);
    return res == INT_MAX ? -1 : res;
}
