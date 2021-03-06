#include "stdafx.h"

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <queue>
#include <stack>

struct ListNode
{
    int m_data;

    std::unique_ptr<ListNode> m_next;
};

//          4
//         / \
//        2   5
//       / \   \
//      1   3   6

struct TreeNode
{
    TreeNode(int d, int s)
        : data(d)
        , size(s)
    {}

    int data;
    int size;

    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
};

struct PTreeNode : public TreeNode
{
    std::shared_ptr<PTreeNode> parent;
};

using TreeNodePtr = std::shared_ptr<TreeNode>;
using PTreeNodePtr = std::shared_ptr<PTreeNode>;

bool checkBST(TreeNodePtr root)
{
    static TreeNodePtr prev = nullptr;

    if (root == nullptr)
        return true;

    // inorder traversal

    if (!checkBST(root->left))
        return false;

    if (prev != nullptr && prev->data >= root->data)
        return false;

    prev = root;

    return checkBST(root->right);
}

void levelOrderWalk(TreeNodePtr root)
{
    if (root == nullptr)
        return;

    std::queue<TreeNodePtr> Q;

    TreeNodePtr curr = root;

    while (curr != nullptr)
    {
        std::cout << curr->data << " ";

        if (curr->left != nullptr)
            Q.push(curr->left);

        if (curr->right != nullptr)
            Q.push(curr->right);

        if (Q.empty())
            break;

        curr = Q.front();
        Q.pop();
    }
}

TreeNodePtr minElement(TreeNodePtr root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }

    return root;
}

TreeNodePtr maxElement(TreeNodePtr root)
{
    while (root->right != nullptr)
    {
        root = root->right;
    }

    return root;
}

TreeNodePtr successor(PTreeNodePtr node)
{
    if (node->right)
    {
        return minElement(node->right);
    }

    while (node->parent && node->parent->right == node)
    {
        node = node->parent;
    }

    return node->parent;
}

TreeNodePtr findKthNode(TreeNodePtr root, int k)
{
    while (root && k)
    {
        int leftSize = (root->left ? root->left->size : 0);

        if (leftSize == k - 1)
            return root;

        if (leftSize >= k)
        {
            root = root->left;
        }
        else
        {
            k -= leftSize + 1;
            root = root->right;
        }
    }
    return nullptr;
}

// BST
TreeNodePtr firstLargerThanK(TreeNodePtr root, int k)
{
    TreeNodePtr first = nullptr;
    bool found = false;

    while (root)
    {
        if (root->data == k)
        {
            found = true;
            root = root->right;
        }
        else if (root->data > k)
        {
            first = root;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return (found ? first : nullptr);
}

TreeNodePtr lca(TreeNodePtr root, int v1, int v2)
{
    if (root == nullptr)
        return nullptr;

    if (root->data == v1 || root->data == v2)
        return root;

    TreeNodePtr l = lca(root->left, v1, v2);
    TreeNodePtr r = lca(root->right, v1, v2);

    if (l && r)
        return root;

    return (l != nullptr ? l : r);
}

void printAllAncestors(TreeNodePtr root, TreeNodePtr node)
{
    while (root)
    {
        std::cout << root->data << " ";
        if (root->data > node->data)
        {
            root = root->left;
        }
        else if (root->data < node->data)
        {
            root = root->right;
        }
        else
            break;
    }
}

void printAllCommonAncestors(TreeNodePtr root, int key1, int key2)
{
    auto lowestAncestor = lca(root, key1, key2);
    if (lowestAncestor == nullptr)
        return;

    printAllAncestors(root, lowestAncestor);
}

int getDepth(TreeNodePtr root, int key)
{
    if (root->data == key)
    {
        return 0;
    }

    if (root->data > key)
    {
        return 1 + getDepth(root->left, key);
    }

    return 1 + getDepth(root->right, key);
}

int distanceBetweenTwoNodesHelper(TreeNodePtr root, int key1, int key2)
{
    if (root == nullptr)
        return 0;

    if (key1 < root->data && key2 < root->data)
    {
        return distanceBetweenTwoNodesHelper(root->left, key1, key2);
    }

    if (key1 > root->data && key2 > root->data)
    {
        return distanceBetweenTwoNodesHelper(root->right, key1, key2);
    }

    if (root->data >= key1 && root->data <= key2)
    {
        return getDepth(root, key1) + getDepth(root, key2);
    }

    return -1;
}

int distanceBetweenTwoNodes(TreeNodePtr root, int key1, int key2)
{
    if (key1 > key2)
    {
        std::swap(key1, key2);
    }
    return distanceBetweenTwoNodesHelper(root, key1, key2);
}

class BSTIterator
{
public:
    BSTIterator(TreeNodePtr root)
    {
        pushAll(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext()
    {
        return !paths.empty();
    }

    /** @return the next smallest number */
    int next()
    {
        TreeNodePtr tmpNode = paths.top();
        paths.pop();
        pushAll(tmpNode->right);

        return tmpNode->data;
    }

private:
    void pushAll(TreeNodePtr root)
    {
        while (root != nullptr)
        {
            paths.push(root);
            root = root->left;
        }
    }

    std::stack<TreeNodePtr> paths;
};


int main()
{
    TreeNodePtr root = std::make_shared<TreeNode>(4, 5);
    root->right = std::make_shared<TreeNode>(5, 1);
    root->right->right = std::make_shared<TreeNode>(6, 0);

    root->left = std::make_shared<TreeNode>(2, 2);
    root->left->left = std::make_shared<TreeNode>(1, 0);
    root->left->right = std::make_shared<TreeNode>(3, 0);

    
    BSTIterator i = BSTIterator(root);
    while (i.hasNext())
        std::cout << i.next();

    std::cout << std::endl;
    levelOrderWalk(root);

    int kk;
    std::cin >> kk;
}
