import java.util.LinkedList

fun numberOfSubarrays(nums: IntArray, k: Int): Int {
    var numberOfSubarrays = 0
    var headIdx = -1
    val idxOfOddNums = LinkedList<Int>()
    for ((i, num) in nums.withIndex()) {
        if (num % 2 == 1) {
            idxOfOddNums.add(i)
        }
        if (idxOfOddNums.size == k + 1) {
            headIdx = idxOfOddNums.remove()
        }
        if (idxOfOddNums.size == k) {
            numberOfSubarrays += (idxOfOddNums.first() - headIdx)
        }
    }
    return numberOfSubarrays
}
