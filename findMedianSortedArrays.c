int binarySearch(int* nums, int size, int target) {
    int l = 0;
    int r = size;
    while (l < r) {
        int m = (l + r) / 2;
        if (nums[m] == target) {
            return m;
        } else if (nums[m] < target) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

int select(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    if (nums1Size == 0) {
        return nums2[k];
    }
    if (nums2Size == 0) {
        return nums1[k];
    }
    int pivot = nums1[nums1Size / 2];
    int nums1Cnt = nums1Size / 2;
    int nums2Cnt = binarySearch(nums2, nums2Size, pivot);
    int cnt = nums1Cnt + nums2Cnt;
    if (cnt < k) {
        return select(
            &nums1[nums1Cnt + 1],
            nums1Size - nums1Cnt - 1,
            &nums2[nums2Cnt],
            nums2Size - nums2Cnt,
            k - cnt - 1
        );
    } else if (cnt > k) {
        return select(nums1, nums1Cnt, nums2, nums2Cnt, k);
    } else {
        return pivot;
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int size = nums1Size + nums2Size;
    if (size % 2 == 0) {
        int l = select(nums1, nums1Size, nums2, nums2Size, size / 2 - 1);
        int r = select(nums1, nums1Size, nums2, nums2Size, size / 2);
        return ((double) (l + r)) / 2;
    } else {
        return select(nums1, nums1Size, nums2, nums2Size, size / 2);
    }
}
