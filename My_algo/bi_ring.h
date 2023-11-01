#ifndef STH
#define STH
#include <iostream>
#include <vector>

template <typename Key, typename Info>
class bi_ring {
private:
    struct Node {
        Key key;
        Info info;
        Node* next;
        Node* prev;
    };
    Node* head;
    int size;
public:
    class iterator {
    private:
        Node* n;
    public:
        iterator(Node* n) : n(n) {}
        iterator(const iterator& it) : n(it.n) {}
        iterator& operator=(const iterator& it) {
            n = it.n;
            return *this;
        }
        iterator& operator++() {
            n = n->next;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            n = n->next;
            return tmp;
        }
        iterator& operator--() {
            n = n->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator tmp = *this;
            n = n->prev;
            return tmp;
        }
        bool operator==(const iterator& it) const {
            return n == it.n;
        }
        bool operator!=(const iterator& it) const {
            return n != it.n;
        }
        Key& key() const {
            return n->key;
        }
        Info& info() const {
            return n->info;
        }
        Node* get_node() const {
            return n;
        }
    };
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(head->prev);
    }

    class const_iterator {
    private:
        Node* n;
    public:
        const_iterator(Node* n) : n(n) {}
        const_iterator(const const_iterator& it) : n(it.n) {}
        const_iterator& operator=(const const_iterator& it) {
            n = it.n;
            return *this;
        }
        const_iterator& operator++() {
            n = n->next;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            n = n->next;
            return tmp;
        }
        const_iterator& operator--() {
            n = n->prev;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            n = n->prev;
            return tmp;
        }
        bool operator==(const const_iterator& it) const {
            return n == it.n;
        }
        bool operator!=(const const_iterator& it) const {
            return n != it.n;
        }
        Key key() const {
            return n->key;
        }
        Info info() const {
            return n->info;
        }
    };
    const_iterator begin() const {
        return const_iterator(head);
    }
    const_iterator end() const {
        return const_iterator(head->prev);
    }

    bi_ring() { head = nullptr; size = 0; }
    ~bi_ring() { clear(); }
    bi_ring(const bi_ring& br);
    bi_ring& operator=(const bi_ring& br);

    bool empty() const;
    void print() const;
    void clear();
    int get_size() const {
        return size;
    }

    iterator insert(iterator position, const Key& k, const Info& i); //inserts before position
    iterator erase(iterator position);

    iterator push_front(const Key& k, const Info& i);
    iterator pop_front();
    iterator push_back(const Key& k, const Info& i);
    iterator pop_back();

    bool sortByInfo();

};

template<typename Key, typename Info>
bool bi_ring<Key, Info>::empty() const {
    return head == nullptr && size == 0;
}

template<typename Key, typename Info>
bool bi_ring<Key, Info>::sortByInfo() {
    if (empty()) {
        return false;
    }
    auto it = begin();
    do {
        auto it2 = it;
        ++it2;
        while (it2 != begin()) {
            if (it.info() > it2.info()) {
                std::swap(it.key(), it2.key());
                std::swap(it.info(), it2.info());
            }
            ++it2;
        }
        ++it;
    } while (it != begin());
    return true;
}

template<typename Key, typename Info>
bi_ring<Key, Info>::bi_ring(const bi_ring& br) {
    head = nullptr;
    size = 0;
    auto it = br.begin();
    do {
        push_back(it.key(), it.info());
        ++it;
    } while (it != br.begin());
}

template<typename Key, typename Info>
bi_ring<Key, Info>& bi_ring<Key, Info>::operator=(const bi_ring& br) {
    if (this == &br) {
        return *this;
    }
    clear();
    auto it = br.begin();
    do {
        push_back(it.key(), it.info());
        ++it;
    } while (it != br.begin());
    return *this;
}

//***********************Push and Pop***********************//
template <typename Key, typename Info>
typename bi_ring<Key, Info>::iterator bi_ring<Key, Info>::push_front(const Key& k, const Info& i) {
    Node* n = new Node;
    n->key = k;
    n->info = i;
    if (empty()) {
        n->next = n;
        n->prev = n;
        head = n;
    }
    else {
        n->next = head;
        n->prev = head->prev;
        head->prev->next = n;
        head->prev = n;
        head = n;
    }
    size++;
    return iterator(n);
}

