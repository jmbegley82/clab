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
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "Notype.h"

using jmb::common::Atom;
using jmb::common::Node;
using jmb::common::Integer;
using jmb::common::Float;
using jmb::common::String;
using jmb::common::Notype;
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
	Atom* nt = a1.Dereference("badvalue");
	if(nt->GetType() == Notype::type) {
		cout << "Dereference badvalue test passed" << endl;
		delete nt;
	}
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
	cout << "And again:" << endl;
	root2->Command("root1/a3");
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
	cout << "Now let's annoy it..." << endl;
	root->Command("a1=a9er");
	delete a1;
	delete a2;
	delete root;
	cout << endl;
}

void test5() {
	cout << ":::Integer Test:::" << endl;
	Node* root = new Node("root");
	Integer* i1 = new Integer("i1");
	Integer* i2 = new Integer("i2");
	Float* f1 = new Float("f1");
	Float* f2 = new Float("f2");

	root->AddChild(i1);
	root->AddChild(i2);
	root->AddChild(f1);
	root->AddChild(f2);
	cout << "Initializing." <<endl;
	i1->SetValue("0");
	i2->SetValue("0");
	f1->SetValue("0");
	f2->SetValue("0");
	cout << "Setting i1 to 12 manually." << endl;
	i1->SetValue("12");
	cout << "If '" << i1->GetValueAsStdString() <<
		"' = '12' SetValue worked and also GetValueAsStdString worked" << endl;
	cout << "Command i2=i1" << endl;
	root->Command("i2=i1");
	cout << "i2 = '" << i2->GetValueAsStdString() <<
		"'; should be 12 if Integer::OperatorEqu is working" << endl;
	cout << "Command i1=42" << endl;
	root->Command("i1=42");
	cout << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should still be 12" << endl;
	cout << "Setting i2 to 39 manually." << endl;
	i2->SetValue("39");
	cout << "Command i1-=i2" << endl;
	root->Command("i1-=i2");
	cout << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be -27 now if OperatorSub is cooperating" << endl;

	cout << "Setting i2 to -3 manually." << endl;
	i2->SetValue("-3");
	cout << "Command i1*=i2" << endl;
	root->Command("i1*=i2");
	cout << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be 81 now if OperatorMul is cooperating" << endl;

	cout << "Setting i2 to 9 manually." << endl;
	i2->SetValue("9");
	cout << "Command i1/=i2" << endl;
	root->Command("i1/=i2");
	cout << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be 9 now if OperatorDiv is cooperating" << endl;

	cout << "Setting i2 to 2 manually." << endl;
	i2->SetValue("2");
	cout << "Command i1^=i2" << endl;
	root->Command("i1^=i2");
	cout << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be 81 again if OperatorPow is cooperating" << endl;

	cout << "Command f1=i1" << endl;
	root->Command("f1=i1");
	cout << "f1 = '" << f1->GetValueAsStdString() <<
		"'; should be 81" << endl;

	cout << "Command f1/=i2" << endl;
	root->Command("f1/=i2");
	cout << "f1 = '" << f1->GetValueAsStdString() <<
		"'; should be 40.5" << endl;

        cout << "Command i1=f1" << endl;
        root->Command("i1=f1");
        cout << "i1 = '" << i1->GetValueAsStdString() <<
                "'; should be 41" << endl;

	cout << "Setting f2 = 3.14159" << endl;
	f2->SetValue("3.14159");
	cout << "f2 = '" << f2->GetValueAsStdString() <<
		"'; should be 3.14159" << endl;

	cout << "Command f1^=f2" << endl;
	root->Command("f1^=f2");
	cout << "f1 = '" << f1->GetValueAsStdString() <<
		"'; no idea what it'll be" << endl;

	cout << "Set f1=1048576, f2 = 0.25" << endl;
	f1->SetValue("1048576");
	f2->SetValue("0.25");
	cout << "Command f1^=f2" << endl;
	root->Command("f1^=f2");
	cout << "f1 = '" << f1->GetValueAsStdString() <<
		"'; should be 32" << endl;

	delete root;
	cout << endl;
}

void test6() {
	cout << "::String test::" << endl;
	Node root("root");
	String* s1 = new String("s1");
	String* s2 = new String("s2");
	String* s3 = new String("s3");
	Integer* i1 = new Integer("i1");
	Float* f1 = new Float("f1");
	root.AddChild(s1);
	root.AddChild(s2);
	root.AddChild(s3);
	root.AddChild(i1);
	root.AddChild(f1);
	s1->SetValue("This is the first half of the sentence; ");
	s2->SetValue("the other half is on the other side of the semicolon.");
	i1->SetValue("42");
	f1->SetValue("3.14159");
	root.Command("s3=s1");
	cout << "Get/Set test:  " << s3->GetValueAsStdString();
	root.Command("s3=s2");
	cout << s3->GetValueAsStdString() << endl;
	root.Command("s3=s1");
	root.Command("s3+=s2");
	cout << "OperatorEqu test:  " << s3->GetValueAsStdString() << endl;
	root.Command("s3=i1");
	cout << "Interpret test:  " << s3->GetValueAsStdString() << endl;
	root.Command("s3=f1");
	cout << "Interpret test:  " << s3->GetValueAsStdString() << endl;
	cout << endl;
}

int main(int argc, char** argv) {
	cout << "The test begins...  now." << endl;
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	return 0;
}
