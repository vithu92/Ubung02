#include "OrderedSet.h"
#include "MySet.h"

//ctor

OrderedSet::OrderedSet(size_t size) : Set(size), m_start(0) {}
OrderedSet::OrderedSet() : Set(), m_start(0) {}
OrderedSet::OrderedSet(const initializer_list<int> il) : Set(il), m_start(0) { sort(); }
OrderedSet::OrderedSet(const Set& set) : Set(set), m_start(0) { sort(); }
OrderedSet::OrderedSet(const int* values, size_t size) : Set(values, size), m_start(0) { sort(); }

//Beginn Methode, welche den Pointer des ersten Wertes zurückgibt
int* OrderedSet::begin() const { return m_values.get() + m_start; }

// Sortiermethode gemäss Standard-Library sort()
void OrderedSet::sort() {
	int* beg = begin();
	std::sort(beg, beg + m_size);
}


Set OrderedSet::merge(const Set& set) const {
	// Um eine sichere Casten zu gewährleisten.
	const OrderedSet* safteSetPtr = dynamic_cast<const OrderedSet*>(&set);
	if (safteSetPtr == nullptr) {
		return __super::merge(set);
	}
	else {
		const OrderedSet set = (*safteSetPtr);
		OrderedSet result(size() + set.size());
		int *pThis = begin(), *pSet = set.begin();
		size_t i = 0, j = 0;
		size_t tSize = size(), sSize = set.size();
		while (i < tSize || j < sSize) {
			int iVal = pThis[i], jVal = pSet[j], val;
			if (i < tSize && j < sSize) {
				if (iVal <= jVal) { val = iVal; i++; }
				if (iVal >= jVal) { val = jVal; j++; }
			}
			else if (i < tSize) {
				val = iVal; i++;
			}
			else if (j < sSize) {
				val = jVal; j++;
			} result[result.m_size++] = val;
		} return result;
	}
}

OrderedSet OrderedSet::getSmaller(int cutoff) const {
	for (size_t i(0); i < m_size; i++) {
		if ((*this)[i] >= cutoff) return OrderedSet(begin(), i);
	} return OrderedSet(*this);
}

OrderedSet OrderedSet::getLarger(int cutoff) const {
	for (size_t i(0); i < m_size; i++) {
		if ((*this)[i] > cutoff) return OrderedSet(begin() + i, m_size - i);
	} return OrderedSet();
}
