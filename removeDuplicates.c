int removeDuplicates(int* nums, int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        nums[count++] = nums[i];
        while (i < numsSize - 1 && nums[i] == nums[i + 1]) {
            i++;
        }
    }
    return count;
}
