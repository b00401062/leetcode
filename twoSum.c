#include<stdlib.h>
#include<stdbool.h>

#define HASHTABLECAPACITY 100003

typedef struct {
    int key;
    int value;
} HashTableEntry;

typedef HashTableEntry** HashTable;

HashTable table_init() {
    return calloc(sizeof(HashTableEntry*), HASHTABLECAPACITY);
}

int* table_get(HashTable table, int key) {
    int hash = (key % HASHTABLECAPACITY + HASHTABLECAPACITY) % HASHTABLECAPACITY;
    int* value = NULL;
    while (table[hash] != NULL) {
        if (table[hash]->key == key) {
            value = malloc(sizeof(int));
            *value = table[hash]->value;
        }
        hash = (hash + 1) % HASHTABLECAPACITY;
    }
    return value;
}

void table_put(HashTable table, int key, int value) {
    int hash = (key % HASHTABLECAPACITY + HASHTABLECAPACITY) % HASHTABLECAPACITY;
    while (table[hash] != NULL) {
        hash = (hash + 1) % HASHTABLECAPACITY;
    }
    table[hash] = malloc(sizeof(HashTableEntry));
    table[hash]->key = key;
    table[hash]->value = value;
}

void table_free(HashTable table) {
    for (int i = 0; i < HASHTABLECAPACITY; i++) {
        free(table[i]);
    }
    free(table);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashTable idxOfNums = table_init();
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
