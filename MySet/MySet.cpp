#include "MySet.h"

using namespace std;


//Beginn methode
int* Set::begin() const {
	return m_values.get();
}

// Operator Methode - Mit Begin das erste Element und dann anzahl size_t addieren. 
int &Set::operator[](size_t i) const {
	return (*(begin() + i));
}

// Merge Methode
Set Set::merge(const Set& set) const {
	// erstelle eine neue Menge mit allen Elementen von this
	Set result(m_size + set.m_size);
	std::memcpy(result.begin(), begin(), m_size * sizeof(int));
	result.m_size = m_size;
	// fuege nur jene Elemente von set dazu, die in this noch nicht enthalten sind
	for (size_t i = 0; i < set.m_size; ++i) {
		if (!contains(set[i])) result[result.m_size++] = set[i];
	}
	return result;
}



Set Set::difference(const Set& set) const {
	Set result(set.m_size);
	for (size_t i(0); i < set.m_size; i++) {
		int val(set[i]);
		if (!contains(val)) result[result.m_size++] = val;
	} return result;
}

Set Set::difference(Set&& set) const {
	if (set.m_values.use_count() == 1) {
		size_t count(0);
		for (size_t i(0); i < set.m_size; i++) {
			int val(set[i]);
			if (!contains(val)) set[count++] = val;
		} set.m_size = count;
		return set;
	}
	else return difference(set);
}


Set Set::intersection(const Set& set) const {
	Set res(m_size);
	for (size_t i(0); i < set.m_size; i++) {
		int val(set[i]);
		if (contains(val)) res[res.m_size++] = val;
	} return res;
}

Set Set::intersection(Set&& set) const {
	if (set.m_values.use_count() == 1) {
		size_t count(0);
		for (size_t i(0); i < set.m_size; i++) {
			int val(set[i]);
			if (contains(val)) set[count++] = val;
		} set.m_size = count;
		return set;
	}
	else return intersection(set);
}

bool Set::contains(const int value) const
{

	for (size_t i = 0; i < size(); ++i) {
		if (begin()[i] == value) {
			return true;
		}
	}

	return false;
}

bool Set::containsAll(const Set& set) const
{
	for (size_t i = 0; i < set.size(); ++i) {
		if (!contains(set[i])) {
			return false;
		}
	}

	return true;
}

bool Set::isEmpty() const {
	return m_size == 0;
}

size_t Set::size() const {
	return m_size;
}

// Merge Funktion
Set Set::merge(const Set& set1, const Set& set2) {
	return set1.merge(set2);
}

// Difference Funktion
Set Set::difference(const Set& set1, const Set& set2) {
	return set2.difference(set1);
}

// Difference Funktion mit Move Semantik (nur Lesezugriff)
Set Set::difference(Set && set1, const Set & set2) {
	return set2.difference(std::move(set1));
}

// Difference Funktion mit Move Semantik
Set Set::difference(Set && set1, Set && set2) {
	return set2.difference(std::move(set1));
}

// Intersection Funktion
Set Set::intersection(const Set& set1, const Set& set2) {
	return set1.intersection(set2);
}

// Intersection Funktion mit Move Semantik
Set Set::intersection(Set&& set1, Set&& set2) {
	return set1.intersection(move(set2));
}

// Intersection Funktion mit Move Semantik (nur Lesezugriff)
Set Set::intersection(const Set& set1, Set&& set2) {
	return set1.intersection(move(set2));
}

// Intersection Funktion mit Move Semantik (nur Lesezugriff)
Set Set::intersection(Set&& set1, const Set& set2) {
	return set2.intersection(move(set1));
}

