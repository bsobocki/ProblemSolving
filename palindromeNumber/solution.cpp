#include <iostream>
#include <vector>

bool isPalindromeVec(int x) {
    if (x < 0) return false;

    std::vector<int> digits;
    while(x > 0) {
        digits.push_back(x%10);
        x /= 10;
    }

    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != digits[digits.size()-1-i])
            return false;
    }
    return true;
}

// reverse the whole X
bool isPalindromeRev(int x) {
    if (x < 0) return false;
    int tempX = x;
    long int revX = 0;

    while(tempX > 0) {
        // move current digits
        revX *= 10;
        // add the new one
        revX += tempX % 10;
        tempX /= 10;
    }

    return revX == x;
}

// reverse only the half of the X number
// this is not my idea, but it is a little bit faster :D
// so i wanted to add it
bool isPalindromeRevHalf(int x) {
    // the algorithm won't work for 10*k
    if (x < 0 or (x and x % 10 == 0)) return false;

    int revX = 0;
    while (revX < x) {
        revX = revX * 10 + x % 10;
        x /= 10;
    }

    return x == revX or x == revX/10;
}

void runSolution() {
    /* nothing.. for now! */
}
