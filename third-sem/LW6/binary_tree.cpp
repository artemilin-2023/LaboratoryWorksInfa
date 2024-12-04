#include "binary_tree.h"

#include <iostream>
#include <limits>
#include <stack>
#include <queue>

namespace btree {
    node *insert(node *root, int key) {
        node *cur_node = root;
        node *parent{};

        // traverse down the tree finding a suitable place for a new node
        while (cur_node != nullptr) {
            // save the parent to later link to it
            parent = cur_node;
            if (key <= cur_node->key) {
                cur_node = cur_node->left;
            } else if (key > cur_node->key) {
                cur_node = cur_node->right;
            } else {
                std::cout << "Duplicate key: " << key << "!\n";
                return root;
            }
        }

        if (parent == nullptr) {
            // the tree was empty
            return new node(key);
        }

        if (key <= parent->key) {
            parent->left = new node(key);
        } else {
            parent->right = new node(key);
        }

        return root;
    }

    node *erase(node *root, int key) {
        node *cur_node = root;
        node *parent{};
        while (cur_node != nullptr) {
            if (key == cur_node->key) {
                break; // found the node we need to delete
            }
            parent = cur_node;
            if (key < cur_node->key) {
                cur_node = cur_node->left;
            } else {
                cur_node = cur_node->right;
            }
        }
        if (cur_node == nullptr) {
            // not found
            return root;
        }

        if (cur_node->left != nullptr && cur_node->right != nullptr) {
            // there are two children. we'll replace current node with
            // the smallest node in the right subtree, then delete it
            // because it will have at most one child (left one is nullptr)
            // , we can just use the code below to get rid of it
            node *successor_parent = cur_node;
            node *successor = cur_node->right;
            while (successor->left != nullptr) {
                successor_parent = successor;
                successor = successor->left;
            }
            cur_node->key = successor->key;
            cur_node = successor;
            parent = successor_parent;
        }

        // there is only one child (if there were two, we are now deleting its successor, which has at most one)
        // we'll need to reconnect this child to the parent node
        node *replacement_child;
        if (cur_node->left != nullptr) {
            replacement_child = cur_node->left;
        } else {
            replacement_child = cur_node->right;
        }

        if (parent == nullptr) {
            // the node to delete is root. make its child the new root
            root = replacement_child;
        } else if (cur_node->left == replacement_child) {
            // reconnect the parent's left node
            parent->left = replacement_child;
        } else {
            // reconnect the parent's right node
            parent->right = replacement_child;
        }

        delete cur_node; // finally
        return root;
    }

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

    node *search(node *root, int key) {
        while (root != nullptr) {
            if (key < root->key) {
                root = root->left;
            } else if (key > root->key) {
                root = root->right;
            } else {
                // key == root->key
                return root;
            }
        }
        return nullptr; // not found
    }

