#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool rotateString(char* s, char* goal) {
    if (strlen(s) != strlen(goal)) {
        return false;
    }
    int sLen = strlen(s);
    int tableSize = 2 * sLen + 1;
    int table[tableSize][tableSize];
    memset(table, 0, sizeof(table[0][0]) * tableSize * tableSize);
    for (int i = 1; i < tableSize; i++) {
        char cI = s[(i - 1) % sLen];
        for (int j = 1; j < tableSize; j++) {
            char cJ = goal[(j - 1) % sLen];
            table[i][j] = cI == cJ ? table[i - 1][j - 1] + 1 : 0;
            if (table[i][j] >= sLen) {
                return true;
            }
        }
    }
    return false;
}
