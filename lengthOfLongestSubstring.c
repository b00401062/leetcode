#include <stdlib.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
    int** data;
    int size;
} Table;

#define TABLE_CAPACITY 23

int toHash(char c) {
    return c - 'a';
}

Table table_init() {
    Table table = {
        .data = calloc(sizeof(int*), TABLE_CAPACITY),
        .size = 0
    };
    return table;
}

int* table_get(Table table, char key) {
    int hash = toHash(key);
    return table.data[hash];
}

void table_put(Table table, char key, int value) {
    int hash = toHash(key);
    table.data[hash] = malloc(sizeof(int));
    table.data[hash]
    table.size += 1;
}

int table_size(Table table) {
    return table.size;
}

void table_del(Table table, char key) {
    int hash = toHash(key);
    free(table.data[hash]);
    table.data[hash] = NULL;
    table.size -= 1;
}

void table_free(Table table) {
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        free(table.data[i]);
    }
    free(table.data);
}

void table_show(Table table) {
    printf("%d\n", table.size);
}

int lengthOfLongestSubstring(char* s) {
    Table idxOfChars = table_init();
    int maxLen = 0;
    int headIdx = 0;
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        int* preCIdx = table_get(idxOfChars, c);
        if (preCIdx != NULL) {
            for (int j = headIdx; j < *preCIdx; j++) {
                table_del(idxOfChars, s[j]);
            }
            headIdx = *preCIdx + 1;
        }
        table_put(idxOfChars, c, i);
        maxLen = MAX(maxLen, table_size(idxOfChars));
        table_show(idxOfChars);
    }
    table_free(idxOfChars);
    return maxLen;
}

int main() {
    printf("%d\n", lengthOfLongestSubstring("bbbbbb"));
}
