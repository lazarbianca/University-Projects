#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

void SortedMultiMap::resize()
{
    int newCapacity = 2 * this->mapCapacity;
    TKey* newMapKeys = new TKey[newCapacity];
    SLLA** newMapValues = new SLLA * [newCapacity];
    int* newNextIndices = new int[newCapacity];

    // Copy old values 
    for (int i = 0; i < this->mapCapacity; i++) {
        newMapKeys[i] = mapKeys[i];
        newNextIndices[i] = mapNextIndices[i];
        newMapValues[i] = mapValues[i];
    }

    // Add next values for added space
    for (int i = this->mapCapacity; i < newCapacity; i++)
    {
        newMapValues[i] = nullptr;
        newNextIndices[i] = i + 1;
    }

    newNextIndices[newCapacity - 1] = -1;
    // destroy old arrays and replace them
    delete[] mapKeys;
    delete[] mapNextIndices;
    /*mapCurrentSize = this->mapCurrentSize;
    mapHead = this->mapHead;*/
    delete[] this->mapValues;
    mapKeys = newMapKeys;
    mapValues = newMapValues;
    mapNextIndices = newNextIndices;
    mapFirstFreePosition = mapCapacity;
    mapCapacity = newCapacity;
}
// Theta(newCapacity)

void SortedMultiMap::replace(TKey k, TValue oldValue, TValue newValue)
{
    SMMIterator it = SMMIterator(*this);
    it.first();
    while (it.valid())
    {
        if (it.getCurrent().first == k)
        {
            if (it.getCurrent().second == oldValue)
            {
                //we have to set the value to be newValue
                this->mapValues[it.currentElementIndex]->values[it.currentIndexOfValue] = newValue;
            }
        }
        it.next();
    }
}
// Theta(map.size())

SortedMultiMap::SortedMultiMap(Relation r) {
    //Implementation
    mapHead = -1;
    mapCapacity = 10;
    mapFirstFreePosition = 0;
    mapCurrentSize = 0;
    mapKeys = new TKey[mapCapacity];
    mapValues = new SLLA * [mapCapacity];
    mapNextIndices = new int[mapCapacity];
    for (int i = 0; i < mapCapacity; i++)
    {
        this->mapValues[i] = nullptr;
        this->mapNextIndices[i] = i + 1;
    }
    this->mapNextIndices[mapCapacity - 1] = -1;
    relation = r;
}
// Theta(mapCapacity)

void SortedMultiMap::SLLA::addToHead(TValue valueToAdd)
{
    if (this->currentSize == this->capacityOfCurrentSLLA)
    {
        this->resizeSLLA();
    }
    int positionToAdd = this->firstFreePositionOfCurrentSLLA;
    int nextFreePosition = this->nextIndices[positionToAdd];
    int oldHead = this->headOfCurrentSLLA;
    this->nextIndices[positionToAdd] = oldHead;
    this->headOfCurrentSLLA = positionToAdd;
    this->values[this->headOfCurrentSLLA] = valueToAdd;
    this->currentSize++;
    this->firstFreePositionOfCurrentSLLA = nextFreePosition;
}
// O(2*mapCapacity)   (if we have to resize),  Omega(1)  (no resize)

void SortedMultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    if (mapHead == -1) // smm is empty
    {
        // we are going to add the key on the firstFreePosition = 1
        if (this->mapCurrentSize == this->mapCapacity)
        {
            this->resize();
        }//might not need it here when smm is empty
        int positionToAdd = mapFirstFreePosition;
        int nextFreePosition = mapNextIndices[positionToAdd];
        this->mapNextIndices[positionToAdd] = -1;
        this->mapHead = positionToAdd;
        // adding the element
        this->mapKeys[this->mapHead] = c;
        this->mapCurrentSize++;
        this->mapValues[positionToAdd] = new SLLA();
        this->mapValues[positionToAdd]->addToHead(v);
        this->mapFirstFreePosition = nextFreePosition;
    }
    else
    {
        SMMIterator it = SMMIterator(*this);
        //if array contains elements, we have to iterate over the array to find the position to insert the key value pair
        int prev = -1;
        it.first();
        // sorted asc: return it.key <= target.key
        while (it.valid() && this->relation(this->mapKeys[it.currentElementIndex], c))
        {
            prev = it.currentElementIndex;
            it.next();
        }
        int current = it.currentElementIndex;  //the index of the crt element in the iteration of SMM
        if (it.valid() && it.map.mapKeys[current] == c)
        {
            //the key already exists; we add the value to its corresponding SLLA
            this->mapValues[current]->addToHead(v);
            return;
        }

        // we dont actually add and move things around, just simulate the adding by putting the
        // key value pair on the ***first free pos*** and changing the next indices so that it is in order
        // WE ACTUALLY ADD ON FIRST FREE POSITION!!!
        // for each case, we have to treat whether the key already exists! (& add value in its specific slla)

        //if the key does not exist, we add it
        if (this->mapCurrentSize == this->mapCapacity)
        {
            this->resize();
        }
        int positionToAdd = this->mapFirstFreePosition;
        this->mapFirstFreePosition = this->mapNextIndices[positionToAdd];
        this->mapKeys[positionToAdd] = c;
        this->mapValues[positionToAdd] = new SLLA();
        this->mapValues[positionToAdd]->addToHead(v);
        this->mapCurrentSize++;
        if (prev == -1)
        {
            //add to head - make the connections
            this->mapNextIndices[positionToAdd] = mapHead;
            this->mapHead = positionToAdd;
        }
        else {
            this->mapNextIndices[positionToAdd] = this->mapNextIndices[prev];
            this->mapNextIndices[prev] = positionToAdd;
        }
    }
}
//Best Case: Theta(1),      Worst Case: O(mapSize)  Worse Case: O(2*mapCapacity)    Total Case: O(mapSize) ?
//(add to head or empty amm)  (on the last pos)     (last pos PLUS resize)

vector<TValue> SortedMultiMap::search(TKey c) const {
    //TODO - Implementation
    vector<TValue> valuesOfGivenKey;
    SMMIterator it = SMMIterator(*this);
    //bool enteredWhile = false;
    it.first();

    while (it.valid())
    {
        if (it.getCurrent().first == c)
        {
            valuesOfGivenKey.push_back(it.getCurrent().second);
        }
        it.next();
    }
    return valuesOfGivenKey;
}
// O(mapSize)

bool SortedMultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    SMMIterator it = SMMIterator(*this);
    it.first();
    int indexOfPreviousKey = -1;
    while (it.valid())
    {
        if (this->mapKeys[it.currentElementIndex] == c)
        {
            if (it.currentIndexOfValue == 0) // the SLLA has only one value associated to the given key
            {   // an entire element will need to be deleted
                if (it.getCurrent().second == v) // if the value is the one we want to remove
                {
                    if (indexOfPreviousKey != -1) // the key we want to delete from the SMM is not the head
                    {
                        //connect previous with next (ignore the current in between)
                        int indexOfNextKey = this->mapNextIndices[it.currentElementIndex];
                        this->mapNextIndices[indexOfPreviousKey] = indexOfNextKey;
                    }
                    else
                    {
                        //we change the head of the SMM with the next value (ignore the old head)
                        this->mapHead = this->mapNextIndices[it.currentElementIndex];
                    }
                    // add the deleted position into mapFirstFreePosition
                    int positionToRemove = it.currentElementIndex;
                    int oldFirstFreePositionOfKeys = this->mapFirstFreePosition;
                    this->mapNextIndices[positionToRemove] = oldFirstFreePositionOfKeys;
                    this->mapFirstFreePosition = positionToRemove;

                    this->mapCurrentSize--;
                    return true;
                }
                //otherwise, the given (key,value) pair does not exist
                return false;
            }
            else
            {
                //we only remove the value from that key's slla
                //we have to parse it to search the position in the SLLA of the value v
                int previousIndexOfValueInSLLA = -1;
                int currentIndexOfValueInSLLA = this->mapValues[it.currentElementIndex]->headOfCurrentSLLA;
                while (currentIndexOfValueInSLLA != -1)
                {
                    if (this->mapValues[it.currentElementIndex]->values[currentIndexOfValueInSLLA] == v) 
                    {
                        //if the value on the current position in the SLLA is the value we want to remove
                        if (previousIndexOfValueInSLLA != -1) //if it's not the head of the SLLA
                        {
                            // connect previous and next
                            int nextIndexOfValueInSLLA = this->mapValues[it.currentElementIndex]->nextIndices[currentIndexOfValueInSLLA];
                            this->mapValues[it.currentElementIndex]->nextIndices[previousIndexOfValueInSLLA] = nextIndexOfValueInSLLA;
                        }
                        else // change the head of the SLLA to the next value
                        {
                            this->mapValues[it.currentElementIndex]->headOfCurrentSLLA = this->mapValues[it.currentElementIndex]->nextIndices[currentIndexOfValueInSLLA];
                        }
                        int oldFirstFreeIndexOfSLLA = this->mapValues[it.currentElementIndex]->firstFreePositionOfCurrentSLLA;
                        this->mapValues[it.currentElementIndex]->nextIndices[currentIndexOfValueInSLLA] = oldFirstFreeIndexOfSLLA;
                        this->mapValues[it.currentElementIndex]->firstFreePositionOfCurrentSLLA = currentIndexOfValueInSLLA;
                        this->mapValues[it.currentElementIndex]->currentSize--;
                        return true;
                    }
                    previousIndexOfValueInSLLA = currentIndexOfValueInSLLA;
                    currentIndexOfValueInSLLA = this->mapValues[it.currentElementIndex]->nextIndices[currentIndexOfValueInSLLA];
                }
                return false;
            }
            // return true immediately after successful removal
        }
        indexOfPreviousKey = it.currentElementIndex;
        it.next();
    }
    return false;
}
//Best Case: Theta(1), Worst Case: (last element) O(mapSize),  Total Case: O(mapSize)       mapSize = map.size()

