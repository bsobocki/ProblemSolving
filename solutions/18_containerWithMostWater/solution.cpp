#include <iostream>
#include <utils/utils.hpp>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

// brute force solution
// time complexity O(n^2)
// space complexity O(1)
int maxAreaBruteForce(const vector<int>& height) {
    int max = 0;
    for (int i = 0; i < height.size(); i++) {
        for (int j = i+1; j < height.size(); j++) {
            int area = min(height[i], height[j]) * (j-i);
            if (max < area)
                max = area;
        }
    }
    return max;
}

// we go through the vector looking for highest walls
// time complexity O(n)
// space complexity O(1)
int maxArea(const vector<int>& height) {
    // start with the biggest width (distance between walls)
    int left = 0;
    int right = height.size()-1;

    int maxAreaVal = 0;
    // we will go through the vector moving left or right
    while(left < right) {
        int area = std::min(height[left], height[right]) * (right - left);
        maxAreaVal = std::max(maxAreaVal, area);

        // maximize areas by leaving higher walls and moving from smaller
        // because each step decreases width, so to maximize areas we need to choose higher walls
        if (height[left] > height[right])
            right--; // move left
        else
            left++; // move right
    }
    return maxAreaVal;
}

struct Test {
    vector<int> height;
    int expectedOutput;

    std::string getInfo() const {
        stringstream ss;
        ss << height;
        return ss.str();
    }
};

vector<int> generateRandomVector(int n, int min_height, int max_height) {
    // Setup random number generator
    // static logic ensures we don't re-seed every time we call the function
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(min_height, max_height);

    vector<int> vec(n);
    std::ranges::generate(vec, [&]() { return distrib(gen); });

    return vec;
}

void runSolution() {
    const std::vector<Test> tests = {
        // Example 1: Standard case from problem description
        {
            {1, 8, 6, 2, 5, 4, 8, 3, 7},
            49
        },
        // Example 2: Minimum number of lines
        {
            {1, 1},
            1
        },
        // Case 3: Increasing height
        // Max is between 2 (index 1) and 5 (index 4): width 3 * height 2 = 6
        // Or 1 (index 0) and 5 (index 4): width 4 * height 1 = 4
        {
            {1, 2, 3, 4, 5},
            6
        },
        // Case 4: Decreasing height (Symmetric to Case 3)
        {
            {5, 4, 3, 2, 1},
            6
        },
        // Case 5: Tall pillars in the middle vs Wide pillars on edges
        // The two 100s are close (dist 1), area 100.
        // The edges are small (1, 1) but wide (dist 5), area 5.
        {
            {1, 2, 100, 100, 2, 1},
            100
        },
        // Case 6: All heights equal
        // Max area is simply the endpoints: width 3 * height 5 = 15
        {
            {5, 5, 5, 5},
            15
        },
        // Case 7: Contains zeros
        // Valid container must be between index 0 (height 1) and 2 (height 2).
        // Width 2 * min(1, 2) = 2.
        {
            {1, 0, 2},
            2
        },
        // Case 8: "Mountain" shape
        // Outer: 1 vs 1 (width 6) = 6
        // Inner peaks: 100 vs 100 (width 2) = 200
        {
            {1, 8, 100, 2, 100, 8, 1},
            200
        },
        // Case 9: Large Width wins over Height
        // 2 (idx 0) and 10 (idx 6) -> width 6 * 2 = 12
        // 15 (idx 2) and 15 (idx 4) -> width 2 * 15 = 30
        // 2 (idx 0) and 6 (idx 7) -> width 7 * 2 = 14
        // Actually, check 20s:
        // {2, 9, 20, 5, 20, 9, 10, 6}
        // 20(2) and 20(4) -> area 40.
        // 9(1) and 10(6) -> width 5 * 9 = 45.
        {
            {2, 9, 20, 5, 20, 9, 10, 6},
            45
        },
        // Case 10: Zero area possible (though constraints say height >= 0, n >= 2)
        // If both lines are 0, area is 0.
        {
            {0, 0},
            0
        }
    };

    runTests(tests, [](const Test& test){
        int resultBruteForce = maxAreaBruteForce(test.height);
        int result = maxArea(test.height);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedOutput, result) << std::endl;
        return result == test.expectedOutput && result == resultBruteForce;
    });

    std::cout << "\n--- RANDOM TESTS ---\n" << std::endl;

    const int NUM_TESTS = 10;
    // data constraints from problem description
    const int MIN_N = 2;
    const int MAX_N = 100000;
    const int MIN_H = 0; 
    const int MAX_H = 1000;

    // Setup RNG for random size of vector
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> size_dist(MIN_N, MAX_N);

    auto runAndMeasureSolution = [](auto solution, std::vector<int>& height, double& elapsedTime) {
        auto start_time = std::chrono::high_resolution_clock::now();
        int result = solution(height);
        auto end_time = std::chrono::high_resolution_clock::now();
        elapsedTime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
        return result;
    };

    int failed = 0;
    for (int i = 1; i <= NUM_TESTS; ++i) {
        int n = size_dist(gen);
        vector<int> height = generateRandomVector(n, MIN_H, MAX_H);

        std::cout << std::format("{} Test Running: size={}", i, n) << std::flush;

        double elapsedTime;

        int resultBruteForce = runAndMeasureSolution(maxAreaBruteForce, height, elapsedTime);
        std::cout << " | brute force: " << elapsedTime << "ms" << std::flush;

        int resultOptimized = runAndMeasureSolution(maxArea, height, elapsedTime);
        std::cout << " | optimized: " << elapsedTime << "ms" << std::flush;

        if (resultBruteForce != resultOptimized) {
            cout << " " << getTestResultInfo(std::format("Random Test: size={}",n), resultBruteForce, resultOptimized) << std::flush;
            failed++;
        }

        std::cout << std::endl;
    }

    if (failed) std::cout << redStr(std::format("✗ {}/{} TESTS FAILED!", failed, NUM_TESTS)) << std::endl;
    else std::cout << greenStr(std::format("✓ ALL {} TESTS PASSED!", NUM_TESTS)) << std::endl;
}