/*
 *  main.cpp
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */


#include <iostream>
#include <string>
#include "Atom.h"

using jmb::common::Atom;
using std::cout;
using std::endl;

void test1() {
	cout << ":::Atom test:::" << endl;
	Atom a1("a1");
	cout << a1.GetPath() << " should be \'/a1\'" << endl;
	cout << (int)a1.GetType() << " should be \'-1\'" << endl;
	if(a1.Dereference("") == &a1)
		cout << "Dereference test passed" << endl;
	else cout << "Dereference test failed" << endl;
	if(a1.Dereference("/") == &a1)
		cout << "Dereference root test passed" << endl;
	else cout << "Dereference root test failed" << endl;
	if(a1.Dereference("badvalue") == NULL)
		cout << "Dereference badvalue test passed" << endl;
	else cout << "Dereference badvalue test failed" << endl;
	cout << endl;
}

int main(int argc, char** argv) {
	cout << "The test begins...  now." << endl;
	test1();
	return 0;
}