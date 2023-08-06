#ifndef CCTREE
#define CCTREE

#include <iostream>
#include <vector>
#include <string>



struct TreeNode
{
    int value;
    TreeNode *parent = NULL;
    TreeNode *left = NULL, *right = NULL;

    int get_value() { return this->value; };
    int is_leaf() { return (this->left == NULL && this->right == NULL); };

    TreeNode* insert(int value);
    int get_height();
    int get_balance()
    {
        int left_height = 0, right_height = 0;
        if (this->left != NULL) left_height = this->left->get_height();
        if (this->right != NULL) right_height = this->right->get_height();
        return left_height - right_height;
    }
    TreeNode *get_uncle();
};

int TreeNode::get_height()
{
    if (this->left == NULL && this->right == NULL)
        return 1;
    else if (this->left == NULL)
        return this->right->get_height() + 1;
    else
        return this->left->get_height() + 1;
}

TreeNode *TreeNode::get_uncle()
{
    if (this->parent != NULL && this->parent->parent != NULL)
    {
        if (this->parent == this->parent->parent->right)
        {
            return this->parent->parent->left;
        }
        return this->parent->parent->right;
    }
    return NULL;
}

TreeNode* TreeNode::insert(int value)
{
    if (value <= this->value)
    {
        if (left != NULL)
            return this->left->insert(value);
        else
        {
            this->left = new TreeNode;
            this->left->parent = this;
            this->left->value = value;
            return this->left;
        }
    }
    else
    {
        if (right != NULL)
            return this->right->insert(value);
        else
        {
            this->right = new TreeNode;
            this->right->parent = this;
            this->right->value = value;
            return this->right;
        }
    }
    return NULL;
}


class Tree
{
private:
    TreeNode *root = NULL;

    void balance(TreeNode* node);

    void in_order(TreeNode *node)
    {
        if (node->left != NULL)
            in_order(node->left);
        std::cout << ' ' << node->value << ' ';
        if (node->right != NULL)
            in_order(node->right);
    }

    void pre_order(TreeNode *node)
    {
        std::cout << ' ' << node->value << ' ';
        if (node->left != NULL)
            pre_order(node->left);
        if (node->right != NULL)
            pre_order(node->right);
    }

    void post_order(TreeNode *node)
    {
        if (node->left != NULL)
            post_order(node->left);
        if (node->right != NULL)
            post_order(node->right);
        std::cout << ' ' << node->value << ' ';
    }

public:
    Tree(){};
    ~Tree(){};

    void insert(int value);
    void in_order_traversal() { this->in_order(this->root); };
    void pre_order_traversal() { this->pre_order(this->root); };
    void post_order_traversal() { this->post_order(this->root); };
    TreeNode *get_node(int number);

    TreeNode *get_root() { return this->root; };
    void left_rotation(TreeNode *node);
    void right_rotation(TreeNode *node);
};

void Tree::balance(TreeNode* node)
{
    std::cout << "Balance: " << node->get_balance() << "\n";
    if (node->get_balance() < -1)
    {
        if (node->right->left != NULL)
        {
            this->left_rotation(node->right->left);
            this->right_rotation(node->right);
        }
        else
        {
            this->right_rotation(node->right);
        }
    }
    else if (node->get_balance() > 1)
    {
        if (node->left->right != NULL)
        {
            this->right_rotation(node->left->right);
            this->left_rotation(node->left);
        }
        else
        {
            this->left_rotation(node->left);
        }
    }
    else if (node->parent != NULL)
    {
        this->balance(node->parent);
    }
}

void Tree::insert(int value)
{
    if (root != NULL)
    {
        TreeNode *node = this->root->insert(value);
        this->balance(node);
    }
    else
    {
        this->root = new TreeNode;
        this->root->value = value;
    }
}

void Tree::right_rotation(TreeNode *node)
{
    if (node->parent != NULL)
    {
        TreeNode *father = node->parent;
        node->parent = father->parent;
        if (father->parent == NULL)
            this->root = node;
        else
        {
            if (father->parent->right == father)
            {
                father->parent->right = node;
            }
            else
            {
                father->parent->left = node;
            }
        }
        father->parent = node;
        father->right = node->left;
        if (node->left != NULL)
        {
            node->left->parent = father;
        }
        node->left = father;
    }
    else if (node->right != NULL)
    {
        this->right_rotation(node->right);
    }
}

void Tree::left_rotation(TreeNode *node)
{
    if (node->parent != NULL)
    {
        TreeNode *father = node->parent;
        node->parent = father->parent;
        if (father->parent == NULL)
            this->root = node;
        else
        {
            if (father->parent->left == father)
                father->parent->left = node;
            else
                father->parent->right = node;
        }
        father->parent = node;
        father->left = node->right;
        if (node->right != NULL)
            node->right->parent = father;
        node->right = father;
    }
    else if (node->left != NULL)
    {
        this->left_rotation(node->left);
    }
}

TreeNode *Tree::get_node(int number)
{
    if (this->root == NULL)
        return NULL;
    TreeNode *current = this->root;
    while (current->value != number && current != NULL)
    {
        if (current->value <= number)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return current;
}

#endif