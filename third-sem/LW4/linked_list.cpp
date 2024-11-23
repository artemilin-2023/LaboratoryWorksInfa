//
// Created by y7o4ka on 23.11.2024.
//

#include "linked_list.h"

namespace llist {

#pragma region node

    node::node(float newData) {
        data = newData;
        next = nullptr;
        prev = nullptr;
    }

    node::node(float newData, node *newNext, node *newPrev) {
        data = newData;
        next = newNext;
        prev = newPrev;
    }

    std::ostream &operator<<(std::ostream &os, const node &n) {
        os << "data: " << n.data << " next: ";
        if (n.next == nullptr) {
            os << "nullptr";
        } else {
            os << n.next->data << " (" << n.next << ")";
        }
        os << " prev: ";
        if (n.prev == nullptr) {
            os << "nullptr";
        } else {
            os << n.prev->data << " (" << n.prev << ")";
        }

        return os;
    }

#pragma endregion

#pragma region linked_list

    linked_list::linked_list() : head{}, tail{}, _size{} {}

    linked_list::~linked_list() {
        node *current = head;
        while (current != nullptr) {
            node *next = current->next;
            delete current;
            current = next;
        }
    }

    node *linked_list::begin() const { return head; }

    node *linked_list::end() const { return tail; }

    node *linked_list::nodeAt(int index) const {
        node *current = head;
        for (int i = 0; i < index; i++) {
            if (current == nullptr)
                return nullptr;
            current = current->next;
        }
        return current;
    }

    bool linked_list::empty() const { return head == nullptr; }

    int linked_list::size() const { return _size; }

    void linked_list::clear() {
        node *current = head;
        // delete nodes until there's none left
        while (current != nullptr) {
            node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    void linked_list::insert(node *after_node, float data) {
        if (after_node == nullptr) {
            return;
        }
        // link the new node to its neighbors
        node *new_node = new node(data, after_node, after_node->prev);
        // link the prev node to the new node
        if (after_node->prev != nullptr) {
            after_node->prev->next = new_node;
        }
        // link the after node to the new node
        after_node->prev = new_node;
        if (after_node == head) {
            head = new_node;
        }
        _size++;
    }

    void linked_list::insert(int pos, float data) {
        if (pos == _size) {
            push_back(data);
        } else if (pos == 0) {
            push_front(data);
        } else {
            insert(nodeAt(pos), data);
        }
    }

    void linked_list::erase(node *node) {
        if (node == nullptr) {
            return;
        }
        // link the prev node to the next one
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        }
        // link the next node to the prev one
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }
        // fix head
        if (node == head) {
            head = node->next;
        }
        // fix tail
        if (node == tail) {
            tail = node->prev;
        }
        delete node;
        _size--;
    }

    void linked_list::erase(int index) {
        erase(nodeAt(index));
    }

    void linked_list::push_back(float data) {
        node *new_node = new node(data);
        if (tail == nullptr) {
            // empty
            head = new_node;
            tail = new_node;
        } else {
            // link tail node to ours
            new_node->prev = tail;
            // link our node to tail
            tail->next = new_node;
            // fix tail
            tail = new_node;
        }
        _size++;
    }

    void linked_list::pop_back() {
        if (tail == nullptr) { return; }
        node *new_last = tail->prev;
        delete tail;
        tail = new_last;
        if (tail == nullptr) {
            // list is empty now, fix head
            head = nullptr;
        } else {
            // unlink new tail
            tail->next = nullptr;
        }
        _size--;
    }

    void linked_list::push_front(float data) {
        node *new_node = new node(data);
        if (head == nullptr) {
            // empty
            head = new_node;
            tail = new_node;
        } else {
            // link head node to ours
            new_node->next = head;
            // link our node to head
            head->prev = new_node;
            // fix head
            head = new_node;
        }
        _size++;
    }

    void linked_list::pop_front() {
        if (head == nullptr) { return; }
        node *new_first = head->next;
        delete head;
        head = new_first;
        if (head == nullptr) {
            // list is empty now, fix tail
            tail = nullptr;
        } else {
            // unlink new head
            head->prev = nullptr;
        }
    }

    node *linked_list::max(std::optional<std::reference_wrapper<int>> out_i) {
        node *current = head;
        if (current == nullptr) {
            return nullptr;
        }

        int i = 0, max_i = 0;
        node *max = current;

        while (current != nullptr) {
            if (current->data > max->data) {
                max_i = i;
                max = current;
            }
            current = current->next;
            i++;
        }
        if (out_i) {
            // callee needs max index too
            out_i->get() = max_i;
        }
        return max;
    }

    std::ostream &operator<<(std::ostream &os, const linked_list &l) {
        node *current = l.head;
        if (current == nullptr) {
            os << "empty list";
            return os;
        }
        int i = 0;
        while (current != nullptr) {
            os << '[' << i << "]=" << current->data << "->";
            current = current->next;
        }
        os << "nullptr";
        return os;
    }


#pragma endregion

} // llist
