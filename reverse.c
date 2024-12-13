#include <limits.h>

int reverse(int x){
    int y = 0;
    while (x != 0) {
        int r = x % 10;
        x /= 10;
        if (
            y > INT_MAX / 10 ||
            y == INT_MAX / 10 && r > 7 ||
            y < INT_MIN / 10 ||
            y == INT_MIN / 10 && r < -8
        ) return 0;
        y = y * 10 + r;
    }
    return y;
}