int SortedMultiMap::size() const {
    //TODO - Implementation
    //return this->mapCurrentSize;

    //the size will be the sum of the number of elements of each SLLA
    int nrOfElements = 0;
    int currentPositionInSMM = this->mapHead;

    while (currentPositionInSMM != -1)
    {
        nrOfElements += this->mapValues[currentPositionInSMM]->currentSize;
        currentPositionInSMM = this->mapNextIndices[currentPositionInSMM];
    }
    return nrOfElements;
}
// O(mapCapacity)

bool SortedMultiMap::isEmpty() const {
    //TODO - Implementation
    return this->mapCurrentSize == 0;  //head == -1
}
//Theta(1)

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    //TODO - Implementation
    delete[] mapKeys;
    delete[] mapNextIndices;
    for (int i = 0; i < this->mapCapacity; i++) {
        if (mapValues[i] != nullptr) {
            delete mapValues[i];
        }
    }
    delete[] mapValues;
}
//O(mapCapacity)

SortedMultiMap::SLLA::SLLA() {
    headOfCurrentSLLA = -1;
    capacityOfCurrentSLLA = 5;
    firstFreePositionOfCurrentSLLA = 0;
    currentSize = 0;
    values = new TValue[capacityOfCurrentSLLA];
    nextIndices = new int[capacityOfCurrentSLLA];
}
//O(1)

SortedMultiMap::SLLA::~SLLA()
{
    delete[] values;
    delete[] nextIndices;
}
//O(1)

void SortedMultiMap::SLLA::resizeSLLA()
{
    int newCapacityOfCurrentSLLA = 2 * capacityOfCurrentSLLA;
    TValue* newValues = new TValue[newCapacityOfCurrentSLLA];
    int* newNextIndices = new int[newCapacityOfCurrentSLLA];
    // Copy old values 
    for (int i = 0; i < capacityOfCurrentSLLA; i++)
    {
        newValues[i] = values[i];
        newNextIndices[i] = nextIndices[i];
    }
    // Add next values for added space
    for (int i = capacityOfCurrentSLLA; i < newCapacityOfCurrentSLLA; i++)
    {
        newNextIndices[i] = i + 1;
    }
    newNextIndices[newCapacityOfCurrentSLLA - 1] = -1;
    // destroy old arrays and replace them
    this->~SLLA();
    /*delete[] values;
    delete[] nextIndices;*/
    values = newValues;
    nextIndices = newNextIndices;
    firstFreePositionOfCurrentSLLA = capacityOfCurrentSLLA;
    capacityOfCurrentSLLA = newCapacityOfCurrentSLLA;
}
//O(2*capacityOfCurrentSLLA)
