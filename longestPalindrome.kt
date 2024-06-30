fun longestPalindrome(s: String): String {
    if (s.length <= 1) {
        return s
    }
    val joinedS = "#" + s.toCharArray().joinToString("#") + "#"
    val spans = IntArray(joinedS.length) { 0 }
    var ctIdx = 0
    var rtIdx = 0
    for (i in 0 until joinedS.length) {
        if (i <= rtIdx) {
            spans[i] = min(rtIdx - i, spans[2 * ctIdx - i])
        }
        while (
            i - spans[i] - 1 >= 0 &&
            i + spans[i] + 1 < joinedS.length &&
            joinedS[i - spans[i] - 1] == joinedS[i + spans[i] + 1]
        ) {
            spans[i]++
        }
        if (i + spans[i] > rtIdx) {
            ctIdx = i
            rtIdx = i + spans[i]
        }
    }
    ctIdx = spans.indices.maxBy { spans[it] }!!
    return joinedS.substring(ctIdx - spans[ctIdx], ctIdx + spans[ctIdx] + 1).replace("#", "")
}
