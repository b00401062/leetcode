#include <stdbool.h>

bool isMatch(char* s, char* p) {
    if (s[0] != '\0' && p[0] != '\0' && (s[0] == p[0] || p[0] == '.')) {
        if (p[1] == '*') {
            return isMatch(s, p + 2) || isMatch(s + 1, p);
        } else {
            return isMatch(s + 1, p + 1);
        }
    } else if (p[0] != '\0' && p[1] == '*') {
        return isMatch(s, p + 2);
    } else {
        return s[0] == '\0' && p[0] == '\0';
    }
}
