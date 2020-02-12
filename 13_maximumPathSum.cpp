/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/maximum-path-sum/1

    Solution Description
    
    Let be maxL the maximum sum of a path toward a leaf in the left subtree, and
    maxR the maximum sum of a path toward a leaf in the right subtree.

    Base cases:
    - if the node is null, it returns INT_MIN
    - if the node is a leaf, it returns node.data
    - if the node is part of a path but not a leaf, it returns 
      (node.data + MAX(maxL, maxR))
    - if the node is a conjunction of two paths toward two different leaves,
      it calculates the maximum value as (node.value + maxL + maxR)

    Recursion:
    Call the function to the left node to find the maximum sum toward a leaf in
    the left subtree.
    Call the function to the right node to find the maximum sum toward a leaf in
    the right subtree.

    Time  Complexity: O(N)
    Space Complexity: O(1)
*/

#define MAX(a, b) ((a) > (b) ? (a) : (b)) 

int maxLeaf(struct Node * root, int & max)
{
    if (root == NULL) {
        return INT_MIN;
    }

    int maxL = maxLeaf(root->left, max);
    int maxR = maxLeaf(root->right, max);

    // root is a leaf
    if (maxL == INT_MIN && maxR == INT_MIN) {
        return root->data;
    }

    // root is the conjunction of two paths toward to 2 different leaves
    if ((maxL != INT_MIN) && (maxR != INT_MIN)) {
        int maxConj = root->data + maxL + maxR;
        max = MAX(max, maxConj);
    }

    // return the best path toward a leaf
    return root->data + MAX(maxL, maxR);
}

int maxPathSum(struct Node * root)
{
    int max = INT_MIN;
    maxLeaf(root, max);
    return max;
}