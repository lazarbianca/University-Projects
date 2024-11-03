#include <assert.h>
#include <iostream>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testRemoveFromKtoK()
{
    SortedIndexedList list = SortedIndexedList(relation1);
    assert(list.size() == 0);
    assert(list.isEmpty());
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    assert(list.size() == 5);
    assert(list.removeFromKtoK(2) == 3);

    assert(list.size() == 2);
    assert(list.search(1) == -1);
    assert(list.search(3) == -1);
    assert(list.search(5) == -1);
    assert(list.search(2) == 0);
    assert(list.search(4) == 1);

    assert(list.remove(0) == 2);
    assert(list.remove(0) == 4);
    assert(list.size() == 0);
    assert(list.isEmpty());
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    assert(list.size() == 5);

    assert(list.removeFromKtoK(10) == 0);
    assert(list.size() == 5);
    
    bool exceptionThrown = false;
    try
    {
        list.removeFromKtoK(-7);
    }
    catch (exception&)
    {
        std::cout << "oops" << endl;
        exceptionThrown = true;
    }
    assert(exceptionThrown == true);

    exceptionThrown = false;
    try
    {
        list.removeFromKtoK(0);
    }
    catch (exception&)
    {
        std::cout << "oops" << endl;
        exceptionThrown = true;
    }
    assert(exceptionThrown == true);
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

