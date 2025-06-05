#include "__RBT__.h"

int main() {
    RBTREE tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(15);
    tree.insert(20);
    tree.insert(13);
    tree.insert(25);
    tree.insert(30);
    tree.insert(28);
    tree.insert(27);

    tree.preorder_print();
    tree.remove(20);
    tree.preorder_print();
    return 0;
}

