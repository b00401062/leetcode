import java.util.LinkedList

fun numberOfSubarrays(nums: IntArray, k: Int): Int {
    var count = 0
    var lastEvenNumIdx = -1
    val idxOfOddNums = LinkedList<Int>()
    for ((i, num) in nums.withIndex()) {
        if (num % 2 == 1) {
            idxOfOddNums.add(i)
        }
        if (idxOfOddNums.size == k + 1) {
            lastEvenNumIdx = idxOfOddNums.remove()
        }
        if (idxOfOddNums.size == k) {
            count += (idxOfOddNums.first() - lastEvenNumIdx)
        }
    }
    return count
}
