/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/maximum-path-sum/1

    Solution Description
    Let be maxL the maximum sum of a path toward a leaf in the left subtree, and
    maxR the maximum sum of a path toward a leaf in the right subtree.

    Base cases:
    - node is null, return 0
    - node is a leaf, return node->data
    - node with both child nodes, return node->data + max(maxL, maxR)
    - node with only one child node, return node->data + child->data

    Recursion:
    - recursive call to find the maximum sum toward a leaf in the left subtree
    - recursive call to find the maximum sum toward a leaf in the right subtree

    Time  Complexity: O(N)
    Space Complexity: O(Height of the tree)
*/

int maxLeaf(struct Node * root, int & res)
{
    if (root == NULL) return 0;
    // leaf
    if (!root->left and !root->right) return root->data;

    const int maxL = maxLeaf(root->left, res);
    const int maxR = maxLeaf(root->right, res);

    // node with both child nodes
    if (root->left and root->right) {
        res = max(res, root->data + maxL + maxR);
        return root->data + max(maxL, maxR);
    }

    // node with only one child node
    return root->data + (root->left ? maxL : maxR);
}

int maxPathSum(struct Node * root)
{
    int res = INT_MIN;
    maxLeaf(root, res);
    return res;
}
