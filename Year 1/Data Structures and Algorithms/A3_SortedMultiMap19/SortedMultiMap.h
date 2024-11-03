//#pragma once
////DO NOT INCLUDE SMMITERATOR
//
////DO NOT CHANGE THIS PART
//#include <vector>
//#include <utility>
//typedef int TKey;
//typedef int TValue;
//typedef std::pair<TKey, TValue> TElem;
//#define NULL_TVALUE -111111
//#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
//using namespace std;
//class SMMIterator;
//typedef bool(*Relation)(TKey, TKey);
//
//
//class SortedMultiMap {
//	friend class SMMIterator;
//    private:
//        class SLLA
//        {
//        public:
//            TValue* values;
//            int* nextIndices;
//            int headOfCurrentSLLA;
//            int capacityOfCurrentSLLA;
//            int firstFreePositionOfCurrentSLLA;
//            int currentSize;
//            SLLA();
//            ~SLLA();
//            void resizeSLLA();
//            int getHead() { return headOfCurrentSLLA; }
//            void addToHead(TValue valueToAdd);
//            // EXTRA OPERATION!!!
//            // replaces the value currently mapped to a key k,with value newValue, oonly if the current value is
//            // equal to oldValue
//            // if  the current value is not oldValue, or if k is not in the sortedmap, nothing changes
//            // void replace(TKey k, TValue oldValue, TValue newValue);
//        };
//
//		//TODO - Representation
//        TKey* mapKeys;
//        SLLA* mapValues;
//        int* mapNextIndices;  // stores the indices of the next elements in the SLLA for each element in the elems array. 
//        //This creates a linked list structure for the elements with the same key.
//        int mapCapacity;
//        int mapHead; //index of the first element (the element with the smallest key, based on the relation)
//        int mapFirstFreePosition; //the index of the first free element in the SLLA. 
//        int mapCurrentSize;
//        Relation relation;
//
//        void resize();
//
//    public:
//
//    // constructor
//    SortedMultiMap(Relation r);
//
//	//adds a new key value pair to the sorted multi map
//    void add(TKey c, TValue v);
//
//	//returns the values belonging to a given key
//    vector<TValue> search(TKey c) const;
//
//	//removes a key value pair from the sorted multimap
//	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
//    bool remove(TKey c, TValue v);
//
//    //returns the number of key-value pairs from the sorted multimap
//    int size() const;
//
//    //verifies if the sorted multi map is empty
//    bool isEmpty() const;
//
//    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
//    SMMIterator iterator() const;
//
//    // destructor
//    ~SortedMultiMap();
//};


#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
    friend class SMMIterator;
private:
    class SLLA
    {
    public:
        TValue* values;
        int* nextIndices;
        int headOfCurrentSLLA;
        int capacityOfCurrentSLLA;
        int firstFreePositionOfCurrentSLLA;
        int currentSize;
        SLLA();
        ~SLLA();
        void resizeSLLA();
        int getHead() { return headOfCurrentSLLA; }
        void addToHead(TValue valueToAdd);
        // EXTRA OPERATION!!!
        // void replace(TKey k, TValue oldValue, TValue newValue);
    };

    //TODO - Representation
    TKey* mapKeys;
    SLLA** mapValues;
    int* mapNextIndices;  // stores the indices of the next elements in the SLLA for each element in the elems array. 
    //This creates a linked list structure for the elements with the same key.
    int mapCapacity;
    int mapHead; //index of the first element (the element with the smallest key, based on the relation)
    int mapFirstFreePosition; //the index of the first free element in the SLLA. 
    int mapCurrentSize;
    Relation relation;

    void resize();
public:
    // replaces the value currently mapped to a key k with value newValue, only if the current value is equal to oldValue
    // if  the current value is not oldValue, or if k is not in the sortedmap, nothing changes
    void replace(TKey k, TValue oldValue, TValue newValue);

    // constructor
    SortedMultiMap(Relation r);

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
