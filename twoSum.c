#include <stdlib.h>
#include <stdbool.h>

#define TABLE_CAPACITY 100003

typedef struct {
    int key;
    int value;
} TableEntry;

typedef TableEntry** Table;

Table table_init() {
    return calloc(sizeof(TableEntry*), TABLE_CAPACITY);
}

int* table_get(Table table, int key) {
    int hash = (key % TABLE_CAPACITY + TABLE_CAPACITY) % TABLE_CAPACITY;
    int* value = NULL;
    while (table[hash] != NULL) {
        if (table[hash]->key == key) {
            value = malloc(sizeof(int));
            *value = table[hash]->value;
        }
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    return value;
}

void table_put(Table table, int key, int value) {
    int hash = (key % TABLE_CAPACITY + TABLE_CAPACITY) % TABLE_CAPACITY;
    while (table[hash] != NULL) {
        hash = (hash + 1) % TABLE_CAPACITY;
    }
    table[hash] = malloc(sizeof(TableEntry));
    TableEntry entry = {key, value};
    *table[hash] = entry;
}

void table_free(Table table) {
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        free(table[i]);
    }
    free(table);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Table idxOfNums = table_init();
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int* j = table_get(idxOfNums, target - num);
        if (j == NULL) {
            table_put(idxOfNums, num, i);
        } else {
            *returnSize = 2;
            int* indices = malloc(sizeof(int) * *returnSize);
            indices[0] = *j;
            indices[1] = i;
            free(j);
            return indices;
        }
    }
    table_free(idxOfNums);
    exit(EXIT_FAILURE);
}
