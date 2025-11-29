# Intuition
The `LCA` is the deepest node where paths to p and q diverge. We can use `DFS` to search both subtrees and return information about which nodes we found (`p` or `q` if we found one of them or `nullptr` otherwise). \
If we find `p` in one subtree and `q` in another, the current node must be their `LCA`. \
If one of the wanted nodes is `LCA` then we return it eather way (the `root` will get `p` or `q` from one subtree and `nullptr` from the another one, so it will return this found node `p` or `q` as `LCA`).

# Approach
Use recursive DFS to traverse the tree:
1. Base case: if we find p or q, return that node
2. Recursively search left and right subtrees
3. If both subtrees return non-null values, it means p and q are in different subtrees, so current node is the LCA
4. If only one subtree returns non-null, it means either:
   - That subtree contains both p and q (LCA already found)
   - Or it contains only one of them (keep propagating upward)
5. Return the non-null result upward

# Complexity
- Time complexity: $O(n)$

- Space complexity: $O(n)$ (actually $O(h)$, where $h$ is tree height due to recursion stack. Since the tree can be unbalanced, $h$ can be $n$ in worst case (skewed tree like a linked list), so we have $O(n)$.)

# Code
```cpp []
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // return nodes to shows which one we have in current path
        if (root == p || root == q) return root;
        // leaves cannot be LCA so return null to show that we have nothing here
        if (!root || (!root->left && !root->right)) return nullptr;

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
};
```