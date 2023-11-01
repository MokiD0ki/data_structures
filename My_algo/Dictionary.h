#ifndef DICTIONARY
#define DICTIONARY

#include "Linked_List.h"
#include <map>

template<typename key, typename val>
class Dictionary
{
private:
	Linked_List<key, val> llist;

public:
	//constructors/destructor
	Dictionary() {

	}
	Dictionary(const Dictionary& newList) {
		this->llist = newList.llist;
	}
	Dictionary<key, val>& operator= (const Dictionary& newDict) {
		this->llist = newDict.llist;
		return *this;
	}
	~Dictionary() {
		llist.clear();
	}
	//Iterator
	typename Linked_List<key, val>::Iterator begin() { return llist.begin(); }
	typename Linked_List<key, val>::Iterator end() { return llist.end(); }

	//const Iterator
	typename Linked_List<key, val>::Const_Iterator constBegin() const { return llist.constBegin(); }
	typename Linked_List<key, val>::Const_Iterator constEnd() const { return llist.constEnd(); }

	val& operator[] (const key& _key) {
		auto it = llist.begin();
		while (it != llist.end()) {
			if (it.getKey() == _key)
				return it.getValRef();
			++it;
		}

		throw "key not found";
	}

	//Methods
	int getSize() { return llist.getSize(); }
	void print() { llist.print(); }

	void insert(key _key, val _val) {
		if (llist.find(_key)) {	// if we already have such element we don't change anything	
			return;
		}
		llist.insert(_key, _val);
	}
};

template<typename key, typename val>
Dictionary<key, val> join(const Dictionary<key, val>& l1, const Dictionary<key, val>& l2)
{
	Dictionary<key, val> ans;
	auto it1 = l1.constBegin();
	auto it2 = l2.constBegin();

	std::map<key, val> hashMap;
	for (it1; it1 != l1.constEnd(); it1++) {
		hashMap[it1.getKey()] += it1.getVal();
	}

	for (it2; it2 != l2.constEnd(); it2++) {
		hashMap[it2.getKey()] += it2.getVal();
	}

	for (const auto& i : hashMap) {
		ans.insert(i.first, i.second);
	}

	return ans;
}
#endif