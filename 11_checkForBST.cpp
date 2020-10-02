/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/check-for-bst/1

    Solution Description
    Knowing that Binary Search Tree (BST) has the following invariants:
    - for each node x, every key found in the left subtree of x is less than or
      equal to the key found in x
    - for each node x, every key found in the right subtree of x is greater
      than or equal to the key found in x

    For the first invariant, we derive that every key in the left subtree of
    node x must be in the rage [-inf, x.key]
    For the second invariant, we derive that every key in the right subtree of
    node x must be in the range [x.key, +inf]

    It is simple to solve the problem in a recursive way.
    Base Cases:
    - if the node is NULL, it returns 1 (true)
    - if the data node is outside the range [min, max] it returns 0 (false)

    Recursion:
    Call the function to the left and to the right node.
    For the left node the min is the previous min, the max is the data node.
    For the right node the min is the data node, the max is the previous max.

    Time  Complexity: O(N)
    Space Complexity: O(Height of the BST)
*/

int isBSTUtil(struct Node* node, int min, int max)
{
    if (node == NULL) return 1;
    if (node->data <= min || node->data >= max) return 0;
    return isBSTUtil(node->left, min, node->data) and isBSTUtil(node->right, node->data, max);
}

bool isBST(Node* root)
{
    return isBSTUtil(root, INT_MIN, INT_MAX);
}