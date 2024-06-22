fun twoSum(nums: IntArray, target: Int): IntArray {
    val idxOfNums = mutableMapOf<Int, Int>()
    for ((i, num) in nums.withIndex()) {
        idxOfNums[target - num]?.let {
            return intArrayOf(i, it)
        }
        idxOfNums[num] = i
    }
    throw Exception()
}
