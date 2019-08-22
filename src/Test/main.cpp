/*
 *  main.cpp
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */


#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include "Clab.h"
#include "Log.h"
#include "Types.h"
#include "Atom.h"
#include "Node.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
//#include "TestMachine.h"
//#include "Video.h"
//#include "Manager.h"
#include "Notype.h"
#include "Time.h"
#include "Clock.h"
#include "FileOps.h"
#include "StringManip.h"
#include "FastNode.h"

using jmb::common::Log;
using jmb::common::GetHomePrefix;
using jmb::common::GetAppPrefix;
using jmb::common::GetLogPrefix;
using jmb::common::Atom;
using jmb::common::Node;
using jmb::common::FastNode;
using jmb::common::Integer;
using jmb::common::Float;
using jmb::common::String;
//using jmb::common::TestMachine;
//using jmb::common::Video;
//using jmb::common::Manager;
using jmb::common::Notype;
//using jmb::common::GetTimeInMsecAsDouble;
using jmb::common::Clock;
using jmb::common::Types::AddMapping;
using jmb::common::ClabInit;
using jmb::common::GetHexString;
using jmb::common::GetFirstWord;
using jmb::common::GetFirstWordEtc;
using jmb::common::GetString;
using jmb::common::CommandSplitRev;
using std::string;
using std::endl;
using std::stringstream;

void test0() {
	*Log << ":::Version Variable Test:::" << endl;
	*Log << "Library reports version string:  " << jmb::common::ClabVersionString() << endl;
	*Log << "Library reports major version:   " << jmb::common::ClabVersionMajor() << endl;
	*Log << "Library reports minor version:   " << jmb::common::ClabVersionMinor() << endl;
	*Log << "Linked using major version:   " << CLAB_VERSION_MAJOR << endl;
	*Log << "Linked using minor version:   " << CLAB_VERSION_MINOR << endl;
	*Log << endl;
}

void test1() {
	*Log << ":::Atom test:::" << endl;
	Atom a1("a1");
	*Log << a1.GetAbsolutePath() << " should be \'\' (empty)" << endl;
	*Log << (int)a1.GetType() << " should be \'-1\'" << endl;
	if(a1.Dereference("") == &a1)
		*Log << "Dereference test passed" << endl;
	else *Log << "Dereference test failed" << endl;
	if(a1.Dereference("/") == &a1)
		*Log << "Dereference root test passed" << endl;
	else *Log << "Dereference root test failed" << endl;
	Atom* nt = a1.Dereference("badvalue");
	if(nt->GetType() == Notype::type) {
		*Log << "Dereference badvalue test passed" << endl;
		delete nt;
	}
	else *Log << "Dereference badvalue test failed" << endl;
	*Log << endl << endl;
}

void test2() {
	*Log << ":::Node test:::" << endl;
	
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
	
	*Log << "root1:" << endl;
	root1->Command("");
	*Log << endl << "root2:" << endl;
	root2->Command("");
	*Log << endl;
	
	*Log << "Move a2 from root1 to root2:" << endl;
	root2->AddChild(a2);
	*Log << "root1:" << endl;
	root1->Command("");
	*Log << endl << "root2:" << endl;
	root2->Command("");
	*Log << endl;
	
	*Log << "Move root1 into root2:" << endl;
	root2->AddChild(root1);
	*Log << "root2:" << endl;
	root2->Command("");
	*Log << endl;
	
	*Log << "Now just a3:" << endl;
	//a3->Command("");
	root2->Command("/root1/a3");
	*Log << "And again:" << endl;
	root2->Command("root1/a3");
	delete root2;
	*Log << endl << endl;
}

void test3() {
	*Log << ":::Node path test:::" << endl;
	Node* root = new Node("root");
	Node* a1 = new Node("a1");
	Node* b1 = new Node("b1");
	a1->AddChild(b1);
	root->AddChild(a1);
	if(b1->GetRoot()->Dereference(b1->GetAbsolutePath()) == b1)
		*Log << "Dereference test #1 pass" << endl;
	else *Log << "Dereference test #1 fail" << endl;
	if(root->GetRoot() == root && root == root->Dereference(""))
		*Log << "Dereference test #2 pass" << endl;
	else *Log << "Dereference test #2 fail" << endl;
	delete root;
	*Log << endl << endl;
}

