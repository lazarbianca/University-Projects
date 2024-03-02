#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <cassert>

using namespace std;


int main() {

	/*MultiMap m;
	m.add(5, 100);
	m.add(18, 100);
	m.add(16, 100);
	m.add(31, 100);
	m.add(13, 100);
	m.add(25, 100);
	assert(m.size() == 6);
	m.add(31, 100);
	cout << "firstFree = " << m.firstFree << "\n\n\n";

	for (int l = 0; l < m.mapCapacity; l++)
	{
		cout << l << " " << "key: " << m.elements[l].first << " value: " << m.elements[l].second << " -- next: " << m.next[l] << endl;
	}
	
	int count = 0;
	MultiMapIterator it = m.iterator();
	while (it.valid()) {
		cout << it.getCurrent().first << "  " << it.getCurrent().second << endl;
		count++;
		it.next();
	}
	assert(count == m.mapSize);*/
	
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