    int height(node *root) {
        if (root == nullptr) {
            return 0;
        }

        // level-order traversal (breadth-first search)

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
                // advance current level
                nodes_cur_level = nodes_next_level;
                nodes_next_level = 0;
            }
        }
        return height;
    }

    int node_count(node *root) {
        if (root == nullptr) {
            return 0;
        }

        // preorder traversal (depth-first search)

        std::stack<node *> stack{};
        stack.push(root);

        int count = 0;

        while (!stack.empty()) {
            node *cur_node = stack.top();
            stack.pop();
            count++;

            if (cur_node->right != nullptr) {
                stack.push(cur_node->right);
            }
            if (cur_node->left != nullptr) {
                stack.push(cur_node->left);
            }
        }
        return count;
    }

    std::tuple<node *, node *, node *, node *> min_max_2(node *root) {
        if (root == nullptr) {
            return {nullptr, nullptr, nullptr, nullptr};
        }

        node *minimum = root, *minimum_2{}, *maximum_2{}, *maximum = root;

        // find minimal (leftmost) element and it's parent
        while (minimum->left != nullptr) {
            minimum_2 = minimum;
            minimum = minimum->left;
        }
        // the parent could be second to min, but
        // if this minimal element has a right subtree
        if (minimum->right != nullptr) {
            // then the parent is bigger than the whole subtree

            // we need to find this subtree's leftmost element
            // it will be second to minimum
            minimum_2 = minimum->right;
            while (minimum_2->left != nullptr) {
                minimum_2 = minimum_2->left;
            }
        }

        // find maximal (rightmost) element and it's parent
        while (maximum->right != nullptr) {
            maximum_2 = maximum;
            maximum = maximum->right;
        }
        // the parent could be second to max, but
        // if this maximal element has a left subtree
        if (maximum->left != nullptr) {
            // then the parent is smaller than the whole subtree

            // we need to find this subtree's rightmost element
            // it will be second to maximum
            maximum_2 = maximum->left;
            while (maximum_2->right != nullptr) {
                maximum_2 = maximum_2->right;
            }
        }

        return {minimum, minimum_2, maximum_2, maximum};
    }

    void print_preorder(node *root) {
        if (root == nullptr) {
            return;
        }

        // preorder traversal (depth-first search)

        std::stack<node *> stack{};
        stack.push(root);

        while (!stack.empty()) {
            node *cur_node = stack.top();
            stack.pop();

            // do whatever you need with the node. here we're just printing it
            std::cout << cur_node->key << ' ';

            // we're putting the right first since the next iteration grabs the last element (left subtree)
            if (cur_node->right != nullptr) {
                stack.push(cur_node->right);
            }
            if (cur_node->left != nullptr) {
                stack.push(cur_node->left);
            }
        }
        std::cout << '\n';
    }

    void print_inorder(node *root) {
        if (root == nullptr) {
            return;
        }

        // inorder traversal (depth-first search)

        std::stack<node *> stack{};
        node *cur_node = root;

        // reach the left subtree, then its parent, then the right subtree
        while (cur_node != nullptr || !stack.empty()) {
            // push nodes onto stack until we reach the leftmost element
            while (cur_node != nullptr) {
                stack.push(cur_node);
                cur_node = cur_node->left;
            }

            // get it
            cur_node = stack.top();
            stack.pop();

            // we've reached the leftmost element in this subtree that we haven't traversed before
            // do whatever you need with the node. here we're just printing it
            std::cout << cur_node->key << ' ';

            // next we're advancing into this element's right subtree (if it exists)
            // if it doesn't exist cur_node will be null, and we'll just pop a parent off the stack
            cur_node = cur_node->right;
        }
        std::cout << '\n';
    }

    void print_postorder(node *root) {
        if (root == nullptr) {
            return;
        }

        // postorder traversal (depth-first search)

        std::stack<node *> stack{};
        node *cur_node = root;
        node *last_visited = nullptr; // we need it to determine from which subtree we're ascending to the parent

        while (cur_node != nullptr || !stack.empty()) {
            // push nodes onto stack until we reach the leftmost element
            while (cur_node != nullptr) {
                stack.push(cur_node);
                cur_node = cur_node->left;
            }

            node *parent_node = stack.top();

            // here it gets tricky
            // if right child exists, and we're ascending from the left child
            if (parent_node->right != nullptr && last_visited != parent_node->right) {
                // then advance into this element's right subtree (if it exists)
                cur_node = parent_node->right;
            } else {
                // else the right child doesn't exist, or we're ascending from the right child
                // either way we need to visit this parent node and move to it's parent

                // do whatever you need with the node. here we're just printing it
                std::cout << parent_node->key << ' ';

                last_visited = parent_node;
                stack.pop();
            }
        }
        std::cout << '\n';
    }

    void print_levelorder(node *root) {
        if (root == nullptr) {
            return;
        }

        // level-order traversal (breadth-first search)

        std::queue<node *> queue{};
        queue.push(root);

        while (!queue.empty()) {
            node *cur_node = queue.front();
            queue.pop();

            // do whatever you need with the node. here we're just printing it
            std::cout << cur_node->key << ' ';

            if (cur_node->left != nullptr) {
                queue.push(cur_node->left);
            }
            if (cur_node->right != nullptr) {
                queue.push(cur_node->right);
            }
        }
        std::cout << '\n';
    }

    void print_tree(const node *node, const std::string &prefix, bool is_left, bool is_end) {
        if (node == nullptr)
            return;
        std::cout << prefix;
        std::cout << (is_end ? "└" : "├") << (is_left ? "l" : "r") << "─";
        // print the value of the node
        std::cout << node->key << std::endl;
        // enter the next tree level - left and right branch
        print_tree(node->left, prefix + (is_end ? "    " : "│   "), true, node->right == nullptr);
        print_tree(node->right, prefix + (is_end ? "    " : "│   "), false, true);
    }

} // btree