void test4() {
	*Log << ":::Operator Test:::" << endl;
	Node* root = new Node("root");
	Node* a1 = new Node("a1");
	Node* a2 = new Node("a2");
	root->AddChild(a1);
	root->AddChild(a2);
	*Log << "The next line should begin with Node::" << endl;
	root->Command("a1=a2");
	*Log << "Now let's annoy it..." << endl;
	root->Command("a1=a9er");
	delete a1;
	delete a2;
	delete root;
	*Log << endl << endl;
}

void test5() {
	*Log << ":::Integer Test:::" << endl;
	Node* root = new Node("root");
	Integer* i1 = new Integer("i1");
	Integer* i2 = new Integer("i2");
	Float* f1 = new Float("f1");
	Float* f2 = new Float("f2");

	root->AddChild(i1);
	root->AddChild(i2);
	root->AddChild(f1);
	root->AddChild(f2);
	*Log << "Initializing." <<endl;
	i1->SetValue("0");
	i2->SetValue("0");
	f1->SetValue("0");
	f2->SetValue("0");
	*Log << "Setting i1 to 12 manually." << endl;
	i1->SetValue("12");
	*Log << "If '" << i1->GetValueAsStdString() <<
		"' = '12' SetValue worked and also GetValueAsStdString worked" << endl;
	*Log << "Command i2=i1" << endl;
	root->Command("i2=i1");
	*Log << "i2 = '" << i2->GetValueAsStdString() <<
		"'; should be 12 if Integer::OperatorEqu is working" << endl;
	//*Log << "Command i1=42" << endl;
	//root->Command("i1=42");
	//*Log << "i1 = '" << i1->GetValueAsStdString() <<
	//	"'; should still be 12" << endl;
	*Log << "Setting i2 to 39 manually." << endl;
	i2->SetValue("39");
	*Log << "Command i1-=i2" << endl;
	root->Command("i1-=i2");
	*Log << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be -27 now if OperatorSub is cooperating" << endl;

	*Log << "Setting i2 to -3 manually." << endl;
	i2->SetValue("-3");
	*Log << "Command i1*=i2" << endl;
	root->Command("i1*=i2");
	*Log << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be 81 now if OperatorMul is cooperating" << endl;

	*Log << "Setting i2 to 9 manually." << endl;
	i2->SetValue("9");
	*Log << "Command i1/=i2" << endl;
	root->Command("i1/=i2");
	*Log << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be 9 now if OperatorDiv is cooperating" << endl;

	*Log << "Setting i2 to 2 manually." << endl;
	i2->SetValue("2");
	*Log << "Command i1^=i2" << endl;
	root->Command("i1^=i2");
	*Log << "i1 = '" << i1->GetValueAsStdString() <<
		"'; should be 81 again if OperatorPow is cooperating" << endl;

	*Log << "Command f1=i1" << endl;
	root->Command("f1=i1");
	*Log << "f1 = '" << f1->GetValueAsStdString() <<
		"'; should be 81" << endl;

	*Log << "Command f1/=i2" << endl;
	root->Command("f1/=i2");
	*Log << "f1 = '" << f1->GetValueAsStdString() <<
		"'; should be 40.5" << endl;

        *Log << "Command i1=f1" << endl;
        root->Command("i1=f1");
        *Log << "i1 = '" << i1->GetValueAsStdString() <<
                "'; should be 41" << endl;

	*Log << "Setting f2 = 3.14159" << endl;
	f2->SetValue("3.14159");
	*Log << "f2 = '" << f2->GetValueAsStdString() <<
		"'; should be 3.14159" << endl;

	*Log << "Command f1^=f2" << endl;
	root->Command("f1^=f2");
	*Log << "f1 = '" << f1->GetValueAsStdString() <<
		"'; no idea what it'll be" << endl;

	*Log << "Set f1=1048576, f2 = 0.25" << endl;
	f1->SetValue("1048576");
	f2->SetValue("0.25");
	*Log << "Command f1^=f2" << endl;
	root->Command("f1^=f2");
	*Log << "f1 = '" << f1->GetValueAsStdString() <<
		"'; should be 32" << endl;

	delete root;
	*Log << endl << endl;
}

