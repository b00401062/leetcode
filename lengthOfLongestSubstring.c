#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_CAPACITY 128

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
    int** data;
    int* size;
} Table;

int toHash(char c) {
    return c - '\0';
}

Table table_init() {
    Table table = {
        .data = calloc(sizeof(int*), TABLE_CAPACITY),
        .size = calloc(sizeof(int), 1)
    };
    return table;
}

bool table_has(Table table, char key) {
    int hash = toHash(key);
    return table.data[hash] != NULL;
}

int table_get(Table table, char key) {
    int hash = toHash(key);
    return *table.data[hash];
}

void table_put(Table table, char key, int value) {
    int hash = toHash(key);
    table.data[hash] = malloc(sizeof(int));
    *table.data[hash] = value;
    *table.size += 1;
}

int table_size(Table table) {
    return *table.size;
}

void table_del(Table table, char key) {
    int hash = toHash(key);
    free(table.data[hash]);
    table.data[hash] = NULL;
    *table.size -= 1;
}

void table_free(Table table) {
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        free(table.data[i]);
    }
    free(table.data);
}

int lengthOfLongestSubstring(char* s) {
    Table idxOfChars = table_init();
    int maxLen = 0;
    int headIdx = 0;
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        if (table_has(idxOfChars, c)) {
            int preCIdx = table_get(idxOfChars, c);
            for (int j = headIdx; j <= preCIdx; j++) {
                table_del(idxOfChars, s[j]);
            }
            headIdx = preCIdx + 1;
        }
        table_put(idxOfChars, c, i);
        maxLen = MAX(maxLen, table_size(idxOfChars));
    }
    table_free(idxOfChars);
    return maxLen;
}
