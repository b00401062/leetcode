void swap(int* nums, int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

void reverse(int* nums, int lt, int rt) {
    while (lt < rt) {
        swap(nums, lt, rt);
        lt++;
        rt--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    int lt = numsSize - 2;
    while (lt >= 0 && nums[lt] >= nums[lt + 1]) {
        lt--;
    }
    if (lt >= 0) {
        int rt = lt + 1;
        while (rt < numsSize - 1 && nums[lt] < nums[rt + 1]) {
            rt++;
        }
        swap(nums, lt, rt);
    }
    reverse(nums, lt + 1, numsSize - 1);
}
