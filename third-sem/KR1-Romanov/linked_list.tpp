namespace llist {

#pragma region node

    template<class T>
    llist::node<T>::node(T newData) {
        data = newData;
        next = nullptr;
        prev = nullptr;
    }

    template<class T>
    llist::node<T>::node(T newData, node *newNext, node *newPrev) {
        data = newData;
        next = newNext;
        prev = newPrev;
    }

#pragma endregion

#pragma region linked_list

    template<class T>
    llist::linked_list<T>::linked_list() : head{}, tail{}, _size{} {}

    template<class T>
    llist::linked_list<T>::~linked_list() {
        llist::node<T> *current = head;
        while (current != nullptr) {
            llist::node<T> *next = current->next;
            delete current;
            current = next;
        }
    }

    template<class T>
    llist::node<T> *llist::linked_list<T>::begin() const { return head; }

    template<class T>
    llist::node<T> *llist::linked_list<T>::end() const { return tail; }

    template<class T>
    llist::node<T> *llist::linked_list<T>::nodeAt(int index) const {
        llist::node<T> *current = head;
        for (int i = 0; i < index; i++) {
            if (current == nullptr)
                return nullptr;
            current = current->next;
        }
        return current;
    }

    template<class T>
    bool llist::linked_list<T>::empty() const { return head == nullptr; }

    template<class T>
    int llist::linked_list<T>::size() const { return _size; }

    template<class T>
    void llist::linked_list<T>::clear() {
        llist::node<T> *current = head;
        // delete nodes until there's none left
        while (current != nullptr) {
            llist::node<T> *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    template<class T>
    void llist::linked_list<T>::insert(llist::node<T> *after_node, T data) {
        if (after_node == nullptr) {
            return;
        }
        // link the new node to its neighbors
        llist::node<T> *new_node = new node(data, after_node, after_node->prev);
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

    template<class T>
    void llist::linked_list<T>::insert(int pos, T data) {
        if (pos == _size) {
            push_back(data);
        } else if (pos == 0) {
            push_front(data);
        } else {
            insert(nodeAt(pos), data);
        }
    }

    template<class T>
    void llist::linked_list<T>::erase(llist::node<T> *node) {
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

    template<class T>
    void llist::linked_list<T>::erase(int index) {
        erase(nodeAt(index));
    }

    template<class T>
    void llist::linked_list<T>::push_back(const T &data) {
        llist::node<T> *new_node = new node(data);
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

    template<class T>
    void llist::linked_list<T>::pop_back() {
        if (tail == nullptr) { return; }
        llist::node<T> *new_last = tail->prev;
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

    template<class T>
    void llist::linked_list<T>::push_front(const T &data) {
        llist::node<T> *new_node = new node(data);
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

    template<class T>
    void llist::linked_list<T>::pop_front() {
        if (head == nullptr) { return; }
        llist::node<T> *new_first = head->next;
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


#pragma endregion

} // llist
