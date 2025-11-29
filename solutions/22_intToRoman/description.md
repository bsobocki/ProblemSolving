# Problem
Seven different symbols represent Roman numerals with the following values:

| Symbol | Value |
| - | - |
| I | 1 |
| V | 5 |
| X | 10 |
| L | 50 |
| C | 100 |
| D | 500 |
| M | 1000 |

Roman numerals are formed by appending the conversions of decimal place values from highest to lowest. Converting a decimal place value into a Roman numeral has the following rules:

- If the value does not start with 4 or 9, select the symbol of the maximal value that can be subtracted from the input, append that symbol to the result, subtract its value, and convert the remainder to a Roman numeral.

- If the value starts with 4 or 9 use the subtractive form representing one symbol subtracted from the following symbol, for example, 4 is 1 (I) less than 5 (V): IV and 9 is 1 (I) less than 10 (X): IX. Only the following subtractive forms are used: 4 (IV), 9 (IX), 40 (XL), 90 (XC), 400 (CD) and 900 (CM).

- Only powers of 10 (I, X, C, M) can be appended consecutively at most 3 times to represent multiples of 10. You cannot append 5 (V), 50 (L), or 500 (D) multiple times. If you need to append a symbol 4 times use the subtractive form.

Given an integer, convert it to a Roman numeral.

#### Example 1:

Input: `num = 3749`

Output: `"MMMDCCXLIX"`

Explanation:
```
3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC as 500 (D) + 100 (C) + 100 (C)
  40 = XL as 10 (X) less of 50 (L)
   9 = IX as 1 (I) less of 10 (X)
Note: 49 is not 1 (I) less of 50 (L) because the conversion is based on decimal places
```

#### Example 2:

Input: `num = 58`

Output: `"LVIII"`

Explanation:
```
50 = L
 8 = VIII
```


#### Example 3:

Input: `num = 1994`

Output: `"MCMXCIV"`

Explanation:
```
1000 = M
 900 = CM
  90 = XC
   4 = IV
```

#### Constraints:

- `1 <= num <= 3999`

---

# Intuition
Roman numerals follow a strict decimal place logic. The pattern used to form numbers 1 through 9 (`I` to `IX`) is structurally identical to the pattern for 10 through 90 (`X` to `XC`) and 100 through 900 (`C` to `CM`).

Instead of subtracting largest values greedily (which is a common approach), we can process the number **digit by digit** (ones, tens, hundreds, thousands). By maintaining an array of symbols `['I', 'V', 'X', 'L', 'C', 'D', 'M']`, we can treat every decimal place generically. We just need to know which index represents the current "unit", "five", and "next ten".

# Approach
1.  **Symbol Mapping**: Store the Roman characters in a vector in ascending order of value.
2.  **Reverse Iteration**: Process the input integer `num` from the last digit to the first (using modulo `% 10` and division `/= 10`).
3.  **Dynamic Symbol Selection**: Maintain a `place` index that points to the "unit" symbol for the current decimal position:
    *   `place = 0` (Ones): Unit='I', Five='V', Ten='X'
    *   `place = 2` (Tens): Unit='X', Five='L', Ten='C'
    *   `place = 4` (Hundreds): Unit='C', Five='D', Ten='M'
    *   `place = 6` (Thousands): Unit='M'
4.  **Digit Construction**: For each digit, construct the Roman substring using the standard rules:
    *   **0-3**: Repeat the unit symbol.
    *   **4**: Append Unit + Five.
    *   **5-8**: Append Five + (Digit-5) Units.
    *   **9**: Append Unit + Ten.
5.  **Result Building**: Since we process from right to left (ones to thousands), we prepend the generated substring to our `result` string.

# Complexity
- Time complexity: $O(1)$
  Since the constraint is `1 <= num <= 3999`, the maximum number of digits is 4. The loop runs a constant number of times. (Generalized, this is $O(\log_{10} n)$).

- Space complexity: $O(1)$
  We use a fixed-size vector for symbols and the output string length is bounded (the longest string is "MMMDCCCLXXXVIII", which is 15 characters).

# Code
```cpp []
class Solution {
public:
    string intToRoman(int num) {
        static const std::vector<char> romans = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
        
        // place shows where we have as digital place
        // it maps to our array 'romans' as 0, 2, 4, 6
        auto getRoman = [&](int digit, int place) {
            if (place < 0 || place > 6) return string("");

            // digit 'unit' in current digital place
            // 'unit' symbolize power of 10
            char unit = romans[place];

            // if we have thousands return 'M' up to 3 times
            if (place == 6)
                return string(digit, 'M');
            
            // digit 'five' in current digital place
            char five = romans[place+1];
            // digit 'unit' from the next digital place (so 'ten' in current)
            char ten = romans[place+2];

            // append 'unit' up to 3 times
            if (digit < 4)
                return string(digit, unit);

            // use subtractive forms:
            else if (digit == 4)
                return string({unit, five});

            else if (digit == 9)
                return string({unit, ten});
            
            // add 'five' and append 'unit' up to 3 times
            return string({five}) + string(digit-5, unit);
        };

        // start from the less important digits
        int place = 0;
        std::string result;

        // standard digit handling
        while (num > 0) {
            // add current roman part at the beggining
            result = getRoman(num % 10, place) + result;
            place += 2;
            num /= 10;
        }

        return result;
    }
};
```