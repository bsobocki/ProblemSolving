# Problem
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

#### Example 1:

Input: `strs = ["flower","flow","flight"]`\
Output: `"fl"`

#### Example 2:

Input: `strs = ["dog","racecar","car"]`
Output: `""`
Explanation: `There is no common prefix among the input strings.`
 
#### Constraints:

`1 <= strs.length <= 200`\
`0 <= strs[i].length <= 200`\
`strs[i] consists of only lowercase English letters if it is non-empty.`

---

# Solution

## Vertical Scanning

**Time Complexity**: $O(S)$ *(where S is the sum of all characters in all strings)* \
**Space Complexity**: $O(1)$ *(We only store indices)*

There are several ways to solve this (Horizontal Scanning, Sorting, Tries), but **Vertical Scanning** is efficient because it "fails fast". If the prefix is short, we stop immediately without processing the tails of long strings.

### Intuition
Imagine the strings stacked on top of each other like a grid.
```text
f l o w e r
f l o w
f l i g h t
```
We compare the **characters** at index `i` for all strings simultaneously.
1. Check column 0 (`f`, `f`, `f`) -> Match.
2. Check column 1 (`l`, `l`, `l`) -> Match.
3. Check column 2 (`o`, `o`, `i`) -> **Mismatch!** Stop.

### Algorithm
1.  **Edge Check:** If the vector is empty, return `""`.
2.  **Find Shortest String:** We identify the shortest string in the array first. The Longest Common Prefix cannot be longer than the shortest string. This ensures we never access an index out of bounds.
3.  **Iterate Columns:** We loop through indices `i` from `0` to `shortestLen`.
4.  **Check Rows:** For each column `i`, we compare every string against our reference (the shortest string).
    *   If `str[i] != reference[i]`, we have found the end of the common prefix. We immediately return the substring from `0` to `i`.
5.  **Full Match:** If the loop finishes without returning, it means the entire shortest string is the common prefix.