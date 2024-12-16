#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef LW_LINKED_LIST_H
#define LW_LINKED_LIST_H

#include <optional>
#include <iostream>

namespace llist {

    template<class T>
    class node {
    public:
        T data;
        node *next;
        node *prev;

        explicit node(T newData);

        node(T newData, node *newNext, node *newPrev);

        ~node() = default;
    };

    template<class T>
    class linked_list {
    private:
        llist::node<T> *head;
        llist::node<T> *tail;
        int _size;
    public:
        linked_list();

        ~linked_list();

        // node accessors
        llist::node<T> *begin() const; // O(1)
        llist::node<T> *end() const; // O(1)
        llist::node<T> *nodeAt(int index) const; // O(n)
        //capacity
        bool empty() const; // O(1)
        int size() const; // O(1)
        //modifiers
        void clear(); // O(n)
        void insert(llist::node<T> *node, T data); // before node O(n)
        void insert(int pos, T data); // before pos O(n)
        void erase(llist::node<T> *node); // O(1)
        void erase(int index); // O(n)
        void push_back(const T& data); // O(1)
        void pop_back(); //O(1)
        void push_front(const T& data); // O(1)
        void pop_front(); // O(1)
    };

} // llist

#include "linked_list.tpp"

#endif //LW_LINKED_LIST_H

#pragma clang diagnostic pop
