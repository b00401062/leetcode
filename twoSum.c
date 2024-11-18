#include <stdlib.h>
#include <stdbool.h>

#define TABLE_CAPACITY 100003

#define hash(key) (((key) % TABLE_CAPACITY + TABLE_CAPACITY) % TABLE_CAPACITY)

typedef struct {
    int key;
    int value;
} TableEntry;

typedef struct {
    TableEntry* data[TABLE_CAPACITY];
} Table;

Table* table_init() {
    Table* self = calloc(1, sizeof(Table));
    return self;
}

bool tableHas(Table* self, int key) {
    int hash = hash(key);
    while (self->data[hash] != NULL) {
        if (self->data[hash]->key == key) {
            return true;
        }
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    return false;
}

int tableGet(Table* self, int key) {
    int hash = hash(key);
    while (self->data[hash] != NULL) {
        if (self->data[hash]->key == key) {
            return self->data[hash]->value;
        }
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    exit(EXIT_FAILURE);
}

void tablePut(Table* self, int key, int value) {
    int hash = hash(key);
    while (self->data[hash] != NULL) {
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    self->data[hash] = malloc(sizeof(TableEntry));
    TableEntry entry = {key, value};
    *self->data[hash] = entry;
}

void tableFree(Table* self) {
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        free(self->data[i]);
    }
    free(self);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 0;
    int* indices = NULL;
    Table* idxOfNums = table_init();
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        if (tableHas(idxOfNums, target - num)) {
            *returnSize = 2;
            indices = malloc(sizeof(int) * *returnSize);
            indices[0] = tableGet(idxOfNums, target - num);
            indices[1] = i;
            break;
        } else {
            tablePut(idxOfNums, num, i);
        }
    }
    tableFree(idxOfNums);
    return indices;
}
