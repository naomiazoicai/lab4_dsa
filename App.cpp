#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"


#include <iostream>
using namespace std;


int main() {
	testAll();
    testAllExtended();
    testGetMapInInterval();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


