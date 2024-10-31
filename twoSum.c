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

bool table_has(HashTable table, int key) {
    int hash = (key % HASHTABLECAPACITY + HASHTABLECAPACITY) % HASHTABLECAPACITY;
    while (table[hash] != NULL) {
        if (table[hash]->key == key) {
            return true;
        }
        hash = (hash + 1) % HASHTABLECAPACITY;
    }
    return false;
}

int table_get(HashTable table, int key) {
    int hash = (key % HASHTABLECAPACITY + HASHTABLECAPACITY) % HASHTABLECAPACITY;
    while (table[hash] != NULL) {
        if (table[hash]->key == key) {
            return table[hash]->value;
        }
        hash = (hash + 1) % HASHTABLECAPACITY;
    }
    exit(EXIT_FAILURE);
}

void table_insert(HashTable table, int key, int value) {
    int hash = (key % HASHTABLECAPACITY + HASHTABLECAPACITY) % HASHTABLECAPACITY;
    while (table[hash] != NULL) {
        hash = (hash + 1) % HASHTABLECAPACITY;
    }
    table[hash] = calloc(sizeof(HashTableEntry), 1);
    table[hash]->key = key;
    table[hash]->value = value;
}

void table_destroy(HashTable table) {
    for (int i = 0; i < HASHTABLECAPACITY; i++) {
        free(table[i]);
    }
    free(table);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashTable idxOfNums = table_init();
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        if (table_has(idxOfNums, target - num)) {
            int* indices = (int*) calloc(sizeof(int), 2);
            indices[0] = table_get(idxOfNums, target - num);
            indices[1] = i;
            *returnSize = 2;
            return indices;
        } else {
            table_insert(idxOfNums, num, i);
        }
    }
    table_destroy(idxOfNums);
    exit(EXIT_FAILURE);
}
