#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    Node *parent, *lchild, *rchild;
    int val;
    Color col;

    Node(int value) : parent(nullptr), lchild(nullptr), rchild(nullptr), val(value), col(RED) {}
};

class RBTREE {
    Node *root;
    Node *NIL;
    int size;

public:
    RBTREE();
    ~RBTREE();
    bool insert(int val);
    bool remove(int val);
    void preorder_print();

private:
    void insertion_fixup(Node *z);
    void deletion_fixup(Node *x);
    void LeftRotate(Node *x);
    void RightRotate(Node *x);
    Node* minimum(Node *node);
    Node* maximum(Node *node);
    void destroy(Node *node);
    void preorder_print(Node *node);
    void transplant(Node *u, Node *v);
};

RBTREE::RBTREE() {
    NIL = new Node(-1);
    NIL->col = BLACK;
    NIL->lchild = NIL->rchild = NIL->parent = NIL;
    root = NIL;
    size = 0;
}

RBTREE::~RBTREE() {
    destroy(root);
    delete NIL;
}

void RBTREE::destroy(Node *node) {
    if (node != NIL) {
        destroy(node->lchild);
        destroy(node->rchild);
        delete node;
    }
}

Node* RBTREE::minimum(Node *node) {
    while (node->lchild != NIL) node = node->lchild;
    return node;
}

Node* RBTREE::maximum(Node *node) {
    while (node->rchild != NIL) node = node->rchild;
    return node;
}

void RBTREE::LeftRotate(Node *x) {
    Node *y = x->rchild;
    x->rchild = y->lchild;
    if (y->lchild != NIL) y->lchild->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->lchild) x->parent->lchild = y;
    else x->parent->rchild = y;

    y->lchild = x;
    x->parent = y;
}

void RBTREE::RightRotate(Node *x) {
    Node *y = x->lchild;
    x->lchild = y->rchild;
    if (y->rchild != NIL) y->rchild->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->lchild) x->parent->lchild = y;
    else x->parent->rchild = y;

    y->rchild = x;
    x->parent = y;
}

bool RBTREE::insert(int val) {
    Node *temp = root, *p = NIL;
    while (temp != NIL) {
        p = temp;
        if (val < temp->val) temp = temp->lchild;
        else temp = temp->rchild;
    }

    Node *nNode = new Node(val);
    nNode->lchild = nNode->rchild = NIL;
    nNode->parent = p;

    if (p == NIL) root = nNode;
    else if (val < p->val) p->lchild = nNode;
    else p->rchild = nNode;

    insertion_fixup(nNode);
    root->col = BLACK;
    size++;
    return true;
}

void RBTREE::transplant(Node *u, Node *v) {
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->lchild)
        u->parent->lchild = v;
    else
        u->parent->rchild = v;
    v->parent = u->parent;
}

bool RBTREE::remove(int val) {
    Node *z = root;
    while (z != NIL) {
        if (val == z->val)
            break;
        else if (val < z->val)
            z = z->lchild;
        else
            z = z->rchild;
    }
    if (z == NIL) return false;

    Node *y = z;
    Color y_original_color = y->col;
    Node *x;

    if (z->lchild == NIL) {
        x = z->rchild;
        transplant(z, z->rchild);
    } else if (z->rchild == NIL) {
        x = z->lchild;
        transplant(z, z->lchild);
    } else {
        y = minimum(z->rchild);
        y_original_color = y->col;
        x = y->rchild;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->rchild);
            y->rchild = z->rchild;
            y->rchild->parent = y;
        }
        transplant(z, y);
        y->lchild = z->lchild;
        y->lchild->parent = y;
        y->col = z->col;
    }

    delete z;
    size--;

    if (y_original_color == BLACK)
        deletion_fixup(x);

    if (root != NIL)
        root->parent = NIL;

    return true;
}

void RBTREE::insertion_fixup(Node *z) {
    while (z->parent->col == RED) {
        if (z->parent == z->parent->parent->lchild) {
            Node *y = z->parent->parent->rchild;
            if (y->col == RED) {
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->rchild) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->col = BLACK;
                z->parent->parent->col = RED;
                RightRotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->lchild;
            if (y->col == RED) {
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->lchild) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->col = BLACK;
                z->parent->parent->col = RED;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->col = BLACK;
}

void RBTREE::deletion_fixup(Node *x) {
    while (x != root && x->col == BLACK) {
        if (x == x->parent->lchild) {
            Node *w = x->parent->rchild;
            if (w->col == RED) {
                w->col = BLACK;
                x->parent->col = RED;
                LeftRotate(x->parent);
                w = x->parent->rchild;
            }
            if (w->lchild->col == BLACK && w->rchild->col == BLACK) {
                w->col = RED;
                x = x->parent;
            } else {
                if (w->rchild->col == BLACK) {
                    w->lchild->col = BLACK;
                    w->col = RED;
                    RightRotate(w);
                    w = x->parent->rchild;
                }
                w->col = x->parent->col;
                x->parent->col = BLACK;
                w->rchild->col = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->lchild;
            if (w->col == RED) {
                w->col = BLACK;
                x->parent->col = RED;
                RightRotate(x->parent);
                w = x->parent->lchild;
            }
            if (w->rchild->col == BLACK && w->lchild->col == BLACK) {
                w->col = RED;
                x = x->parent;
            } else {
                if (w->lchild->col == BLACK) {
                    w->rchild->col = BLACK;
                    w->col = RED;
                    LeftRotate(w);
                    w = x->parent->lchild;
                }
                w->col = x->parent->col;
                x->parent->col = BLACK;
                w->lchild->col = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->col = BLACK;
}

void RBTREE::preorder_print() {
    preorder_print(root);
    cout << endl;
}

void RBTREE::preorder_print(Node *node) {
    if (node == NIL) return;

    // Print node value in red or black color
    if (node->col == RED)
        cout << "\033[31m" << node->val << "\033[0m ";
    else
        cout << "\033[30;1m" << node->val << "\033[0m ";

    // Print children with parentheses if any
    if (node->lchild != NIL || node->rchild != NIL) {
        cout << "(";
        preorder_print(node->lchild);
        cout << ",";
        preorder_print(node->rchild);
        cout << ")";
    }
}
