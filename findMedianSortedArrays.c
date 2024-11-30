int binarySearch(int* nums, int size, int target) {
    int left = 0;
    int right = size;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return -left - 1;
}

int select(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    if (nums1Size == 0) {
        return nums2[k];
    }
    if (nums2Size == 0) {
        return nums1[k];
    }
    int pivot = nums1[nums1Size / 2];
    int index = binarySearch(nums2, nums2Size, pivot);
    int nums1Cnt = nums1Size / 2;
    int nums2Cnt = index >= 0 ? index : -index - 1;
    int count = nums1Cnt + nums2Cnt;
    if (count < k) {
        return select(&nums1[nums1Cnt + 1], nums1Size - nums1Cnt - 1, &nums2[nums2Cnt], nums2Size - nums2Cnt, k - count - 1);
    } else if (count > k) {
        return select(nums1, nums1Cnt, nums2, nums2Cnt, k);
    } else {
        return pivot;
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int size = nums1Size + nums2Size;
    return size % 2 == 0 ? (
        (
            (double) select(nums1, nums1Size, nums2, nums2Size, size / 2 - 1) +
            (double) select(nums1, nums1Size, nums2, nums2Size, size / 2)
        ) / 2
    ) : (
        (double) select(nums1, nums1Size, nums2, nums2Size, size / 2)
    );
}
