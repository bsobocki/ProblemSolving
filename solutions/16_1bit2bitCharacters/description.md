# Problem
We have two special characters:

The first character can be represented by one bit `0`.\
The second character can be represented by two bits (`10` or `11`).\
Given a binary array `bits` that ends with `0`, return `true` if the last character must be a one-bit character.

#### Example 1:

Input: `bits = [1,0,0]`\
Output: `true`\
Explanation: `The only way to decode it is two-bit character and one-bit character.`\
`So the last character is one-bit character.`

#### Example 2:

Input: `bits = [1,1,1,0]`\
Output: `false`\
Explanation: `The only way to decode it is two-bit character and two-bit character.`\
`So the last character is not one-bit character.`

#### Constraints:

`1 <= bits.length <= 1000`\
`bits[i] is either 0 or 1.`


# Intuition
Since the encoding rules are deterministic (a 1-bit character  is always `0`, and `1` always starts a 2-bit character `10` or `11`), we can simulate the decoding process from the beginning of the array. We don't need to backtrack; we simply walk through the array consuming bits.

At first we can immediately return `true` for two cases:
1. `[0]`,
2. `[... 0 0]`.

For the rest we will go through the bits.

If we reach to the last element `bits[size-1]`, then the last two elements makes a 2-bit char, because we can only go here from 1-bit step `i++` from `bits[size-2]` or 2-bit step `i+=2` from `bits[size-3]` - we excluded situation with two zeros at the end `[... 0 0]`. \
We have those two options then:
`[... 1 1 0 1 0]` or `[... 1 1 1 0]` -- in both ways we have the last character 2-bit.

Otherwise, if we finish processing the bits by jumping "over" the last bit, the answer is `true`, because we can't reach bits[size-1] and jump by 1-bit step. It's because of the part above and excluding two 1-bits at the end [... 0 0] before.

# Approach
1.  **Edge Case:** If the array has only one bit `[0]`, it is definitely a one-bit character. Return `true`.
2.  **Optimization:** If the second-to-last bit (`bits[n-2]`) is `0`, the last character *must* be a one-bit character. This is because a `0` always completes a character (whether it was a standalone `0` or the end of `10`). If index `n-2` is `0`, the character ending there is complete, leaving the last `0` at `n-1` to be processed alone.
3.  **Simulation:** We iterate through the array using a pointer `i` (initialized to 1 to check a pair of bits if they creates 2-bit character, where `bits[i-1]` is the first bit of it).
    *   If the current bit `bits[i-1]` is `1`, it indicates the start of a 2-bit character. We increment `i` by 2 to skip the next bit (which is the tail of this character) and jump to the next character.
    *   If `bits[i-1]` is `0`, it is a 1-bit character. We increment `i` by 1 to the next character.
4.  **Check Position:**
    *   Essentially, the loop determines where the "character boundaries" fall using the logic described in the ***"Intuition"*** part.

# Complexity
- **Time complexity:** $O(n)$
  We iterate through the `bits` array at most once, incrementing the pointer by 1 or 2 at every step.

- **Space complexity:** $O(1)$
  We only use a few variables (`i` and the size) for storage; no additional data structures are allocated.

# Code
```cpp []
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        // [0] so it is 1-bit
        if (bits.size() == 1) return true;

        // we have [... 0 0] so the last one is 1-bit
        if (bits[bits.size()-2] == 0) return true;

        // we will go through bits making steps equal to 2 for 2-bits chars and 1 for 1-bit chars
        size_t i = 1;
        while (i < bits.size()) {
            // we have 2-bit char
            if (bits[i-1] == 1)
                i += 2;
            // we have 1-bit char
            else
                i++; // if we have 1-bit then we move only by one bit
            
            // if we reach to the last element, then the last two elements makes 2-bit char
            // because we can go from 1-bit step from bits[size-2] or 2-bit step from bits[size-3]
            // we excluded two 1-bits at the end [... 0 0] from this simulation before this loop
            // [... 0 1 0] or [... 1 1 1 0] -- in both ways we have the last 2-bit character
            if (i == bits.size()-1)
                return false;

            // if we jumped over the last element, then we have 2-bit char before the last element
            // because we can't reach bits[size-1] and jump by 1-bit step
            // it's because of the 'if' statement above and excluding two 1-bits at the end [... 0 0] before this loop
            if (i == bits.size()) // that means that the last character is 1-bit
                return true;
        }

        return false;
    }
};
```