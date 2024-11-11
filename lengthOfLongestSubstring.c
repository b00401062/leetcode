#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_CAPACITY 128

#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
    int* data[TABLE_CAPACITY];
    int size;
} Table;

Table* table_init() {
    Table* self = malloc(sizeof(Table));
    self->size = 0;
    memset(self->data, 0, TABLE_CAPACITY * sizeof(int*));
    return self;
}

bool table_has(Table* self, char key) {
    return self->data[key] != NULL;
}

int table_get(Table* self, char key) {
    return *self->data[key];
}

void table_put(Table* self, char key, int value) {
    self->data[key] = malloc(sizeof(int));
    *self->data[key] = value;
    self->size += 1;
}

int table_size(Table* self) {
    return self->size;
}

void table_del(Table* self, char key) {
    free(self->data[key]);
    self->data[key] = NULL;
    self->size -= 1;
}

void table_free(Table* self) {
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        free(self->data[i]);
    }
}

int lengthOfLongestSubstring(char* s) {
    Table* idxOfChars = table_init();
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
        maxLen = max(maxLen, table_size(idxOfChars));
    }
    table_free(idxOfChars);
    return maxLen;
}
