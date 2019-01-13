#pragma once
#include <memory>
#include <iostream>

using namespace std;

class Set
{
protected:
	size_t m_size;
	const shared_ptr<int[]> m_values;

	// protected Datenstruktur (erlaubt Vererbung)
	Set(size_t size)
		: m_values(new int[size], default_delete<int[]>()), m_size(0)
	{
		cout << "private-ctor " << endl;
	}

	// geschuetzte Instanzmethoden
	virtual int *begin() const;

	int& operator[](size_t i) const;

	virtual Set merge(const Set& set) const;

	Set difference(const Set& set) const;

	Set difference(Set&& set) const;

	Set intersection(const Set& set) const;

	Set intersection(Set&& set) const;

public:
	// Default Konstruktor
	Set(const Set& s) : m_size(s.m_size), m_values(s.m_values) {};

	//Empty Konstruktor
	Set() : m_size(0) {}

	//Optional

	// Copy Konstruktor
	Set(const int* arr, size_t size) : Set(size) {
		for (size_t i(0); i < size; i++) {
			int val(arr[i]);
			if (!contains(val)) (*this)[m_size++] = val;
		}
	}

	//Konstruktor mit Liste als Parameter
	Set(const initializer_list<int> ilist) : Set(ilist.begin(), ilist.size()) {}

	//Instanzmethoden
	size_t size() const;
	bool isEmpty() const;
	bool contains(int e) const;
	bool containsAll(const Set& set) const;
	
	bool operator==(const Set& set) const { return containsAll(set) && set.containsAll(*this); }

	friend ostream& operator<<(ostream& stream, const Set& s) {
		const int* const ptr = s.begin();
		stream << "{";
		if (!s.isEmpty()) stream << ptr[0];
		for (size_t i = 1; i < s.m_size; ++i) 
			{
			stream << ", " << ptr[i];
			}
		stream << "}";
		return stream;
	}

	// statische Methoden
	static Set merge(const Set&, const Set&);
	static Set difference(const Set&, const Set&);
	static Set difference(Set&&, const Set&);
	static Set difference(Set&&, Set&&);
	static Set intersection(const Set&, const Set&);
	static Set intersection(const Set&, Set&&);
	static Set intersection(Set&&, const Set&);
	static Set intersection(Set&&, Set&&);
};

