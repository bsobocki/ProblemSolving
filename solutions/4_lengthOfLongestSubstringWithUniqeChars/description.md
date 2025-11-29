# Problem
Given a string `s`, find the length of the `longest substring` without duplicate characters.

#### Example 1:

Input: `s = "abcabcbb"`\
Output: `3`\
Explanation: `The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.`

#### Example 2:

Input: `s = "bbbbb"`\
Output: `1`\
Explanation: `The answer is "b", with the length of 1.`

#### Example 3:

Input: `s = "pwwkew"`\
Output: `3`\
Explanation: `The answer is "wke", with the length of 3.`\
`Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.`
 

#### Constraints:

`0 <= s.length <= 5 * 104`\
`s consists of English letters, digits, symbols and spaces.`

---

# Solution

## The Sliding Window Strategy

**Time Complexity**: $O(N)$ \
**Space Complexity**: $O(\min(N, \Sigma))$ *(where $\Sigma$ is the size of the character set)*

The naive approach would be to check every possible substring, which is $O(N^3)$ or $O(N^2)$. We can optimize this to a single pass ($O(N)$) using the **Sliding Window** technique combined with a Hash Map.

### Intuition
Imagine a window defined by `[start, i]` expanding over the string:
1.  We expand the window to the right by increasing `i`.
2.  We store the index of every character we see in a map: `seen[char] = index`.
3.  If we encounter a character that is **already inside our current window**, we have found a duplicate.
4.  To fix the duplicate, we simply contract the window from the left by moving `start` to the right.

### After finding duplicates
When we find a duplicate then we move `start` to the position immediately after the duplicate character's last occurrence in our currently considered substring.

**Key Logic Check:**
When we find a character that is already in the map, we must check:
`if (seen[char] >= start)`
This ensures that the duplicate character is actually **inside** the current window. If the duplicate is at an index *before* `start`, it means it was part of an old substring we already finished, so we ignore it.

### Algorithm Steps

1.  Initialize `start = 0` and `maxSize = 0`.
2.  Iterate through the string with index `i`.
3.  Check if `s[i]` is in `seen`:
    *   If yes, AND `seen[s[i]] >= start`:
        *   Calculate current length (`i - start`) and update `maxSize`.
        *   Move `start` to `seen[s[i]] + 1`.
4.  Update the map: `seen[s[i]] = i`.
5.  After the loop, perform one final length check (to account for the substring ending at the very last character).

### Example Walkthrough: `s = "dvdf"`

1.  **i=0 ('d')**: Map={`d`:0}. Window `d`.
2.  **i=1 ('v')**: Map={`d`:0, `v`:1}. Window `dv`.
3.  **i=2 ('d')**:
    *   'd' is in map at index 0.
    *   Index 0 is inside current window (0 >= 0). **Collision!**
    *   Move `start` to `0 + 1 = 1`.
    *   Map updates `d` to 2. Map={`d`:2, `v`:1}.
    *   Window is now `vd` (indices 1 to 2).
4.  **i=3 ('f')**: Map={`d`:2, `v`:1, `f`:3}. Window `vdf`.

Final `maxSize` is 3 ("vdf").