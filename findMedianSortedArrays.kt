fun select(l1: IntArray, l2: IntArray, k: Int): Int {
    if (l1.isEmpty()) {
        return l2[k]
    }
    if (l2.isEmpty()) {
        return l1[k]
    }
    val pivot = l1[l1.size / 2]
    val index = l2.binarySearch(pivot)
    val ltPivotInL1Cnt = l1.size / 2
    val ltPivotInL2Cnt = if (index >= 0) index else -index - 1
    val ltPivotCnt = ltPivotInL1Cnt + ltPivotInL2Cnt
    return when {
        k < ltPivotCnt -> {
            val subL1 = l1.sliceArray(0 until ltPivotInL1Cnt)
            val subL2 = l2.sliceArray(0 until ltPivotInL2Cnt)
            select(subL1, subL2, k)
        }
        k > ltPivotCnt -> {
            val subL1 = l1.sliceArray(ltPivotInL1Cnt + 1 until l1.size)
            val subL2 = l2.sliceArray(ltPivotInL2Cnt until l2.size)
            select(subL1, subL2, k - ltPivotCnt - 1)
        }
        else -> pivot
    }
}

fun findMedianSortedArrays(nums1: IntArray, nums2: IntArray): Double {
    val len = nums1.size + nums2.size
    return when (len % 2) {
        0 -> {
            val ltMed = select(nums1, nums2, len / 2 - 1)
            val rtMed = select(nums1, nums2, len / 2)
            (ltMed + rtMed).toDouble() / 2
        }
        else -> select(nums1, nums2, len / 2).toDouble()
    }
}
