# Problem

Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer.

The algorithm for `myAtoi(string s)` is as follows:

1. **Whitespace:** Ignore any leading whitespace (`" "`).
2. **Signedness:** Determine the sign by checking if the next character is `'-'` or `'+'`, assuming positivity if neither present. 
3. **Conversion:** Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
4. **Rounding:** If the integer is out of the 32-bit signed integer range [$-2^{31}$, $2^{31} - 1$], then round the integer to remain in the range. Specifically, integers less than $-2^{31}$ should be rounded to $-2^{31}$, and integers greater than $2^{31} - 1$ should be rounded to $2^{31} - 1$.

Return the integer as the final result.

 

### Example 1:

Input: `s = "42"`

Output: `42`

#### Explanation:

```
The underlined characters are what is read in and the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^
```

### Example 2:

Input: `s = " -042"`

Output: `-42`

#### Explanation:

```
Step 1: "   -042" (leading whitespace is read and ignored)
            ^
Step 2: "   -042" ('-' is read, so the result should be negative)
             ^
Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)
               ^
```

### Example 3:

Input: `s = "1337c0d3"`

Output: `1337`

#### Explanation:

```
Step 1: "1337c0d3" (no characters read because there is no leading whitespace)
         ^
Step 2: "1337c0d3" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "1337c0d3" ("1337" is read in; reading stops because the next character is a non-digit)
             ^
```

### Example 4:

Input: `s = "0-1"`

Output: `0`

#### Explanation:

```
Step 1: "0-1" (no characters read because there is no leading whitespace)
         ^
Step 2: "0-1" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "0-1" ("0" is read in; reading stops because the next character is a non-digit)
          ^
```

### Example 5:

Input: `s = "words and 987"`

Output: `0`

#### Explanation:

```
Reading stops at the first non-digit character 'w'.
```


### Constraints:

`0 <= s.length <= 200` \
`s` consists of English letters (lower-case and upper-case), digits `(0-9)`, `' '`, `'+'`, `'-'`, and `'.'`.

&nbsp;
&nbsp;

# Intuition
The key insight is to use `long long` as a "safety buffer" - since multiplying any 32-bit integer by 10 won't overflow a 64-bit integer, we can safely perform arithmetic first and check bounds afterward.

# Approach
1. **Trim leading whitespace**: Use `std::string_view` for zero-copy substring operations. Find the first non-whitespace character using `std::find_if`.

2. **Parse sign**: Check the first character after whitespace for `'+'` or `'-'`. Default to positive if neither is present. Advance the index past the sign character.

3. **Extract digits with smart overflow handling**: 
   - Use `long long` to accumulate the result, which gives us room to safely compute `num*10 + digit` without overflow (since `INT_MAX × 10 < LLONG_MAX`)
   - **After** each digit addition, check if the result exceeds 32-bit bounds
   - For negative numbers: check if `-num <= INT_MIN`
   - For positive numbers: check if `num >= INT_MAX`
   - Return the appropriate boundary value immediately upon overflow detection

4. **Return result**: Multiply by sign and cast to int. If no digits were found, `num` remains 0, which is the correct behavior.

**Why check overflow AFTER computation?** Because we're using `long long`, we can afford to compute first then check. This is simpler and equally safe compared to pre-checking `if (num > (INT_MAX - digit) / 10)`.

# Complexity
- Time complexity: $O(n)$
where `n` is the length of the input string. We make at most two passes: one to skip leading whitespace and one to parse digits. In practice, we only process each character once, stopping at the first non-digit character.

- Space complexity: $O(1)$
<!-- Add your space complexity here, e.g. $$O(n)$$ -->
We use constant extra space. `std::string_view` is just a pointer and length (16 bytes typically), not a copy of the string. All variables (`sign`, `idx`, `num`) are fixed-size primitives regardless of input size.

# Code
```cpp []
class Solution {
public:
    std::string_view trimLeft(std::string_view s) {
        auto firstNotWhiteChar = std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        });
        return s.substr(firstNotWhiteChar - s.begin());
    }

    int myAtoi(string s) {
        std::string_view input = trimLeft(s);

        if (input.empty()) return 0;

        int8_t sign = 1;
        size_t idx = 0;

        if (input[idx] == '-') {
            sign = -1;
            idx++;
        } 
        else if (input[idx] == '+') 
            idx++;

        long long num = 0;
        while(idx < input.size() && std::isdigit(input[idx])) {
            num = num*10 + (int)(input[idx] - '0');
            idx++;

            if (sign == -1) {
                if (-num <= INT_MIN) return INT_MIN;
            }
            else if (num >= INT_MAX) return INT_MAX;
        }

        return (int)(sign*num);
    }
};
```