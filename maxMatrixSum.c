#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define min(a, b) ({\
    __typeof__(a) _a = (a);\
    __typeof__(b) _b = (b);\
    _a < _b ? _a : _b;\
})

long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    long long sum = 0;
    int minAbsNum = INT_MAX;
    int negNumCnt = 0;
    bool hasZero = false;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            int num = matrix[i][j];
            sum += abs(num);
            minAbsNum = min(minAbsNum, abs(num));
            negNumCnt += num < 0;
            hasZero |= num == 0;
        }
    }
    return sum - 2 * minAbsNum * (!hasZero && negNumCnt % 2);
}
