# Longest Palindrome Substring

## Problem

**Input**: string `str` - string containing characters without any specific order
**Output**: string - the longest palindrome substring

### Palindrome Substring

Is a continuous substring of string which is equal to its reversed version.

**Examples**: `aakskaa`, `jlj`, `dwwd`, `aaaaaa`, `foddjddof`

#### Example 1:

Input: `s = "babad"`\
Output: `"bab"`\
`Explanation: "aba" is also a valid answer.`

#### Example 2:

Input: `s = "cbbd"`\
Output: `"bb"`
 

#### Constraints:

`1 <= s.length <= 1000`\
`s consist of only digits and English letters.`

---

# Solution Evolution (Process)

This solution evolved through four stages. We started with a basic human intuition (Recursion) and refined it step-by-step to create a highly optimized engineering solution.

## 1. The Naive Approach: Recursion
**Time Complexity**: Exponential (Very Slow) \
**Space Complexity**: High (Recursion Stack)

**The Intuition:**
How do we check if a string is a palindrome? We check the outsides, then check the insides.
If we want to find the *longest* one, we can try a brute-force recursive strategy:
1. Check if the *current* string is a palindrome. If yes, we found it!
2. If not, try two possibilities: chop off the **first letter** or chop off the **last letter**.
3. Repeat this recursively until we find a match.

**Why it fails:**
This approach does the same work millions of times. If we have the string `"ABCDE"`, the recursion will check the substring `"BCD"` multiple times (once when coming from `"ABCD"` and once when coming from `"BCDE"`). For long strings, this takes forever.

## 2. The Optimization Attempt: Memoization
**Time Complexity**: $O(n^3)$ \
**Space Complexity**: $O(n^3)$ (Memory Heavy)

**The Fix:**
To stop re-calculating the same substrings, we use a "Notebook" (a table) to write down results we've already found. This is called **Memoization**.

**The Trap:**
In this specific solution, we tried to store the actual **Strings** in our table.
*   Storing `"a"` is cheap.
*   Storing `"a...[1000 chars]...a"` is very expensive.
*   Copying and storing these strings fills up the computer's RAM instantly, leading to a **Memory Limit Exceeded** error.

## 3. Dynamic Programming (The Mathematical Solution)
**Time Complexity**: $O(n^2)$ \
**Space Complexity**: $O(n^2)$

**The Logic Shift:**
Instead of storing strings, we only store `True` or `False`. We create a grid (table) called `dp` where `dp[i][j]` answers the question: *"Is the substring from index `i` to `j` a palindrome?"*

**The "Onion" Strategy:**
We can determine if a substring is a palindrome by peeling it like an onion. A string is a palindrome **only if**:
1. The outer layer matches (First letter == Last letter).
2. **AND** the inner layer is already known to be a palindrome.

**The Algorithm:**
1. We create a 2D table of `Boolean` values.
2. We fill the diagonal with `True` (because single letters "a", "b" are always palindromes).
3. We iterate **backwards**. We start from the end of the string and move to the beginning.
    *   *Why backwards?* Because to know if the outer layer is valid, we need to have *already calculated* the inner layer.\
        At first we have bottom left triangle filled up only (`true` `V`), so we can make more calculations based only on that. For example:
        ```
             0   1   2   3   4   5   6   7    < j
           _________________________________
         0 | V |   |   |   |   |   |   |   |
         1 | V | V |   |   |   |   |   |   |
         2 | V | V | V |   |   |   |   |   |
         3 | V | V | V | V |   |   |   |   |
         4 | V | V | V | V | V |   |   |   |
         5 | V | V | V | V | V | V |   |   |
         6 | V | V | V | V | V | V | V |   |
         7 | V | V | V | V | V | V | V | V |
           '''''''''''''''''''''''''''''''''
         ^
         i
        ```
        It means that all one-char strings are palindromes, and empty strings are palindromes (for valid calculations). \
        We will fill `dp[i][j] = str[i]==str[j] && dp[i+1][j-1]` (if edge characters are the same and the inner part is a palindrome)\
        As you can see if we start from the top, we could fill `[0,1]` and `[0,2]`, but to fill `[0,3]` we need a value from `[1,2]` but we don't have one.
4. Once the table is full, we look for the `True` value that represents the longest distance between start and end.

## 4. Expand Around Center (The Optimal Solution)
**Time Complexity**: $O(n^2)$ \
**Space Complexity**: $O(1)$ (Uses almost no memory)

**The Insight:**
The Dynamic Programming solution is correct, but creating a massive 2D table takes up a lot of space.\
We can solve this without the table by looking at the **Geometry** of a palindrome.

Every palindrome has a **Center**.
*   **Odd Length:** The center is a specific character (e.g., "b**a**b").
*   **Even Length:** The center is the gap between two characters (e.g., "a**|**a").

**The Algorithm:**
1. We iterate through the string, treating every character (and every gap) as a potential center.
2. From that center, we expand two "arms" (pointers) left and right.
3. As long as the characters on the left and right match, we keep expanding.
4. When they stop matching, we calculate the length and compare it to our record.

**Why this is best:**
It does the same amount of comparisons as Dynamic Programming, but it requires **zero** extra memory allocation for tables. It is extremely fast and cache-friendly.