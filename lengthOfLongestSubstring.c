#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_CAPACITY 128

#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
    int* data[TABLE_CAPACITY];
    int size;
} Table;

Table* tableInit() {
    Table* self = calloc(1, sizeof(Table));
    return self;
}

bool tableHas(Table* self, char key) {
    return self->data[key] != NULL;
}

int tableGet(Table* self, char key) {
    return *self->data[key];
}

void tablePut(Table* self, char key, int value) {
    self->data[key] = malloc(sizeof(int));
    *self->data[key] = value;
    self->size += 1;
}

int tableSize(Table* self) {
    return self->size;
}

void tableDel(Table* self, char key) {
    free(self->data[key]);
    self->data[key] = NULL;
    self->size -= 1;
}

void tableFree(Table* self) {
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        free(self->data[i]);
    }
}

int lengthOfLongestSubstring(char* s) {
    Table* idxOfChars = tableInit();
    int maxLen = 0;
    int headIdx = 0;
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        if (tableHas(idxOfChars, c)) {
            int preCIdx = tableGet(idxOfChars, c);
            for (int j = headIdx; j <= preCIdx; j++) {
                tableDel(idxOfChars, s[j]);
            }
            headIdx = preCIdx + 1;
        }
        tablePut(idxOfChars, c, i);
        maxLen = max(maxLen, tableSize(idxOfChars));
    }
    tableFree(idxOfChars);
    return maxLen;
}
