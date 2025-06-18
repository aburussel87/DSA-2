#include <bits/stdc++.h>
using namespace std;

struct node {
    node *lchild;
    node *rchild;
    node *parent;
    int height;
    int value;
    node(int value) {
        this->value = value;
        this->parent = this->rchild = this->lchild = nullptr;
        this->height = 0;
    }
};

class AVL_TREE {
    node *root;
    int size;

    node* leftRotate(node *z) {
        if (!z || !z->rchild) return nullptr;
        node *y = z->rchild;
        z->rchild = y->lchild;
        if (y->lchild) y->lchild->parent = z;
        y->parent = z->parent;
        if (z->parent == nullptr) root = y;
        else if (z == z->parent->lchild) z->parent->lchild = y;
        else z->parent->rchild = y;
        y->lchild = z;
        z->parent = y;
        fix_height(z);
        fix_height(y);
        return y;
    }

    node* rightRotate(node *z) {
        if (!z || !z->lchild) return nullptr;
        node *y = z->lchild;
        z->lchild = y->rchild;
        if (y->rchild) y->rchild->parent = z;
        y->parent = z->parent;
        if (z->parent == nullptr) root = y;
        else if (z == z->parent->lchild) z->parent->lchild = y;
        else z->parent->rchild = y;
        y->rchild = z;
        z->parent = y;
        fix_height(z);
        fix_height(y);
        return y;
    }

    void fix_height(node *z) {
        int hl = z->lchild ? z->lchild->height : -1;
        int hr = z->rchild ? z->rchild->height : -1;
        z->height = max(hl, hr) + 1;
    }

    int getBfactor(node *z) {
        int hl = z->lchild ? z->lchild->height : -1;
        int hr = z->rchild ? z->rchild->height : -1;
        return hl - hr;
    }

    node* insert_helper(node *root, int value) {
        if (root == nullptr) {
            size++;
            return new node(value);
        }
        if (value < root->value) {
            root->lchild = insert_helper(root->lchild, value);
            if (root->lchild) root->lchild->parent = root;
        } else if (value > root->value) {
            root->rchild = insert_helper(root->rchild, value);
            if (root->rchild) root->rchild->parent = root;
        } else {
            return root;
        }

        fix_height(root);
        int balance = getBfactor(root);

        if (balance <= -2) {
            if (getBfactor(root->rchild) > 0) {
                root->rchild = rightRotate(root->rchild);
                if (root->rchild) root->rchild->parent = root;
            }
            return leftRotate(root);
        } else if (balance >= 2) {
            if (getBfactor(root->lchild) < 0) {
                root->lchild = leftRotate(root->lchild);
                if (root->lchild) root->lchild->parent = root;
            }
            return rightRotate(root);
        }
        return root;
    }

    void destroy_helper(node *root) {
        if (root == nullptr) return;
        destroy_helper(root->lchild);
        destroy_helper(root->rchild);
        delete root;
    }

public:
    AVL_TREE() {
        root = nullptr;
        size = 0;
    }

    ~AVL_TREE() {
        destroy();
    }

    void destroy() {
        destroy_helper(root);
    }

    void insert(int value) {
        root = insert_helper(root, value);
    }
};
