#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef LW_LINKED_LIST_H
#define LW_LINKED_LIST_H

#include <optional>
#include <iostream>

namespace llist {

    class node {
    public:
        float data;
        node *next;
        node *prev;

        explicit node(float newData);

        node(float newData, node *newNext, node *newPrev);

        ~node() = default;

        friend std::ostream &operator<<(std::ostream &os, const node &n);
    };

    class linked_list {
    private:
        node *head;
        node *tail;
        int _size;
    public:
        linked_list();

        ~linked_list();

        // node accessors
        node *begin() const; // O(1)
        node *end() const; // O(1)
        node *nodeAt(int index) const; // O(n)
        //capacity
        bool empty() const; // O(1)
        int size() const; // O(1)
        //modifiers
        void clear(); // O(n)
        void insert(node *node, float data); // before node O(n)
        void insert(int pos, float data); // before pos O(n)
        void erase(node *node); // O(1)
        void erase(int index); // O(n)
        void push_back(float data); // O(1)
        void pop_back(); //O(1)
        void push_front(float data); // O(1)
        void pop_front(); // O(1)
        // operators
        node *max(std::optional<std::reference_wrapper<int>> = {});

        // operator overloads
        friend std::ostream &operator<<(std::ostream &os, const linked_list &l);
    };

} // llist

#endif //LW_LINKED_LIST_H

#pragma clang diagnostic pop
