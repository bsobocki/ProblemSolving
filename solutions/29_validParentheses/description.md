# Problem

Given a string s containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

#### Example 1:
```
Input: s = "()"

Output: true
```

#### Example 2:
```
Input: s = "()[]{}"

Output: true
```

#### Example 3:
```
Input: s = "(]"

Output: false
```

#### Example 4:
```
Input: s = "([])"

Output: true
```

#### Example 5:
```
Input: s = "([)]"

Output: false
```

#### Constraints:

- `1 <= s.length <= 104`
- `s consists of parentheses only '()[]{}'`

---

# Intuition
The problem requires validating nested structures (Last-In-First-Out), which naturally suggests using a **Stack**. However, checking for matching pairs (like `(` with `)`, `{` with `}`) usually involves writing multiple verbose `if-else` statements or using a hash map.

My intuition was to simplify the matching logic using **arithmetic**. By assigning a specific integer ID to each bracket, we can reduce the matching condition to a simple mathematical sum. If the ID of an opening bracket plus the ID of a closing bracket equals a specific `checkSum`, they are a valid pair.

# Approach
1.  **Mapping:** We assign IDs to the brackets such that valid pairs always sum to **7**.
    *   Open brackets: `(` = 1, `{` = 2, `[` = 3
    *   Close brackets: `]` = 4, `}` = 5, `)` = 6
    *   Logic: `1+6=7`, `2+5=7`, `3+4=7`.
2.  **Stack Operations:**
    *   We iterate through the string.
    *   **Open Brackets:** If the character's ID is less than 4, it is an opening bracket. We push it onto the stack.
    *   **Close Brackets:** If it is a closing bracket, we check if the stack is non-empty and if `charId(stack.top()) + charId(current) == 7`.
        *   If the sum is 7, we pop the stack (valid closure).
        *   Otherwise, the string is invalid.
3.  **Final Check:** After the loop, if the stack is empty, all brackets were matched correctly. If not, there are unmatched opening brackets remaining.

# Complexity
- Time complexity: $O(n)$
  We iterate through the string exactly once. The operations inside the loop (calculating ID, stack push/pop, integer comparison) are all $O(1)$.

- Space complexity: $O(n)$
  In the worst-case scenario (e.g., a string of all opening brackets like `"((((("`), the stack will store all $n$ characters.