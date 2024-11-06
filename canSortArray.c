#include <stdbool.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

bool canSortArray(int* nums, int numsSize) {
    int pMax = 0, cMin = 0, cMax = 0;
    int pCnt = 0;
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int cCnt = __builtin_popcount(num);
        if (pCnt == cCnt) {
            cMin = min(cMin, num);
            cMax = max(cMax, num);
        } else {
            pCnt = cCnt;
            pMax = cMax;
            cMin = cMax = num;
        }
        if (cMin < pMax) {
            return false;
        }
    }
    return true;
}
