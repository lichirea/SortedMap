#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"
#include <iostream>
#include <cassert>
using namespace std;


bool f(TKey c1, TKey c2) {
    if (c1 <= c2) {
        return true;
    } else {
        return false;
    }
}

void test() {
    cout << "CUSTOM TEST" << endl;
    SortedMap sm(f);
    sm.add(4, 10);
    sm.add(2, 10);
    sm.add(7, 10);
    sm.add(5, 10);

    std::vector<TKey> v = sm.keySet();
    assert(v.size() == 4);
    assert(v[0] == 2);
    assert(v[1] == 4);
    assert(v[2] == 5);
    assert(v[3] == 7);

    sm.add(12, 10);
    v = sm.keySet();
    assert(v.size() == 5);
    assert(v[0] == 2);
    assert(v[1] == 4);
    assert(v[2] == 5);
    assert(v[3] == 7);
    assert(v[4] == 12);

    sm.remove(5);
    v = sm.keySet();
    assert(v.size() == 4);
    assert(v[0] == 2);
    assert(v[1] == 4);
    assert(v[2] == 7);
    assert(v[3] == 12);
}




int main() {
	testAll();
	testAllExtended();
    test();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


