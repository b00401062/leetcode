#include <limits.h>

int myAtoi(char* s) {
    while (*s == ' ') {
        s++;
    }
    int sign = *s == '-' ? -1 : 1;
    if (*s == '-' || *s == '+') {
        s++;
    }
    long result = 0;
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        if (result > INT_MAX) {
            return sign == 1 ? INT_MAX : INT_MIN;
        }
        s++;
    }
    return (int)(sign * result);
}
