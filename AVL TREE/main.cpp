#include <iostream>
#include "avl_tree.h"
using namespace std;

int main() {
    AVL_TREE tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    tree.print_inorder();
    return 0;
}
