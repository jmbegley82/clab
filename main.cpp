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
#include "Node.h"

using jmb::common::Atom;
using jmb::common::Node;
using std::cout;
using std::endl;

void test1() {
	cout << ":::Atom test:::" << endl;
	Atom a1("a1");
	cout << a1.GetAbsolutePath() << " should be \'\' (empty)" << endl;
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

void test2() {
	cout << ":::Node test:::" << endl;
	
	Node* root1 = new Node("root1");
	Atom* a1 = new Atom("a1");
	Atom* a2 = new Atom("a2");
	Atom* a3 = new Atom("a3");
	root1->AddChild(a1);
	root1->AddChild(a2);
	root1->AddChild(a3);
	Node* root2 = new Node("root2");
	Atom* b1 = new Atom("b1");
	Atom* b2 = new Atom("b2");
	Atom* b3 = new Atom("b3");
	root2->AddChild(b1);
	root2->AddChild(b2);
	root2->AddChild(b3);
	
	cout << "root1:" << endl;
	root1->Command("");
	cout << endl << "root2:" << endl;
	root2->Command("");
	cout << endl;
	
	cout << "Move a2 from root1 to root2:" << endl;
	root2->AddChild(a2);
	cout << "root1:" << endl;
	root1->Command("");
	cout << endl << "root2:" << endl;
	root2->Command("");
	cout << endl;
	
	cout << "Move root1 into root2:" << endl;
	root2->AddChild(root1);
	cout << "root2:" << endl;
	root2->Command("");
	cout << endl;
	
	cout << "Now just a3:" << endl;
	//a3->Command("");
	root2->Command("/root1/a3");
	delete root2;
	cout << endl;
}

void test3() {
	cout << ":::Node path test:::" << endl;
	Node* root = new Node("root");
	Node* a1 = new Node("a1");
	Node* b1 = new Node("b1");
	a1->AddChild(b1);
	root->AddChild(a1);
	if(b1->GetRoot()->Dereference(b1->GetAbsolutePath()) == b1)
		cout << "Dereference test #1 pass" << endl;
	else cout << "Dereference test #1 fail" << endl;
	if(root->GetRoot() == root && root == root->Dereference(""))
		cout << "Dereference test #2 pass" << endl;
	else cout << "Dereference test #2 fail" << endl;
	delete root;
	cout << endl;
}

void test4() {
	cout << ":::Operator Test:::" << endl;
	Node* root = new Node("root");
	Node* a1 = new Node("a1");
	Node* a2 = new Node("a2");
	root->AddChild(a1);
	root->AddChild(a2);
	cout << "The next line should begin with Node::" << endl;
	root->Command("a1=a2");
	cout << endl;
}

int main(int argc, char** argv) {
	cout << "The test begins...  now." << endl;
	test1();
	test2();
	test3();
	test4();
	return 0;
}