void test6() {
	*Log << ":::String test:::" << endl;
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
	*Log << "Get/Set test:      " << s3->GetValueAsStdString();
	root.Command("s3=s2");
	*Log << s3->GetValueAsStdString() << endl;
	root.Command("s3=s1");
	root.Command("s3+=s2");
	*Log << "OperatorEqu test:  " << s3->GetValueAsStdString() << endl << endl;
	root.Command("s3=i1");
	*Log << "Interpret test:  Integer into String:  " << s3->GetValueAsStdString() << endl;
	root.Command("s3=f1");
	*Log << "Interpret test:    Float into String:  " << s3->GetValueAsStdString() << endl;
	root.Command("i1=s3");
	*Log << "Interpret test:  String into Integer:  " << i1->GetValueAsStdString() << endl;
	root.Command("f1=s3");
	*Log << "Interpret test:    String into Float:  " << f1->GetValueAsStdString() << endl;
	*Log << endl << endl;
}

void test7() {
	*Log << ":::Spaces/syntax update test:::" << endl;
	Node root("root");
	String* s1 = new String("s1");
	String* s2 = new String("s2");
	String* s3 = new String("s3");
	root.AddChild(s1);
	root.AddChild(s2);
	root.AddChild(s3);
	s1->SetValue("String one");
	s2->SetValue("String two");
	root.Command("s3 = s1");
	root.Command("s3 += s2");
	*Log << "Have some concatenated strings:  " << s3->GetValueAsStdString() << endl;
	*Log << endl << endl;
}

void test8() {
	*Log << ":::Test 8:::" << endl;
	Node root("root");
	root.Command("Integer i1");
	root.Command("Integer i2 = 512");
	root.Command("String s1");
	root.Command("i1 = i2");
	root.Command("s1 = i1");

	Integer* i1 = (Integer*)root.Dereference("i1");
	Integer* i2 = (Integer*)root.Dereference("i2");
	String* s1 = (String*)root.Dereference("s1");
	assert(s1 != NULL);

	*Log << "if " << s1->GetValueAsStdString() << " = 512, test passed!" << endl;

	root.Command("s1 = \"This sentence should contain spaces and no quotes\"");
	*Log << s1->GetValueAsStdString() << endl;
	root.Command("Float f1 = 1.21");
	root.Command("s1 = f1");
	*Log << s1->GetValueAsStdString() << " == 1.21?" << endl;
	root.Command("s1 = this statement should cause an exception to be thrown");
	*Log << s1->GetValueAsStdString() << " should still be 1.21" << endl;

	root.Command("i1 = this command should fail");
	root.Command("Float f1 = this should fail also");

	Float* f1 = (Float*)root.Dereference("f1");
	assert(f1 != NULL);

	*Log << "New command:  s1 := clear" << endl;
	root.Command("s1 := clear");
	*Log << "s1 is now \"" << s1->GetValueAsStdString() << "\"" << endl;
	*Log << "New command:  f1 := round" << endl;
	root.Command("f1 := round");
	*Log << "f1 is now \"" << f1->GetValueAsStdString() << "\"" << endl;

	*Log << "Float f2 = 8.0" << endl;
	root.Command("Float f2 = 8.0");
	Float* f2 = (Float*)root.Dereference("f2");

	*Log << "New command:  f2 := inverse" << endl;
	root.Command("f2 := inverse");
	*Log << "f2 = " << f2->GetValueAsStdString() << "; should be 0.125" << endl;
	root.Command("f2 := inverse");
	*Log << "f2 = " << f2->GetValueAsStdString() << "; should be 8 again" << endl;

	*Log << endl << endl;
}

/*
void test9() {
	*Log << ":::Test 9 from outer space:::" << endl;
	
	Manager root("root");
	//root.Command("Video VideoMgr");
	//root.Command("Event EventMgr");
	Video* v1 = (Video*)root.Dereference("VideoMgr");
	assert(v1 != NULL);
	*Log << "VideoMgr reports a value of:  " << v1->GetValueAsStdString() << endl;
	root.Command("");
	root.Tick(0);
	root.Command("/VideoMgr/windowPosX=200");
	root.Command("");
	root.Tick(0);
	root.Tick(0);
	Clock clk;
	double time = clk.GetTime();
	double target = time + 10000;
	double t_slice = 1000 / 120;
	double currentMsec = time;
	double prevMsec = currentMsec - t_slice;
	while(clk.GetTime() < target) {
		double delta = clk.GetTime() - prevMsec;
		while(delta < t_slice) {
			*Log << "Debug main:  frame limiting..." << endl;
			jmb::common::SleepMsec(t_slice - delta);
			delta = clk.GetTime() - prevMsec;
		}
		root.Tick(delta);
		//root.Command("");
		*Log << "Debug main:  " << clk.GetTime() << " " << delta << endl;
		prevMsec = currentMsec;
		jmb::common::SleepMsec(t_slice - (clk.GetTime() - prevMsec));
		currentMsec = clk.GetTime();
	}

	*Log << endl << endl;
}
*/

