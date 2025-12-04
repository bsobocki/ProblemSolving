#include <iostream>
#include <utils/utils.hpp>
#include <set>
#include <queue>
#include <numeric>

using namespace std;


// Issue: Time Limit Exceeded
// first idea - we will sort from the biggest to the smallest batteries to simulate batteries usage
// we will go through n elements each time decreasing them
// let m = batteries.size()
// Time complexity: O(max(batteries)*(m-n+1)*n)
// O(max(batteries)) -> remove 1 from n biggest nums as much as we can to make it 0
// O(m-n+1) -> resetting numbers to have only n-1 non-zero numbers (so m-n+1 numbers resetting)
// O(n) -> doing for each number in our n-size sliding window
// Space Complexity: O(n+m) -> 
long long maxRunTimeTLE(int n, vector<int>& batteries) {
    auto sortedBatteries = std::multiset<int, std::greater<int>>(batteries.begin(), batteries.end());
    std::vector<int> currUsedBatteries(n, 0);

    int minutes = 0;
    while(true) {
        for (int i = 0; i < n; i++) {
            auto currBatteryIt = sortedBatteries.begin();
            
            if (*currBatteryIt == 0) return minutes;

            currUsedBatteries[i] = *currBatteryIt;
            sortedBatteries.erase(currBatteryIt);
        }

        for (auto currBattery : currUsedBatteries) {
            sortedBatteries.insert(currBattery-1);
        }

        minutes++;
    }

    return 0;
}

// changed approach:
// GOAL: Find max time t to run n computers simultaneously
// CONSTRAINT: Need n*t total energy, so t ≤ SUM/n (theoretical max)
// 
// PROBLEM: Can't always achieve SUM/n due to large batteries
// example: n=2, batteries=[100,1,1], SUM=102, avg=51
//   - At t=51: battery[100] only contributes min(100,51)=51 to ONE computer
//   - Total usable: 51+1+1=53, but need 2*51=102 
//   - large battery can't be shared across computers simultaneously
//
// SOLUTION: If battery > SUM/n, dedicate it to one computer
//   - Remove from pool, decrease n, recalculate average
//   - Once all batteries ≤ avg, we can achieve perfect distribution via swapping
long long maxRunTime(int n, vector<int>& batteries) {
    sort(batteries.begin(), batteries.end());

    long long sum = std::accumulate(batteries.begin(), batteries.end(), 0);

    // dedicate batteries that exceed average to individual computers
    // they will power these computers for as long as needed
    // shrink battery array under consideration - now we will consider only n-1 batteries
    // for sum smaller by currently removed element
    while (batteries.back() > sum / n) {
        sum -= batteries.back();
        batteries.pop_back();
        n--;
    }

    // if we shring enough to have all batteries that we know they will be used completely
    // then the result is SUM/n for this shrinked array and decreased n
    return sum / n;
}

struct Test {
    int n;
    vector<int> batteries;
    long long expectedResult;

    std::string getInfo() const {
        stringstream ss;
        ss << "n: " << n << ", " << batteries;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Basic cases
        {2, {3, 3, 3}, 4},
        {2, {1, 1, 1, 1}, 2},
        
        // Edge cases - single computer
        {1, {5}, 5},
        {1, {1, 2, 3, 4, 5}, 15},
        
        // Large battery dominates
        {2, {100, 1, 1}, 2},
        {3, {100, 50, 1, 1, 1}, 3},
        
        // Perfect distribution (all batteries equal)
        {3, {5, 5, 5}, 5},
        {4, {10, 10, 10, 10}, 10},
        
        // All batteries need dedication
        {3, {100, 200, 300}, 100},
        
        // Multiple large batteries
        {2, {10, 10, 5, 5}, 15},
        {3, {20, 15, 10, 5, 5, 5}, 20},
        
        // One large, many small
        {2, {10, 1, 1, 1, 1, 1}, 5},
        {3, {50, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 4},
        
        // Exact average case
        {2, {6, 6}, 6},
        {3, {9, 9, 9}, 9},
        
        // All small batteries
        {5, {1, 1, 1, 1, 1}, 1},
        {3, {2, 2, 2, 2, 2, 2}, 4},
        
        // Mixed sizes
        {2, {5, 4, 3, 2, 1}, 7},
        {3, {10, 8, 6, 4, 2}, 10},
        
        // Large numbers (near constraints)
        {2, {1000000000, 1000000000}, 1000000000},
        {3, {1000000000, 500000000, 500000000}, 500000000},
        
        // More computers than batteries initially suggests
        {5, {20, 15, 10, 8, 7, 5, 3, 2, 1}, 12},
        
        // Boundary: n equals battery count
        {3, {10, 5, 3}, 3},
        
        // Progressive dedication
        {4, {100, 90, 80, 70, 10, 10, 10, 10}, 93},
    };

    runTests(tests, [](const Test& test){
        auto batteries = test.batteries;
        long long result = maxRunTime(test.n, batteries);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}