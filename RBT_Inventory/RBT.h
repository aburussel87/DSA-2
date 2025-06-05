#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define RED_TXT "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE_TXT "\033[1;34m"
#define BLACK_TXT "\033[0;30m"
#define RESET "\033[0m"

enum Color
{
    RED,
    BLACK
};

struct Node
{
    Node *parent, *lchild, *rchild;
    int id;
    string name;
    int amount;
    Color col;

    Node(int id, string name, int amount)
        : id(id), name(name), amount(amount), col(RED),
          parent(nullptr), lchild(nullptr), rchild(nullptr) {}
};

class RBTREE
{
    Node *root;
    Node *NIL;
    int size;

    void insertion_fixup(Node *z);
    void deletion_fixup(Node *x);
    void LeftRotate(Node *x);
    void RightRotate(Node *x);
    void transplant(Node* u, Node* v);
    Node *minimum(Node *node);
    void destroy(Node *node);
    Node *find(Node *node, int id);
    void preOrder(Node *root);
    void sortedList_helper(Node *root);
    void color_print(Color color, const string &s)
    {
        if (color == RED)
            cout << RED_TXT << s << RESET;
        else
            cout << BLUE_TXT << s << RESET;
    }

public:
    RBTREE();
    ~RBTREE();

    bool insert(int id, string name, int amount);
    bool remove(int id);
    Node *find(int id) { return find(root, id); }
    bool decrease_amount(int id, int amount);
    void print_RBT()
    {
        preOrder(root);
        cout << endl;
    }
    void sortedList()
    {
        sortedList_helper(root);
    }
    int length() { return size; }
};

RBTREE::RBTREE()
{
    NIL = new Node(-1, "", -1);
    NIL->col = BLACK;
    NIL->lchild = NIL->rchild = NIL->parent = nullptr;
    root = NIL;
    size = 0;
}

RBTREE::~RBTREE()
{
    destroy(root);
    delete NIL;
}

void RBTREE::destroy(Node *node)
{
    if (node != NIL)
    {
        destroy(node->lchild);
        destroy(node->rchild);
        delete node;
    }
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

Node *RBTREE::find(Node *node, int id)
{
    if (node == NIL)
        return nullptr;
    if (id < node->id)
        return find(node->lchild, id);
    else if (id > node->id)
        return find(node->rchild, id);
    return node;
}

bool RBTREE::insert(int id, string name, int amount)
{
    Node *temp = root, *p = NIL;
    while (temp != NIL)
    {
        p = temp;
        if (id < temp->id)
            temp = temp->lchild;
        else if (id > temp->id)
            temp = temp->rchild;
        else
        {
            temp->name = name;
            temp->amount = amount;
            return true;
        }
    }

    Node *nNode = new Node(id, name, amount);
    nNode->lchild = nNode->rchild = NIL;
    nNode->parent = p;

    if (p == NIL)
        root = nNode;
    else if (id < p->id)
        p->lchild = nNode;
    else
        p->rchild = nNode;

    insertion_fixup(nNode);
    root->col = BLACK;
    size++;
    return true;
}

void RBTREE::insertion_fixup(Node *z)
{
    while (z->parent->col == RED)
    {
        if (z->parent == z->parent->parent->lchild)
        {
            Node *y = z->parent->parent->rchild;
            if (y->col == RED)
            {
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->rchild)
                {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->col = BLACK;
                z->parent->parent->col = RED;
                RightRotate(z->parent->parent);
            }
        }
        else
        {
            Node *y = z->parent->parent->lchild;
            if (y->col == RED)
            {
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->lchild)
                {
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

bool RBTREE::remove(int id) {
    Node *z = root;
    while (z != NIL) {
        if (id == z->id)
            break;
        else if (id < z->id)
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

Node *RBTREE::minimum(Node *node)
{
    while (node->lchild != NIL)
        node = node->lchild;
    return node;
}

void RBTREE::deletion_fixup(Node *x)
{
    while (x != root && x->col == BLACK)
    {
        if (x == x->parent->lchild)
        {
            Node *w = x->parent->rchild;
            if (w->col == RED)
            {
                w->col = BLACK;
                x->parent->col = RED;
                LeftRotate(x->parent);
                w = x->parent->rchild;
            }
            if (w->lchild->col == BLACK && w->rchild->col == BLACK)
            {
                w->col = RED;
                x = x->parent;
            }
            else
            {
                if (w->rchild->col == BLACK)
                {
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
        }
        else
        {
            Node *w = x->parent->lchild;
            if (w->col == RED)
            {
                w->col = BLACK;
                x->parent->col = RED;
                RightRotate(x->parent);
                w = x->parent->lchild;
            }
            if (w->rchild->col == BLACK && w->lchild->col == BLACK)
            {
                w->col = RED;
                x = x->parent;
            }
            else
            {
                if (w->lchild->col == BLACK)
                {
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

void RBTREE::LeftRotate(Node *x)
{
    if (x == NIL || x->rchild == NIL)
        return;
    Node *y = x->rchild;
    x->rchild = y->lchild;
    if (y->lchild != NIL)
        y->lchild->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->lchild)
        x->parent->lchild = y;
    else
        x->parent->rchild = y;

    y->lchild = x;
    x->parent = y;
}

void RBTREE::RightRotate(Node *x)
{
    if (x == NIL || x->lchild == NIL)
        return;
    Node *y = x->lchild;
    x->lchild = y->rchild;
    if (y->rchild != NIL)
        y->rchild->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->lchild)
        x->parent->lchild = y;
    else
        x->parent->rchild = y;

    y->rchild = x;
    x->parent = y;
}

bool RBTREE::decrease_amount(int id, int amount)
{
    Node *node = find(id);
    if (node == nullptr)
        return false;

    node->amount -= amount;
    if (node->amount <= 0)
        remove(id);
    return true;
}

void RBTREE::preOrder(Node *root)
{
    if (root == NIL)
        return;

    string label = to_string(root->id) + "_" + root->name;
    color_print(root->col, label);

    if (root->lchild != NIL || root->rchild != NIL)
        cout << "(";
    preOrder(root->lchild);
    if (root->lchild != NIL || root->rchild != NIL)
        cout << ",";
    preOrder(root->rchild);
    if (root->lchild != NIL || root->rchild != NIL)
        cout << ")";
}

void RBTREE::sortedList_helper(Node *root)
{
    if (root == NIL)
        return;
    sortedList_helper(root->lchild);
    string  s = to_string(root->id);
    color_print(root->col,s);
    cout<<" => ";
    s = root->name + " ("+to_string(root->amount)+")";
    color_print(root->col,s);
    cout<<endl;
    sortedList_helper(root->rchild);
}
