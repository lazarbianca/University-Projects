#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TKEY -111111
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

typedef int(*Tfunction)(int,TKey);
/*//EXTRA OPERATION:
//finds and returns the maximum key from the MultiMap
//if the MultiMap is empty, it returns NULL_TKEY
		TKey maxKey() const;
	Obs: In order to have a NULL_TKEY, add to the beginning of the MultiMap.h file the following definition:
	#define NULL_TKEY 0
*/

class MultiMap
{
	friend class MultiMapIterator;

private:
	// Representation
	int mapCapacity;
	TElem* elements;  // array of key,value pairs
	int* next;	// array of next values
	int firstFree;	// first free position on which we can add a new element
	Tfunction h;
	int mapSize;

	void resize();

public:
	//finds and returns the maximum key from the MultiMap
	//if the MultiMap is empty, it returns NULL_TKEY
	TKey maxKey() const;

	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();


};

