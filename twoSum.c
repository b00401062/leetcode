#include <stdlib.h>
#include <stdbool.h>

#define TABLE_CAPACITY 100003

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

bool table_has(Table* self, int key) {
    int hash = (key % TABLE_CAPACITY + TABLE_CAPACITY) % TABLE_CAPACITY;
    while (self->data[hash] != NULL) {
        if (self->data[hash]->key == key) {
            return true;
        }
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    return false;
}

int table_get(Table* self, int key) {
    int hash = (key % TABLE_CAPACITY + TABLE_CAPACITY) % TABLE_CAPACITY;
    while (self->data[hash] != NULL) {
        if (self->data[hash]->key == key) {
            return self->data[hash]->value;
        }
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    exit(EXIT_FAILURE);
}

void table_put(Table* self, int key, int value) {
    int hash = (key % TABLE_CAPACITY + TABLE_CAPACITY) % TABLE_CAPACITY;
    while (self->data[hash] != NULL) {
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    self->data[hash] = malloc(sizeof(TableEntry));
    TableEntry entry = {key, value};
    *self->data[hash] = entry;
}

void table_free(Table* self) {
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        free(self->data[i]);
    }
    free(self);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Table* idxOfNums = table_init();
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        if (table_has(idxOfNums, target - num)) {
            *returnSize = 2;
            int* indices = malloc(sizeof(int) * *returnSize);
            indices[0] = table_get(idxOfNums, target - num);
            indices[1] = i;
            return indices;
        } else {
            table_put(idxOfNums, num, i);
        }
    }
    table_free(idxOfNums);
    exit(EXIT_FAILURE);
}
