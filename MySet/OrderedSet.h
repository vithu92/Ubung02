#pragma once
# include "MySet.h"
# include <algorithm>

using namespace std;

class OrderedSet : public Set {
protected:
	size_t m_start;

	OrderedSet(size_t);

	void sort();

	int* begin() const override;
	Set merge(const Set&) const override;

public:
	// constructors and destructor
	OrderedSet();
	OrderedSet(const Set&);
	OrderedSet(const int*, size_t);
	OrderedSet(const initializer_list<int>);
	

	// instance methods

	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) kleiner als x sind
	OrderedSet getSmaller(int) const;

	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) groesser als x sind
	OrderedSet getLarger(int) const;
};

