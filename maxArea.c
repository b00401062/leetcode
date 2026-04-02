#define min(a, b) ({\
    __typeof__ (a) _a = (a);\
    __typeof__ (b) _b = (b);\
    _a < _b ? _a : _b;\
})

#define max(a, b) ({\
    __typeof__ (a) _a = (a);\
    __typeof__ (b) _b = (b);\
    _a > _b ? _a : _b;\
})

int maxArea(int* height, int heightSize) {
    int l = 0;
    int r = heightSize - 1;
    int a = (r - l) * min(height[l], height[r]);
    while (l < r){
        if (height[l] < height[r]) {
            l++;
        } else {
            r--;
        }
        a = max(a, (r - l) * min(height[l], height[r]));
    }
    return a;
}
