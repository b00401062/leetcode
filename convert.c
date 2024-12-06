#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    if (numRows == 1) {
        return s;
    }
    int sLen = strlen(s);
    char* res = malloc(sLen + 1);
    int j = 0;
    for (int r = 0; r < numRows; r++) {
        int jumps[2] = { (numRows - r - 1) * 2, r * 2 };
        int i = r;
        int k = 0;
        while (i < sLen) {
            res[j++] = s[i];
            if (jumps[k] == 0) {
                k = 1 - k;
            }
            i += jumps[k];
            k = 1 - k;
        }
    }
    res[sLen] = '\0';
    return res;
}
