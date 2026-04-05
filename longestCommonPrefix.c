#include <stdlib.h>

char* reduceToCommonPrefix(char* s1, char* s2) {
    assert(s1 != NULL && s2 != NULL);
    char* prefix = (char*) calloc(sizeof(char), 201);
    for (int i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++) {
        prefix[i] = s1[i];
    }
    return prefix;
}

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) return "";
    if (strsSize == 1) return strs[0];
    char* prefix = strs[0];
    for (int i = 1; i < strsSize; i++) {
        char* ret = reduceToCommonPrefix(prefix, strs[i]);
        if (prefix != NULL) free(prefix);
        prefix = ret;
    }
    return prefix;
}
