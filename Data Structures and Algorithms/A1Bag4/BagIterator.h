#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	//TODO  - Representation
	int current; //the position of the current element in elements/frequency arrays
	int count;

	BagIterator(const Bag& c);
public:
	void first();
	//void next(int& count);
	void next();
	int getCount();
	int getFrequency();
	TElem getCurrent() const;
	bool valid() const;
};
