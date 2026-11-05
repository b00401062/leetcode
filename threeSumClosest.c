int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int threeSumClosest(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), cmp);
    int delta = INT_MAX;
    for (int i = 0; i < numsSize - 2; i++) {
        int left = i + 1;
        int right = numsSize - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (abs(sum - target) < abs(delta)) {
                delta = sum - target;
            }
            if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    return target + delta;
}
