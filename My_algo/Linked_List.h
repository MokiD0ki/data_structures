#ifndef LINKED_LIST
#define LINKED_LIST
#include <iostream>

template<typename key, typename val>
class Linked_List
{
	struct Node
	{
		key _key;
		val _val;
		Node* next;
		Node(key _k, val _v) : _key(_k), _val(_v), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	int size;

public:
	//Iterator:
	template<typename K, typename V>
	class iterator {
	private:
		Node* current;

		iterator(Node* curr) : current(curr) {};
	public:
		iterator() : current(nullptr) {};

		iterator(const iterator& source) : current(source.current) {};

		//Operators
		iterator& operator++() {
			if (current) {
				current = current->next;
			}
			return *this;
		}

		iterator& operator++(int) {
			if (current) {
				current = current->next;
			}
			return *this;
		}

		iterator& operator= (const iterator& source) {
			current = source.current;
			return *this;
		}

		Node& operator* () {
			return *current;
		}

		Node* operator->() {
			return current;
		}

		bool operator==(const iterator& source) {
			return current == source.current;
		}

		bool operator!=(const iterator& source) {
			return current != source.current;
		}

		//Methods
		K getKey() const {
			return current->_key;
		}

		V getVal() const {
			return current->_val;
		}

		V& getValRef() {
			return current->_val;
		}

		friend class Linked_List;
	};
	typedef iterator<key, val> Iterator;
	typedef iterator<const key, const val> Const_Iterator;

	//default iterators
	Iterator begin() { return Iterator(head); }
	Iterator end() { return nullptr; }

	//constant iterators
	Const_Iterator constBegin() const { return Const_Iterator(head); }
	Const_Iterator constEnd() const { return nullptr; }

	//constructor/destructor
	Linked_List() : head(nullptr), tail(nullptr), size(0) {}
	~Linked_List() { this->clear(); }

	bool empty() const { return head == nullptr; }

	int getSize() const { return size; }

	//copy constructor
	Linked_List(const Linked_List<key, val>& newList) {
		this->copy(newList);
	}

	Linked_List<key, val>& operator= (const Linked_List<key, val>& newList) {
		this->copy(newList);
		return *this;
	}

	void copy(const Linked_List<key, val>& toCopy) {
		this->clear();
		Node* curr = toCopy.head;
		while (curr) {
			this->insert(curr->_key, curr->_val);
			curr = curr->next;
		}
	}

	void clear() {
		this->size = 0;
		Linked_List::Node* toDelete;

		while (head) {
			toDelete = head;
			head = head->next;
			delete toDelete;
		}

		head = nullptr;
		tail = nullptr;
	}

	void print() const {
		Node* curr = head;
		while (curr) {
			std::cout << "Key[" << curr->_key << "] = " << curr->_val << std::endl;
			curr = curr->next;
		}
	}

	bool find(const key _key) const {
		Node* curr = head;
		while (curr) {
			if (curr->_key == _key) {
				return true;
			}
			curr = curr->next;
		}

		return false;
	}

	void push_back(key _key, val _val) {
		Node* newNode = new Node(_key, _val);
		tail->next = newNode;
		tail = newNode;
	}

	void push_front(key _key, val _val) {
		Node* newNode = new Node(_key, _val);
		newNode->next = head;
		head = newNode;
	}

	void insert(key _key, val _val);
};

template<typename key, typename val>
void Linked_List<key, val>::insert(key _key, val _val) {
	this->size++;

	if (!head) {
		head = new Linked_List::Node(_key, _val);
		tail = head;
		return;
	}

	Linked_List::Node* curr = head;
	Linked_List::Node* newNode = new Node(_key, _val);

	if (curr->_key > _key) {
		newNode->next = head;
		head = newNode;
		return;
	}

	Linked_List::Node* prev = curr;
	curr = curr->next;

	while (curr) {
		if (_key < curr->_key) {
			prev->next = newNode;
			newNode->next = curr;
			return;
		}
		prev = curr;
		curr = curr->next;
	}

	prev->next = newNode;
	tail = newNode;
}

#endif