# Problem
Given an input string `s` and a pattern `p`, implement regular expression matching with support for `'.'` and `'*'` where:
- `'.'` Matches any single character.​​​​ \
- `'*'` Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

 

#### Example 1:

Input: `s = "aa", p = "a"` \
Output: `false` \
Explanation: `"a" does not match the entire string "aa".` \


#### Example 2:

Input: `s = "aa", p = "a*"` \
Output: `true` \
Explanation: `'*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".`


#### Example 3:

Input: `s = "ab", p = ".*"` \
Output: `true` \
Explanation: `".*" means "zero or more (*) of any character (.)".`
 

#### Constraints:

`1 <= s.length <= 20` \
`1 <= p.length <= 20` \
`s contains only lowercase English letters.` \
`p contains only lowercase English letters, '.', and '*'.` \
`It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.`

# Intuition
My first instinct was to solve it recursively - at each position, we have choices:
- match the current character,
- or if there's a `*`, decide whether to use it for zero or more matches.

The key insight is that `*` creates branching: we can either skip the `<char>*` pattern entirely (0 occurrences) or match one character and stay with the same pattern (1+ occurrences).

After implementing the naive recursion (which had exponential time complexity due to recalculating the same subproblems), I realized this problem has overlapping subproblems - the same `(i, j)` pairs are checked multiple times. This led me to memoization, and finally to a bottom-up DP solution.

# Approach
<!-- Describe your approach to solving the problem. -->
I use **dynamic programming** where `dp[i][j]` represents whether `s[0...i-1]` matches `p[0...j-1]`.

**Base cases:**
1. `dp[0][0] = true` (empty string matches empty pattern)
2. For `dp[0][j]` (empty string vs pattern): only true if pattern consists of `<char>*` expressions that can all match zero times

**Main logic:**
- If current pattern character is `*`: 
  - If the character before `*` matches current string character (or is `.`): we have two choices:
    - Use `*` for zero matches: `dp[i][j-2]`
    - Use `*` for one more match: `dp[i-1][j]`
  - If it doesn't match: can only use `*` for zero matches: `dp[i][j-2]`
- If current pattern character is regular or `.`:
  - Must match current characters, so result depends on: `dp[i-1][j-1]`

**Evolution:** I started with naive recursion O(2^(n+m)), improved to memoized recursion O(n*m) by caching states, and finally converted to bottom-up DP for cleaner implementation.

# Complexity
- Time complexity: **O(n × m)**
<!-- Add your time complexity here, e.g. $$O(n)$$ -->
We fill a table of size `(n+1) × (m+1)` where `n = s.length()` and `m = p.length()`. Each cell is computed in O(1) time.

- Space complexity: **O(n × m)**
<!-- Add your space complexity here, e.g. $$O(n)$$ -->
We use a 2D DP table of size `(n+1) × (m+1)`. This could be optimized to O(m) by using only two rows, but the current solution prioritizes clarity.


# Code
```cpp []
class Solution {
public:
    // Dynamic Programming version based on recursion
    bool isMatch(string s, string p) {
        // we will create a table for our cases s[0..i] matches p[0..j] - with empty strings
        // the same checks we did in recursion solution, but here empty strings are at 0 indexes
        // index tells about string length (i tells about current s length and j about p)
        // we will start with false as each value
        std::vector<std::vector<bool>> dp(s.size()+1, std::vector<bool>(p.size()+1, false));

        // empty s matches empty p
        dp[0][0] = true;

        // at first we want to check empty s matches parts of p
        // it can do it only for p composed only from expressions <char>* (like e.g. a*.*b*)
        // index j = 0 represents a column for empty p, so we start from 2 (second character, so first that can be '*')
        for (int j = 2; j <= p.size(); j+=2) {
            if (p[j-1] == '*') {
                // if we have expression <char>* then it can be matched
                // only when empty s matches previous part of p (before "<char>*")
                dp[0][j] = dp[0][j-2];
            }
        }

        // cases where p is empty but s is not remains as false
        // because we can't match empty pattern with non-empty string


        // the column j = 1 remains false except dp[1][1] if s[0] == p[0] or p[0] == '.'
        if (!s.empty() && !p.empty()) {
            dp[1][1] = s[0] == p[0] || p[0] == '.';
        }

        // for each check we will add one more character from s or one more from p
        // so we will consider cases "what after adding this character? will it still match?"
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 2; j <= p.size(); j++) {
                // checking s[0..i-1] and p[0..j-1]
                auto currS = s[i-1];
                auto currP = p[j-1];
                auto prevP = p[j-2];

                if (currP == '*') {
                    if (currS == prevP || prevP == '.') {
                        dp[i][j] =  dp[i][j-2] ||   // we can still treat it as 0 matches (the same as p[0..j-3] - without <char>*)
                                    dp[i-1][j];     // we can treat is as one more match (the same as s[0..i-2] for p[0..j-1])
                    }
                    else {
                        // treat <char>* as 0 occurences so the result is the same as for p without <char>*
                        dp[i][j] =  dp[i][j-2];
                    } 
                }
                // if we have a letter or '.'
                else {
                    // if we match this one then the result is the same as without currS and currP
                    if (currS == currP || currP == '.') {
                        dp[i][j] = dp[i-1][j-1];
                    }
                    // if we don't then the result of current check remains false
                }
            }
        }

        return dp[s.size()][p.size()];
    }
};
```