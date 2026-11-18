int* kmpTable(char* needle) {
    int len = strlen(needle);
    int* kmp = (int*) malloc(sizeof(int) * len);
    kmp[0] = 0;
    int j = 0;
    for (int i = 1; i < len; i++) {
        while (j > 0 && needle[i] != needle[j]) {
            j = kmp[j - 1];
        }
        if (needle[i] == needle[j]) {
            j++;
        }
        kmp[i] = j;
    }
    return kmp;
}

int strStr(char* haystack, char* needle) {
    if (!*needle) return 0;
    int* kmp = kmpTable(needle);
    int j = 0;
    for (int i = 0; haystack[i]; i++) {
        while (j > 0 && haystack[i] != needle[j]) {
            j = kmp[j - 1];
        }
        if (haystack[i] == needle[j]) {
            j++;
        }
        if (j == strlen(needle)) {
            free(kmp);
            return i - j + 1;
        }
    }
    free(kmp);
    return -1;
}
