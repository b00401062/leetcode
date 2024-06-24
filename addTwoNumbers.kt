fun carryRecursively(l: ListNode?): ListNode? {
    if (l == null) {
        return null
    }
    if (l.`val` >= 10) {
        l.`val` -= 10
        l.next = l.next ?: ListNode(0)
        l.next.`val`++
    }
    l.next = carryRecursively(l.next)
    return l
}

fun addTwoNumbersRecursively(l1: ListNode?, l2: ListNode?): ListNode? {
    return when {
        l1 == null -> l2
        l2 == null -> l1
        else -> ListNode(
            l1.`val` + l2.`val`,
             addTwoNumbers(l1.next, l2.next)
        )
    }
}

fun addTwoNumbers(l1: ListNode?, l2: ListNode?): ListNode? {
    return carryRecursively(addTwoNumbersRecursively(l1, l2))
}
