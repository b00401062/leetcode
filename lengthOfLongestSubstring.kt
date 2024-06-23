fun lengthOfLongestSubstring(s: String): Int {
    val idxOfChars = mutableMapOf<Char, Int>()
    var headIdx = 0
    var maxLen = 0
    for ((i, c) in s.withIndex()) {
        idxOfChars[c]?.let {
            for (j in headIdx until it) {
                idxOfChars.remove(s[j])
            }
            headIdx = it + 1
        }
        idxOfChars[c] = i
        maxLen = max(maxLen, idxOfChars.size)
    }
    return maxLen
}
