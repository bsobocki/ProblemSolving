You are given two non-empty linked lists representing two non-negative integers. The digits are stored in `reverse order`, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

#### Example 1:

```
  2 -> 4 -> 3
  5 -> 6 -> 4
---------------
  7 -> 0 -> 8
```

Input: `l1 = [2,4,3], l2 = [5,6,4]`\
Output: `[7,0,8]`\
Explanation: `342 + 465 = 807.`

#### Example 2:

Input: `l1 = [0], l2 = [0]`\
Output: `[0]`

#### Example 3:

Input: `l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]`\
Output: `[8,9,9,9,0,0,0,1]`
 

#### Constraints:

`The number of nodes in each linked list is in the range [1, 100].`\
`0 <= Node.val <= 9`\
`It is guaranteed that the list represents a number that does not have leading zeros.`

&nbsp;\
&nbsp;


# Solution

## Intuition
This problem simulates the "column addition" method we learned in elementary school. Since the digits are stored in **reverse order** (units place first), the Linked List structure perfectly matches the way we naturally add numbers: from right to left (least significant digit to most significant).

We process the lists node by node, maintaining a `carry` for any sum that exceeds 9.

## Algorithm

**Time Complexity**: $O(\max(M, N))$ \
**Space Complexity**: $O(\max(M, N))$ \
*(where M and N are the lengths of the two lists)*

1. **Initialize Pointers**: Create a dummy head for the result list and a `carry` variable initialized to 0.
2. **Iterate**: Loop while there are nodes in `l1` OR nodes in `l2` OR `carry` is non-zero.
    *   **Extract values:** Get the value from the current `l1` node (or 0 if null) and `l2` node (or 0 if null).
    *   **Calculate Sum:** `sum = val1 + val2 + carry`.
    *   **Update Digit:** `digit = sum % 10` (remainder).
    *   **Update Carry:** `carry = sum / 10` (integer division).
    *   **Create Node:** Add a new node with `digit` to the result list.
3. **Advance**: Move `l1` and `l2` pointers forward if they are not null.

## Edge Cases Handled
*   **Different Lengths:** The algorithm handles lists of different sizes (e.g., `99 + 1`) by treating null nodes as `0`.
*   **Final Carry:** If the sum of the last two digits creates a carry (e.g., `5 + 5 = 10`), the loop condition `carry > 0` ensures a new node `[1]` is created at the end.
*   **Zero:** The input `[0] + [0]` correctly returns `[0]`.

## Code Structure
*   **`addTwoNumbers`**: The core logic.
*   **`ListNode`**: Standard definition for a singly-linked list.
*   **Helper Functions**: `createList` and `listToVector` are included to easily convert between C++ `std::vector` (for easy testing) and the `ListNode` structure required by the problem.
*   **Memory Management**: The solution includes logic to `delete` allocated nodes in the test runner to prevent memory leaks.