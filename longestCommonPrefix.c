#include <assert.h>
#include <stdlib.h>

char* reduceToCommonPrefix(char* s1, char* s2) {
    assert(s1 != NULL || s2 != NULL);
    if (s1 == NULL) s1 = s2;
    if (s2 == NULL) s2 = s1;
    char* prefix = (char*) malloc(sizeof(char) * 201);
    prefix[0] = '\0';
    for (int i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++) {
        prefix[i] = s1[i];
        prefix[i + 1] = '\0';
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
