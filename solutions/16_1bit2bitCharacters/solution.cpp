#include <iostream>
#include <utils/utils.hpp>

using namespace std;

bool isOneBitCharacter(const vector<int>& bits) {
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

struct Test {
    vector<int> bits;
    bool expectedResult;

    std::string getInfo() const {
        std::stringstream ss;
        ss << bits;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // 1. Minimal case: Just a single 0. 
        // Must be a one-bit character.
        { {0}, true },

        // 2. Minimal false case: 1 followed by 0.
        // Decodes to "10" (two-bit character). Last char is NOT one-bit.
        { {1, 0}, false },

        // 3. Example 1 provided in problem.
        // Decodes to "10", "0". Last char is one-bit.
        { {1, 0, 0}, true },

        // 4. Example 2 provided in problem (Odd number of 1s before the end).
        // Decodes to "11", "10". Last char is two-bit.
        { {1, 1, 1, 0}, false },

        // 5. Even number of 1s before the end.
        // Decodes to "11", "0". Last char is one-bit.
        { {1, 1, 0}, true },

        // 6. Zero interruption.
        // Decodes to "0", "10". Last char is two-bit.
        { {0, 1, 0}, false },

        // 7. Longer sequence with even 1s (4 ones).
        // Decodes to "11", "11", "0". Last char is one-bit.
        { {1, 1, 1, 1, 0}, true },

        // 8. Longer sequence with odd 1s (5 ones).
        // Decodes to "11", "11", "10". Last char is two-bit.
        { {1, 1, 1, 1, 1, 0}, false },

        // 9. Mixed sequence.
        // Decodes to "10", "11", "0". Last char is one-bit.
        { {1, 0, 1, 1, 0}, true },
        
        // 10. Mixed sequence ending in false.
        // Decodes to "11", "0", "10". Last char is two-bit.
        { {1, 1, 0, 1, 0}, false },

        // 11. Double Zero Ending
        // The second-to-last 0 acts as a barrier. The last 1-stream is empty (length 0, which is even).
        // Decodes: ..., "0", "0". 
        { {1, 1, 1, 0, 0}, true },

        // 12. Long stream of only Zeros
        // No 1s exist to form 2-bit characters.
        { {0, 0, 0, 0, 0}, true },

        // 13. Alternating "10" pattern ending in "10"
        // Decodes: "10", "10", "10". Last char is 2-bit.
        { {1, 0, 1, 0, 1, 0}, false },

        // 14. Alternating "10" pattern ending in isolated "0"
        // Decodes: "10", "10", "0". Last char is 1-bit.
        { {1, 0, 1, 0, 0}, true },

        // 15. Large ODD block of 1s immediately preceding the end
        // 7 ones. 7 is odd -> last 1 merges with 0.
        { {0, 1, 1, 1, 1, 1, 1, 1, 0}, false },

        // 16. Large EVEN block of 1s immediately preceding the end
        // 8 ones. 8 is even -> 1s pair up entirely, leaving 0 alone.
        { {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, true },

        // 17. Trap Case: A zero buried deep inside
        // The '0' at index 2 resets the count. We only care about the 1s after it.
        // Suffix is "1110" (3 ones -> odd -> false).
        { {1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, false },

        // 18. Trap Case: Similar to above but ensuring True result
        // Suffix is "110" (2 ones -> even -> true).
        { {1, 1, 1, 1, 1, 0, 1, 1, 0}, true },

        // 19. "Staircase" pattern 
        // 1, 11, 111... 
        // Ends with 4 ones (even) -> true.
        { {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0}, true },

        // 20. Minimum case for "false" with a prefix
        // Decodes: "0", "0", "10".
        { {0, 0, 1, 0}, false }
    };

    runTests(tests, [](const Test& test){
        bool result = isOneBitCharacter(test.bits);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}