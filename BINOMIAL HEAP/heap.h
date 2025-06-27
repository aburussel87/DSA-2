#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    int key;
    int degree;
    Node *parent;
    Node *child;
    Node *next;

public:
    Node(int k)
    {
        key = k;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        next = nullptr;
    }
    int getKey() const
    {
        return key;
    }
    int getDegree() const
    {
        return degree;
    }
    Node *getParent() const
    {
        return parent;
    }
    Node *getChild() const
    {
        return child;
    }
    Node *getNext() const
    {
        return next;
    }
    void setKey(int k)
    {
        key = k;
    }
    void setDegree(int d)
    {
        degree = d;
    }
    void setParent(Node *p)
    {
        parent = p;
    }
    void setChild(Node *c)
    {
        child = c;
    }
    void setNext(Node *n)
    {
        next = n;
    }
    void incrementDegree()
    {
        degree++;
    }
    void decrementDegree()
    {
        if (degree > 0)
            degree--;
    }
};

class Advanced_Heap
{
private:
    Node *head;
    Node *merge(Node *a, Node *b);
    Node *link(Node *a, Node *b);
    Node *unionHeaps(Node *a, Node *b);
    void deleteTree(Node *h);
    void decreaseKey(Node *node, int newKey);
    Node *findNode(Node *h, int key);
    void printLevelOrder(Node *root, ofstream &output, bool console);

public:
    Advanced_Heap();
    ~Advanced_Heap();
    void insert(int key);
    int extractMin();
    void updateKey(int key, int newKey);
    void removeKey(int key);
    int findMin();
    void printHeap(ofstream &output, bool console = false);
    bool isEmpty() const;
};

Advanced_Heap::Advanced_Heap()
{
    head = nullptr;
}

Advanced_Heap::~Advanced_Heap()
{
    deleteTree(head);
}

bool Advanced_Heap::isEmpty() const
{
    return head == nullptr;
}

Node *Advanced_Heap::merge(Node *a, Node *b)
{
    if (!a)
        return b;
    if (!b)
        return a;

    Node *result = nullptr;
    if (a->getDegree() <= b->getDegree())
    {
        result = a;
        a = a->getNext();
    }
    else
    {
        result = b;
        b = b->getNext();
    }
    Node *tail = result;

    while (a && b)
    {
        if (a->getDegree() <= b->getDegree())
        {
            tail->setNext(a);
            a = a->getNext();
        }
        else
        {
            tail->setNext(b);
            b = b->getNext();
        }
        tail = tail->getNext();
    }
    tail->setNext(a ? a : b);
    return result;
}

Node *Advanced_Heap::link(Node *a, Node *b)
{
    if (a->getKey() > b->getKey())
        swap(a, b);
    b->setParent(a);
    b->setNext(a->getChild());
    a->setChild(b);
    a->incrementDegree();
    return a;
}

Node *Advanced_Heap::unionHeaps(Node *a, Node *b)
{
    Node *merged = merge(a, b);
    if (!merged)
        return nullptr;

    Node *prev = nullptr;
    Node *curr = merged;
    Node *next = curr->getNext();

    while (next)
    {
        if (curr->getDegree() != next->getDegree() ||
            (next->getNext() && next->getNext()->getDegree() == curr->getDegree()))
        {
            prev = curr;
            curr = next;
        }
        else
        {
            if (curr->getKey() <= next->getKey())
            {
                curr->setNext(next->getNext());
                link(curr, next);
            }
            else
            {
                if (prev)
                    prev->setNext(next);
                else
                    merged = next;
                link(next, curr);
                curr = next;
            }
        }
        next = curr->getNext();
    }
    return merged;
}

void Advanced_Heap::deleteTree(Node *h)
{
    if (!h)
        return;
    deleteTree(h->getChild());
    deleteTree(h->getNext());
    delete h;
}

