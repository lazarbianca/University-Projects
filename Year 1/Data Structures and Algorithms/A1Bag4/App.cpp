#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {

	testFilter();
	cout << "Filter passed\n";
	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All tests over" << endl;
	system("pause");

}