void test9() {
	*Log << ":::GetHexString test:::" << endl;
	Atom a = new Atom("a");
	*Log << "Address of Atom a (as reported by GetHexString) is.................. " << GetHexString(&a) << endl;
	stringstream ss;
	ss << &a;
	*Log << "As reported by unceremoniously dumping it into a stringstream, it is " << ss.str() << endl;
	*Log << "GetString(int) thinks that -413 is " << GetString(-413) << endl;
	*Log << endl;
}

void test10() {
	*Log << ":::GetFirstWord* Test:::" << endl;
	string input = "sweet dash 44 dash tender dash nine dash hot dash juicy dash pork chops";

	*Log << "The word after the colon should be 'sweet':  " << GetFirstWord(input) << endl;

	string remainder = "dummy";
	*Log << "Have some words:  ";

	while(remainder != "") {
		string aword = GetFirstWordEtc(input, remainder);
		*Log << aword << " ";
		input = remainder;
	}

	*Log << endl;
	*Log << "Compare with:     sweet dash 44 dash tender dash nine dash hot dash juicy dash pork chops" << endl;
	*Log << "Empty string test begins...";
	input = "";
	remainder = "dummy";
	while(remainder != "") {
		string aword = GetFirstWordEtc(input, remainder);
		*Log << aword << " ";
		input = remainder;
	}
	*Log << endl << "Empty string test passed!" << endl;
	*Log << endl << endl;
}

void test11() {
	*Log << ":::FastNode Test:::" << endl;
        FastNode* root1 = new FastNode("root1");
        Atom* a1 = new Atom("a1");
        Atom* a2 = new Atom("a2");
        Atom* a3 = new Atom("a3");
        root1->AddChild(a1);
        root1->AddChild(a2);
        root1->AddChild(a3);
        FastNode* root2 = new FastNode("root2");
        Atom* b1 = new Atom("b1");
        Atom* b2 = new Atom("b2");
        Atom* b3 = new Atom("b3");
        root2->AddChild(b1);
        root2->AddChild(b2);
        root2->AddChild(b3);

        *Log << "root1:" << endl;
        root1->Command("");
        *Log << endl << "root2:" << endl;
        root2->Command("");
        *Log << endl;

        *Log << "Move a2 from root1 to root2:" << endl;
        root2->AddChild(a2);
        *Log << "root1:" << endl;
        root1->Command("");
        *Log << endl << "root2:" << endl;
        root2->Command("");
        *Log << endl;

        *Log << "Move root1 into root2:" << endl;
        root2->AddChild(root1);
        *Log << "root2:" << endl;
        root2->Command("");
        *Log << endl;

        *Log << "Now just a3:" << endl;
        //a3->Command("");
        root2->Command("/root1/a3");
        *Log << "And again:" << endl;
        root2->Command("root1/a3");
        delete root2;
	*Log << endl << endl;
}

void test12() {
        *Log << ":::FastNode/Node Interop Test:::" << endl;
        Node* root1 = new Node("root1");
        Atom* a1 = new Atom("a1");
        Atom* a2 = new Atom("a2");
        Atom* a3 = new Atom("a3");
        root1->AddChild(a1);
        root1->AddChild(a2);
        root1->AddChild(a3);
        FastNode* root2 = new FastNode("root2");
        Atom* b1 = new Atom("b1");
        Atom* b2 = new Atom("b2");
        Atom* b3 = new Atom("b3");
        root2->AddChild(b1);
        root2->AddChild(b2);
        root2->AddChild(b3);

        *Log << "root1:" << endl;
        root1->Command("");
        *Log << endl << "root2:" << endl;
        root2->Command("");
        *Log << endl;

        *Log << "Move a2 from root1 to root2:" << endl;
        root2->AddChild(a2);
        *Log << "root1:" << endl;
        root1->Command("");
        *Log << endl << "root2:" << endl;
        root2->Command("");
        *Log << endl;

        *Log << "Move root1 into root2:" << endl;
        root2->AddChild(root1);
        *Log << "root2:" << endl;
        root2->Command("");
        *Log << endl;

        *Log << "Now just a3:" << endl;
        //a3->Command("");
        root2->Command("/root1/a3");
        *Log << "And again:" << endl;
        root2->Command("root1/a3");

	*Log << "Testing dynamic resize of root2 to 12 children, which should succeed" << endl;
	root2->SetMaxChildren(12);
	root2->Command("");
	*Log << "Testing dynamic resize of root2 to 2 children, which should fail" << endl;
	if(root2->SetMaxChildren(2) == -1) {
		*Log << "...it appears to have failed correctly." << endl;
	}
	root2->Command("");

        delete root2;
        *Log << endl << endl;
}

