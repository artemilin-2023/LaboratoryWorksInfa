#ifndef LW_BINARY_TREE_H
#define LW_BINARY_TREE_H

#include <tuple>
#include <string>

namespace btree {

    struct node {
        int key;
        node *left;
        node *right;

        explicit node(int new_data) : key{new_data}, left{nullptr}, right{nullptr} {}

        node(int new_data, node *new_left, node *new_right) : key{new_data}, left{new_left}, right{new_right} {}

        ~node() = default; // won't delete it's children itself
    };

    // modifiers

    // inserts a node into a binary tree, creating a root node if root==nullptr. returns root
    node *insert(node *root, int key);

    // removes a key from the binary tree. returns root
    node *erase(node *root, int key);

    // deletes this binary tree, freeing the memory
    void clear(node *root);

    // operations

    // searches for a key. returns node containing the key or nullptr
    node *search(node *root, int key);

    // returns the height of the tree
    int height(node *root);

    // returns the node count of the tree
    int node_count(node *root);

    // returns minimal, last to minimal, last to maximal and maximal elements
    // each element can be nullptr if no suitable one was found
    std::tuple<node *, node *, node *, node *> min_max_2(node *root);

    // traversal

    // prints the tree as array in preorder
    void print_preorder(node *root);

    // prints the tree as array in order
    void print_inorder(node *root);

    // prints the tree as array in postorder
    void print_postorder(node *root);

    // prints the tree as array in level-order
    void print_levelorder(node *root);

    // prints the tree in tree-like form
    void print_tree(const node *node, const std::string &prefix = "", bool is_left = false, bool is_end = true);

} // btree

#endif //LW_BINARY_TREE_H
