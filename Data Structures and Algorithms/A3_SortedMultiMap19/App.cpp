#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
//!!! do not use iterators internally
int main(){
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
