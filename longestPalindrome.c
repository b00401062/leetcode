#include <string.h>
#include <stdlib.h>

#define min(a, b) ({\
    __typeof__(a) _a = (a);\
    __typeof__(b) _b = (b);\
    _a < _b ? _a : _b;\
})

#define max(a, b) ({\
    __typeof__(a) _a = (a);\
    __typeof__(b) _b = (b);\
    _a > _b ? _a : _b;\
})

char* strJoin(char* s, char d) {
    int sLen = strlen(s);
    char* res = malloc(sLen * 2 + 2);
    for (int i = 0; i < sLen; i++) {
        res[i * 2] = d;
        res[i * 2 + 1] = s[i];
    }
    res[sLen * 2] = d;
    res[sLen * 2 + 1] = '\0';
    return res;
}

char* subsequence(char* s, int lt, int rt, int jump) {
    int resLen = (rt - lt - 1) / jump + 1;
    char* res = malloc(resLen + 1);
    for (int i = lt, j = 0; i < rt; i += jump, j++) {
        res[j] = s[i];
    }
    res[resLen] = '\0';
    return res;
}

int argmax(int* a, int size) {
    int arg = 0;
    int max = a[0];
    for (int i = 1; i < size; i++) {
        if (a[i] > max) {
            arg = i;
            max = a[i];
        }
    }
    return arg;
}

char* longestPalindrome(char* s) {
    if (strlen(s) <= 1) {
        return s;
    }
    char* js = strJoin(s, '#');
    int jsLen = strlen(js);
    int spans[jsLen];
    int ct = 0, rt = 0;
    memset(spans, 0, sizeof(spans));
    for (int i = 1; i < jsLen; i++) {
        if (i <= rt) {
            spans[i] = min(rt - i, spans[2 * ct - i]);
        }
        while (
            i - spans[i] - 1 >= 0 &&
            i + spans[i] + 1 < jsLen &&
            js[i - spans[i] - 1] == js[i + spans[i] + 1]
        ) {
            spans[i]++;
        }
        if (i + spans[i] > rt) {
            ct = i;
            rt = i + spans[i];
        }
    }
    int mCt = argmax(spans, jsLen);
    int mLt = mCt - spans[mCt];
    int mRt = mCt + spans[mCt];
    char* res = subsequence(js, mLt + 1, mRt, 2);
    free(js);
    return res;
}
