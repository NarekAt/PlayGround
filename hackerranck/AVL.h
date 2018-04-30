#pragma once
#include <algorithm>

// https://s3.amazonaws.com/hr-challenge-images/0/1436854305-b167cc766c-AVL_Tree_Rebalancing.svg.png

typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node;

int height(node* root)
{
    if (!root)
        return -1;

    return root->ht;
}

node* rotateRight(node* root)
{
    node* right = root;

    root = root->left;
    right->left = root->right;
    root->right = right;

    right->ht = max(height(right->left), height(right->right)) + 1;
    root->ht = max(height(root->left), height(root->right)) + 1;

    return root;
}

node* rotateLeft(node* root)
{
    node* left = root;

    root = root->right;
    left->right = root->left;
    root->left = left;

    left->ht = max(height(left->left), height(left->right)) + 1;
    root->ht = max(height(root->left), height(root->right)) + 1;

    return root;
}

node* insert(node* root, int val)
{
    if (!root)
    {
        root = new node;
        root->val = val;
        root->left = nullptr;
        root->right = nullptr;
        root->ht = 0;
        return root;
    }

    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    int lh = height(root->left);
    int rh = height(root->right);

    root->ht = max(lh, rh) + 1;

    int bf = lh - rh;

    // Left Left Case
    if (bf > 1 && val < root->left->val)
        return rotateRight(root);

    // Right Right Case
    if (bf < -1 && val > root->right->val)
        return rotateLeft(root);

    // Left Right Case
    if (bf > 1 && val > root->left->val)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (bf < -1 && val < root->right->val)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}