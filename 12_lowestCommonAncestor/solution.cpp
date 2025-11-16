#include <iostream>
#include <utils/utils.hpp>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// recursive DFS
// O(n) time complexity
// O(h) where h is tree height, but the tree can be unbalanced so O(n) (worst case: tree as linked list)
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // return nodes to shows which one we have in current path
    if (root == p || root == q) return root;
    // leaves cannot be LCA so return null to show that we have nothing here
    if (!root) return nullptr;

    auto left = lowestCommonAncestor(root->left, p, q); // looking for p, q or LCA
    auto right = lowestCommonAncestor(root->right, p, q); // looking for p, q or LCA

    if (!left) return right; // if nothing in left branch/path then return right (null/LCA/p/q)
    else if (!right) return left; // similarily for the opposite site
    
    // if both subtrees are not nullptr then thay have wanted pointers: one has p and anther has q
    // because we can get something differen than nullptr only if we find p,q or LCA
    // if we find LCA in one of subtrees then we will have nullptr in the other one
    // because both p and q are available in that subtree where LCA is, so the another one is nullptr
    return root;
}

struct Test {
    TreeNode* root;
    TreeNode* p;
    TreeNode* q;
    int expectedVal;
    std::string description;
};

// Helper function to build tree and get node pointers
TreeNode* buildTree(const std::vector<int>& values, std::unordered_map<int, TreeNode*>& nodeMap) {
    if (values.empty() || values[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(values[0]);
    nodeMap[values[0]] = root;
    std::queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (i < values.size() && values[i] != -1) {
            curr->left = new TreeNode(values[i]);
            nodeMap[values[i]] = curr->left;
            q.push(curr->left);
        }
        i++;
        
        if (i < values.size() && values[i] != -1) {
            curr->right = new TreeNode(values[i]);
            nodeMap[values[i]] = curr->right;
            q.push(curr->right);
        }
        i++;
    }
    
    return root;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void runSolution() {
    std::vector<Test> tests;
    
    // Test 1: Example 1 - LCA of 5 and 1 is 3
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({3,5,1,6,2,0,8,-1,-1,7,4}, nodeMap);
        tests.push_back({root, nodeMap[5], nodeMap[1], 3, "Example 1: LCA of 5 and 1"});
    }
    
    // Test 2: Example 2 - LCA of 5 and 4 is 5 (ancestor of itself)
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({3,5,1,6,2,0,8,-1,-1,7,4}, nodeMap);
        tests.push_back({root, nodeMap[5], nodeMap[4], 5, "Example 2: Node is ancestor of itself"});
    }
    
    // Test 3: Example 3 - Simple tree
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({1,2}, nodeMap);
        tests.push_back({root, nodeMap[1], nodeMap[2], 1, "Example 3: Root and child"});
    }
    
    // Test 4: Both nodes in left subtree
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({3,5,1,6,2,0,8,-1,-1,7,4}, nodeMap);
        tests.push_back({root, nodeMap[6], nodeMap[7], 5, "Both nodes in left subtree"});
    }
    
    // Test 5: Both nodes in right subtree
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({3,5,1,6,2,0,8,-1,-1,7,4}, nodeMap);
        tests.push_back({root, nodeMap[0], nodeMap[8], 1, "Both nodes in right subtree"});
    }
    
    // Test 6: Two leaf nodes with same parent
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({3,5,1,6,2,0,8,-1,-1,7,4}, nodeMap);
        tests.push_back({root, nodeMap[7], nodeMap[4], 2, "Two siblings (leaf nodes)"});
    }
    
    // Test 7: Deep tree - nodes far apart
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({3,5,1,6,2,0,8,-1,-1,7,4}, nodeMap);
        tests.push_back({root, nodeMap[6], nodeMap[8], 3, "Nodes in different branches"});
    }
    
    // Test 8: Linear tree (all left)
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({1,2,-1,3}, nodeMap);
        tests.push_back({root, nodeMap[2], nodeMap[3], 2, "Linear tree (left branch)"});
    }
    
    // Test 9: Linear tree (all right)
    {
        std::unordered_map<int, TreeNode*> nodeMap;
        TreeNode* root = buildTree({1,-1,2,-1,3}, nodeMap);
        tests.push_back({root, nodeMap[1], nodeMap[3], 1, "Linear tree (right branch)"});
    }

    int testNum = 1;
    runTests(tests, [&](const Test& test) {
        TreeNode* result = lowestCommonAncestor(test.root, test.p, test.q);
        bool passed = (result && result->val == test.expectedVal);
        
        std::cout << "Test " << testNum++ << ": " << test.description;
        if (passed) {
            std::cout << " - PASSED" << std::endl;
        } else {
            std::cout << " - FAILED" << std::endl;
            std::cout << "  Expected: " << test.expectedVal;
            std::cout << ", Got: " << (result ? std::to_string(result->val) : "nullptr") << std::endl;
        }
        
        deleteTree(test.root);
        return passed;
    });
}