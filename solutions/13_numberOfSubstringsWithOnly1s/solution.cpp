#include <iostream>
#include <utils/utils.hpp>
#include <numeric>

using namespace std;

int numSub(const string& s) {
    constexpr int mod = 1000000007;
    auto l = s.begin();
    auto r = s.begin();
    int sum = 0;

    // Modular arithmetic property: (x+y) % n = ((x % n) + (y % n) ) % n
    // x + x-1 + x-2 + ... + 3 + 2 + 1 = (x+1)*x/2
    // so combined both: ((x+1)*x/2) % n = (((((x+1) % n) * x ) % n) / 2) % n
    // but you can skip %n on division because division only decreases number
    // so no need to do %n on that because the result is still less than 'n'
    // x % n is less than n but here it is also divided by 2 - still less
    while (r != s.end()) {
        l = std::find(r, s.end(), '1');
        r = std::find(l, s.end(), '0');
        size_t size1s = r - l;
        sum = (sum + ((((size1s + 1) % mod) * size1s) % mod) / 2) % mod;
    }

    return sum;
}

struct Test {
    std::string s;
    int expectedResult;
};

struct TestStrInfo {
    bool startsWith1;
    std::vector<int> lengths;

    std::string asStr() {
        stringstream ss;
        ss << "[ start: " << (startsWith1 ? "1" : "0") << " | " << lengths << "]";
        return ss.str();
    }
};

std::string createTestString(TestStrInfo strInfo) {
    size_t strLen = std::accumulate(strInfo.lengths.begin(), strInfo.lengths.end(), 0);
    std::string str;
    str.reserve(strLen);
    char ch = strInfo.startsWith1 ? '0' : '1'; // init inversely because it will be flipped inside loop
    for (auto len : strInfo.lengths) {
        ch = ch == '0' ? '1' : '0';
        for (int i = 0; i < len; i++)
            str += ch;
    }
    return str;
}

void runSolution() {
    const std::vector<Test> tests = {
        // Example cases
        {"0110111", 9},
        {"101", 2},
        {"111111", 21},

        // Edge cases
        {"0", 0},
        {"1", 1},
        {"00000", 0},
        {"11111", 15},

        // Alternating patterns
        {"10101", 3},
        {"01010", 2},

        // Multiple segments
        {"110011", 6},
        {"1110111", 12},
        {"11011", 6},

        // Starting/ending with 0
        {"01110", 6},
        {"011101", 7},

        // Larger consecutive segments
        {"1111", 10},
        {"11111111", 36},

        // Mixed patterns
        {"100101110", 8},
        {"0001000", 1},

        // Large case (stress test)
        {std::string(100, '1'), 5050},
        {std::string(1000, '1'), 500500},

        // Alternating with consecutive
        {"1100110011", 9},
        {"111000111", 12},

        // Single segments separated by multiple zeros
        {"1000001", 2},
        {"110000011", 6},

        // very big test with 80000 x '1' and 1002 x '1' (from leetCode to check modulo for too big data)
        {
            createTestString({
                true,
                {3, 3, 1, 1, 1, 1, 1, 1, 4, 5, 80000, 2, 1, 1, 1, 1, 1002, 4, 1, 2, 1}
            }), 
            200542505
        }
    };

    runTests(tests, [](const Test& test){
        int num = numSub(test.s);
        std::string testResultInfo = getTestResultInfo(test.s, test.expectedResult, num, PrintFlag::SHOW_FAILS_ONLY);
        if (!testResultInfo.empty()) std::cout << testResultInfo << std::endl;
        return num == test.expectedResult;
    });
}