void Advanced_Heap::insert(int key)
{
    Node *newNode = new Node(key);
    head = unionHeaps(head, newNode);
}

Node *Advanced_Heap::findNode(Node *h, int key)
{
    if (!h)
        return nullptr;
    if (h->getKey() == key)
        return h;

    Node *found = findNode(h->getChild(), key);
    if (found)
        return found;

    return findNode(h->getNext(), key);
}

void Advanced_Heap::decreaseKey(Node *node, int newKey)
{
    if (node->getKey() <= newKey)
        return;

    node->setKey(newKey);
    Node *current = node;
    Node *parent = current->getParent();

    while (parent && current->getKey() < parent->getKey())
    {
        int temp = current->getKey();
        current->setKey(parent->getKey());
        parent->setKey(temp);

        current = parent;
        parent = current->getParent();
    }
}

void Advanced_Heap::updateKey(int key, int newKey)
{
    Node *node = findNode(head, key);
    if (node)
    {
        if (newKey < node->getKey())
        {
            decreaseKey(node, newKey);
        }
        else
        {
            node->setKey(newKey);
        }
    }
}

int Advanced_Heap::extractMin()
{
    if (!head)
        return -1;

    Node *minNode = head;
    Node *prevMin = nullptr;
    Node *curr = head->getNext();
    Node *prev = head;

    while (curr)
    {
        if (curr->getKey() < minNode->getKey())
        {
            minNode = curr;
            prevMin = prev;
        }
        prev = curr;
        curr = curr->getNext();
    }

    if (prevMin)
        prevMin->setNext(minNode->getNext());
    else
        head = minNode->getNext();

    Node *child = minNode->getChild();
    Node *revChild = nullptr;
    while (child)
    {
        Node *next = child->getNext();
        child->setNext(revChild);
        child->setParent(nullptr);
        revChild = child;
        child = next;
    }

    head = unionHeaps(head, revChild);

    int minKey = minNode->getKey();
    delete minNode;
    return minKey;
}

int Advanced_Heap::findMin()
{
    if (!head)
        return -1;
    Node *minNode = head;
    Node *curr = head->getNext();

    while (curr)
    {
        if (curr->getKey() < minNode->getKey())
        {
            minNode = curr;
        }
        curr = curr->getNext();
    }
    return minNode->getKey();
}

void Advanced_Heap::removeKey(int key)
{
    Node *node = findNode(head, key);
    if (node)
    {
        decreaseKey(node, INT_MIN);
        extractMin();
    }
}

void Advanced_Heap::printLevelOrder(Node *root, ofstream &output, bool console)
{
    if (!root)
        return;
    queue<pair<Node *, int>> q;
    q.push({root, 0});
    int currentLevel = -1;

    while (!q.empty())
    {
        Node *node = q.front().first;
        int level = q.front().second;
        q.pop();

        if (level != currentLevel)
        {
            if (currentLevel != -1)
            {
                output << endl;
                if (console)
                {
                    cout << endl;
                }
            }
            output << "Level " << level << ": ";
            if (console)
            {
                cout << "Level " << level << ": ";
            }
            currentLevel = level;
        }
        if (console)
        {
            cout << node->getKey() << " ";
        }
        output << node->getKey() << " ";

        Node *child = node->getChild();
        while (child)
        {
            q.push({child, level + 1});
            child = child->getNext();
        }
    }
    if(console)
    {
        cout << endl;
    }
    output << endl;
}

void Advanced_Heap::printHeap(ofstream &output, bool console)
{
    output << "Printing Binomial Heap..." << endl;
    if (console)
    {
        cout << "Printing Binomial Heap..." << endl;
    }
    
    Node *current = head;
    while (current)
    {
        if(console)
        {
            cout << "Binomial Tree, B" << current->getDegree() << endl;
        }
        output << "Binomial Tree, B" << current->getDegree() << endl;
        printLevelOrder(current, output, console);
        current = current->getNext();
    }
}

