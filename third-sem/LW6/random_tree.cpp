#include "random_tree.h"

#include <iostream>
#include <limits>
#include <stack>
#include <queue>

namespace rtree {

    void fix_size(node *p) {
        if (!p) return;
        p->size = 1 + (p->left ? p->left->size : 0) + (p->right ? p->right->size : 0);
    }

    node *rotate_right(node *old_root)
    {
        node *new_root = old_root->left;
        if (!new_root) return old_root;
        old_root->left = new_root->right;
        new_root->right = old_root;
        new_root->size = old_root->size;
        fix_size(old_root);
        fix_size(new_root);
        return new_root;
    }

    node *rotate_left(node *old_root)
    {
        node *new_root = old_root->right;
        if (!new_root) return old_root;
        old_root->right = new_root->left;
        new_root->left = old_root;
        new_root->size = old_root->size;
        fix_size(old_root);
        fix_size(new_root);
        return new_root;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
    node *insert_root(node *root, int k)
    {
        if (!root) return new node(k);
        if (k < root->key) {
            root->left = insert_root(root->left, k);
            return rotate_right(root);
        } else {
            root->right = insert_root(root->right, k);
            return rotate_left(root);
        }
    }

    node *insert(node *root, int k)
    {
        if (!root) return new node(k);
        if (rand() % (root->size + 1) == 0) {
            return insert_root(root, k);
        }
        if (k < root->key) {
            root->left = insert(root->left, k);
        }
        else {
            root->right = insert(root->right, k);
        }
        fix_size(root);
        return root;
    }
#pragma clang diagnostic pop

    void clear(node *root) {
        if (root == nullptr) {
            return;
        }

        // copied from btree::print_postorder. refer to that for comments

        std::stack<node *> stack{};
        node *cur_node = root;
        node *last_visited = nullptr;

        while (cur_node != nullptr || !stack.empty()) {
            while (cur_node != nullptr) {
                stack.push(cur_node);
                cur_node = cur_node->left;
            }

            node *parent_node = stack.top();

            if (parent_node->right != nullptr && last_visited != parent_node->right) {
                cur_node = parent_node->right;
            } else {
                delete parent_node;

                last_visited = parent_node;
                stack.pop();
            }
        }
    }

    int height(node *root) {
        if (root == nullptr) {
            return 0;
        }

        // level-order traversal (breadth-first search)
        // copied from btree::height

        std::queue<node *> queue{};
        queue.push(root);

        int height = 0;
        int nodes_cur_level = 1; // only root
        int nodes_next_level = 0; // unknown

        while (!queue.empty()) {
            node *cur_node = queue.front();
            queue.pop();
            nodes_cur_level--; // processed a new node

            if (cur_node->left != nullptr) {
                queue.push(cur_node->left);
                nodes_next_level++;
            }
            if (cur_node->right != nullptr) {
                queue.push(cur_node->right);
                nodes_next_level++;
            }

            if (nodes_cur_level == 0) {
                // all nodes at current level are processed
                height++;
                // advance the current level
                nodes_cur_level = nodes_next_level;
                nodes_next_level = 0;
            }
        }
        return height;
    }

    void print_tree(const node *node, const std::string &prefix, bool is_left, bool is_end) {
        if (node == nullptr)
            return;
        std::cout << prefix;
        std::cout << (is_end ? "└" : "├") << (is_left ? "l" : "r") << "─";
        // print the value of the node
        std::cout << node->key << ' ' << node->size << std::endl;
        // enter the next tree level - left and right branch
        print_tree(node->left, prefix + (is_end ? "    " : "│   "), true, node->right == nullptr);
        print_tree(node->right, prefix + (is_end ? "    " : "│   "), false, true);
    }

} // tree