#include <stdbool.h>

int reverse(int x) {
    long r = 0;
    while (x > 0) {
        int d = x % 10;
        r = r * 10 + d;
        x /= 10;
    }
    return (int) r;
}

bool isPalindrome(int x) {
    return x >= 0 && x == reverse(x);
}
