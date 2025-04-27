#ifndef LW_RANDOM_TREE_H
#define LW_RANDOM_TREE_H

#include <string>

namespace rtree {

    struct node {
        int key;
        node *left;
        node *right;
        int size;

        explicit node(int new_data) : key{new_data}, left{nullptr}, right{nullptr}, size{1} {}

        node(int new_data, node *new_left, node *new_right) : key{new_data}, left{new_left}, right{new_right},
                                                              size{1} {}

        // won't delete it's children itself
        ~node() = default;
    };

    // modifiers

    // inserts a node into a binary tree, creating a root node if root==nullptr. returns root
    node *insert(node *root, int key);

    // deletes this binary tree, freeing the memory
    void clear(node *root);

    // operations

    // returns the height of the tree
    int height(node *root);

    // traversal

    // prints the tree in tree-like form
    void print_tree(const node *node, const std::string &prefix = "", bool is_left = false, bool is_end = true);


} // tree

#endif //LW_RANDOM_TREE_H