template <typename Key, typename Info>
typename bi_ring<Key, Info>::iterator bi_ring<Key, Info>::pop_front() {
    if (empty()) {
        return iterator(nullptr);
    }
    Node* n = head;
    if (n->next == n) {
        head = nullptr;
    }
    else {
        head = n->next;
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    delete n;
    size--;
    return iterator(head);
}

template <typename Key, typename Info>
typename bi_ring<Key, Info>::iterator bi_ring<Key, Info>::push_back(const Key& k, const Info& i) {
    Node* n = new Node;
    n->key = k;
    n->info = i;
    if (empty()) {
        n->next = n;
        n->prev = n;
        head = n;
    }
    else {
        n->next = head;
        n->prev = head->prev;
        head->prev->next = n;
        head->prev = n;
    }
    size++;
    return iterator(n);
}

template <typename Key, typename Info>
typename bi_ring<Key, Info>::iterator bi_ring<Key, Info>::pop_back() {
    if (empty()) {
        return iterator(nullptr);
    }
    Node* n = head->prev;
    if (n->next == n) {
        head = nullptr;
    }
    else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    delete n;
    size--;
    return iterator(head);
}

//***********************Insert and Erase***********************//
template<typename Key, typename Info>
typename bi_ring<Key, Info>::iterator bi_ring<Key, Info>::insert(iterator position, const Key& k, const Info& i) {
    Node* n = new Node;
    n->key = k;
    n->info = i;
    Node* p = position.get_node();
    n->next = p;
    n->prev = p->prev;
    p->prev->next = n;
    p->prev = n;
    if (p == head) {
        head = n;
    }
    size++;
    return iterator(n);
}

template<typename Key, typename Info>
typename bi_ring<Key, Info>::iterator bi_ring<Key, Info>::erase(iterator position) {
    if (empty()) {
        return iterator(nullptr);
    }
    Node* n = position.get_node();
    if (n->next == n) {
        head = nullptr;
    }
    else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        if (n == head) {
            head = n->next;
        }
    }
    delete n;
    size--;
    return iterator(head);
}


//***********************Deleting***********************//
template<typename Key, typename Info>
void bi_ring<Key, Info>::clear() {
    if (empty()) {
        return;
    }
    Node* n = head;
    do {
        Node* tmp = n;
        n = n->next;
        delete tmp;
    } while (n != head);
    head = nullptr;
    size = 0;
    return;
}

//***********************Printing***********************//
template<typename Key, typename Info>
void bi_ring<Key, Info>::print() const {
    if (empty()) {
        std::cout << "Empty list\n" << std::endl;
        return;
    }
    Node* n = head;
    std::cout << "Start printing" << std::endl;
    do {
        std::cout << "Key[" << n->key << "] => " << n->info << std::endl;
        n = n->next;
    } while (n != head);
    std::cout << "End printing\n" << std::endl;
}


template<typename Key, typename Info>
bi_ring<Key, Info> merge(const std::vector<bi_ring<Key, Info>>& source) {
    bi_ring<Key, Info> result;
    for (auto br : source) {
        auto it = br.begin();
        do {
            result.push_back(it.key(), it.info());
            it++;
        } while (it != br.begin());
    }
    result.sortByInfo();
    return result;
}

// template<typename Key, typename Info>
// bi_ring<Key, Info> filter(const bi_ring<Key, Info>& source, bool (pred)(const Key&) ){

//     bi_ring<Key, Info> result;
//     auto it = source.begin();
//     do{
//         if(pred(it.key())){
//             result.push_back(it.key(), it.info());
//         }
//         it++;
//     }while(it != source.begin());
//     return result;
// }

// template<typename Key, typename Info>
// bi_ring<Key, Info> unique(const bi_ring<Key, Info>& source, Info (aggregate)(const Key&, const Info&, const Info&) ){

//         bi_ring<Key, Info> result;
//         for(auto it = source.begin(); it != source.end(); ++it){
//             bool found = false;
//             for(auto it2 = source.begin(); it2 != source.end(); ++it2){
//                 if(it.key() == it2.key() && it.info() != it2.info()){
//                     found = true;
//                     it2.info() = aggregate(it.key(), it.info(), it2.info());
//                     break;
//                 }
//             }
//             if(!found){
//                 result.push_front(it.key(), it.info());
//             }
//         }
//         return result;
// }




#endif