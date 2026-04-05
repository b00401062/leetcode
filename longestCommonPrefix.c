#include <assert.h>
#include <stdlib.h>
#include <string.h>

char* reduceToCommonPrefix(char* s1, char* s2) {
    assert(s1 != NULL || s2 != NULL);
    char* prefix = (char*) calloc(sizeof(char), 201);
    if (s1 == NULL || s2 == NULL) {
        strcpy(prefix, s1 ? s1 : s2);
        return prefix;
    }
    for (int i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++) {
        prefix[i] = s1[i];
    }
    return prefix;
}

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) return "";
    char* prefix = NULL;
    for (int i = 0; i < strsSize; i++) {
        char* ret = reduceToCommonPrefix(prefix, strs[i]);
        free(prefix);
        prefix = ret;
    }
    return prefix;
}