void test13() {
	*Log << ":::Node/FastNode OperatorEqu tests:::" << endl;
	// make a Node
	Node root("root");
	// make some nodes under it
	root.Command("Node alpha");
	root.Command("Node beta");
	root.Command("Node gamma");
	// make some nodes under alpha
	root.Command("Node alpha/uno");
	root.Command("Node alpha/dos");
	root.Command("Node alpha/tres");
	// and under beta
	root.Command("Node beta/one");
	root.Command("Node beta/two");
	root.Command("Node beta/three");
	// and uder alpha/dos
	root.Command("Node alpha/dos/a");
	root.Command("Node alpha/dos/b");
	root.Command("Node alpha/dos/c");
	// run root's Procedure to list its contents
	root.Command("");
	// let's get weird; this command should move alpha/uno into alpha/dos
	root.Command("alpha/dos += alpha/uno");
	root.Command("");
	*Log << endl << endl;
}

void test14() {
	*Log << ":::CommandSplitRev test:::" << endl;
	*Log << "Function test..." << endl;
	CommandSplitRev CSRa("How much wood would a woodchuck chuck if a woodchuck could chuck wood", " chuck ");
	*Log << "Expectation:  Left=How much wood would a woodchuck chuck if a woodchuck could, Right=wood" << endl;
	*Log << "Reality:      Left=" << CSRa.left << ", Right=" << CSRa.right << endl;
	*Log << "Missing token test..." << endl;
	CommandSplitRev CSRb("A quick brown random sample of text blah blah blah blah blaaaarg", "3.14159");
	*Log << "Expectation:  Left=, Right=" << endl;
	*Log << "Reality:      Left=" << CSRb.left << ", Right=" << CSRb.right << endl;
	*Log << endl << endl;
}

void testX() {
	*Log << ":::Hypothetical situations:::" << endl;
	bool this_code_is_usable = false;
	assert(this_code_is_usable); // none of this works!
	// Hierarchy:
	// (root)\
	//       |-VideoMgr
	//       |-AudioMgr
	//       |-InputMgr
	//       |-Cache
	//       | |-Images
	//       | |-Sounds
	//       | \-Objects
	//       |-EventMgr
	//       | |-TxtCache
	//       | \-Timer
	//       \-Log
	//

	Node root("root");
	root.Command("Video VideoMgr");
	root.Command("Audio AudioMgr");
	root.Command("Input InputMgr");
	root.Command("Event EventMgr");
	root.Command("Node  Cache");
	root.Command("Logger Log");
	// ...
	
	root.Command("EventMgr := initScript: Data/script.txt");
/*
	while(!root.erase_me) {
		root.tick();
	}
*/
}

int main(int argc, char** argv) {
	/*
	AddMapping("Atom", Atom::CtorWrapper);
	AddMapping("Notype", Notype::CtorWrapper);
	AddMapping("Integer", Integer::CtorWrapper);
	AddMapping("String", String::CtorWrapper);
	AddMapping("Float", Float::CtorWrapper);
//	AddMapping("Video", Video::CtorWrapper);
	*/
	ClabInit();
	*Log << "The test begins...  now." << endl;
	*Log << endl;
	*Log << "Home Prefix appears to be:  " << GetHomePrefix() << endl;
	*Log << "App Prefix appears to be:   " << GetAppPrefix() << endl;
	*Log << "Log Prefix appears to be:   " << GetLogPrefix() << endl;
	*Log << endl;
	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	//test11();
	//test12();
	test13();
	test14();
	return 0;
}
