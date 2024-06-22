fun carryRecursively(l: ListNode?): ListNode? {
    if (l == null)
        return null
    if (l.`val` >= 10) {
        l.`val` -= 10
        l.next = l.next ?: ListNode(0)
        l.next.`val`++
    }
    l.next = carryRecursively(l.next)
    return l
}

fun addTwoNumbersRecursively(l1: ListNode?, l2: ListNode?): ListNode? {
    if (l1 == null)
        return l2
    if (l2 == null)
        return l1
    val l = ListNode(l1.`val` + l2.`val`)
    l.next = addTwoNumbers(l1.next, l2.next)
    return l
}

fun addTwoNumbers(l1: ListNode?, l2: ListNode?): ListNode? {
    return carryRecursively(addTwoNumbersRecursively(l1, l2))
}
