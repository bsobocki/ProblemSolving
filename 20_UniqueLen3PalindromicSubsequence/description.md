# Problem

Given a string `s`, return the number of ***unique palindromes of length three*** that are a ***subsequence*** of `s`.

Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.

A `palindrome` is a string that reads the same forwards and backwards.

A `subsequenc`e` of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, `"ace`" is a subsequence of `"abcde"`.
 

#### Example 1:
```
Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")
```

#### Example 2:
```
Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".
```

#### Example 3:
```
Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")
```

#### Constraints:

- `3 <= s.length <= 105`
- `s consists of only lowercase English letters.`

---

# Intuition
A palindrome of length 3 always follows the pattern **"XYX"**.
*   The first and last characters must be the same (`X`).
*   The middle character (`Y`) can be anything.

To find all unique palindromes, we iterate through the alphabet (26 lowercase letters) to find the outer character `X` (occurs at least 2 times). For a specific two characters `X` we check if they can form a palindrome with another character `Y` in the middle, so we need to find **first occurrence** and its **last occurrence** of `X` in the string to make sure, that we will find all possible characters `Y` we can. Any unique character found strictly between these two indices acts as a valid `Y` and forms an unique palindrome with those two `X`'s.

# The Optimization Process

This solution evolved through four stages of optimization.

### Phase 1: Ranges + Hash Sets (Intuitive)
*   **Logic:** Pre-calculate the `[start, end]` range for every letter. Iterate through the string index by index. If the current index falls inside a letter's range, insert the character into a `std::unordered_set`.
*   **Bottleneck:** `unordered_set` involves hashing and memory allocation for every insertion.

### Phase 2: Ranges + Vectors (Data Structure Optimization)
*   **Logic:** Replaced `unordered_set` with a fixed-size `vector<int>` (boolean map).
*   **Improvement:** Removes hashing/allocation overhead.
*   **Bottleneck:** Still checks all 26 ranges for every character in the string ($26 \times N$ operations).

### Phase 3: Inverted Loops (Algorithmic Optimization)
*   **Logic:** Instead of iterating the string, we **iterate the ranges**. We pick a letter, identify its `start` and `end`, and loop **only** between those indices.
*   **Improvement:** Accesses memory sequentially (CPU cache-friendly) and avoids redundant checks.
*   **Bottleneck:** Allocates a vector/array once and reset only used `int`s.

### Phase 4: Bit Manipulation (Hardware Optimization)
*   **Logic:** Since we only track 26 characters, we can use a single `int` (32 bits) as a `bitmask` instead of a `vector`.
*   **Improvement:** Zero memory allocation. Uses bitwise `OR` (`|`) and `std::popcount` which are instant CPU register operations.

## Complexity Analysis

- **Time Complexity:** $O(N)$
    - We scan the string once to find boundaries. Then we scan the interiors of the ranges. Since the alphabet size (26) is constant, this is linear.

- **Space Complexity:** $O(1)$
    - We use fixed-size arrays (size 26) or integers for storage, regardless of input size.