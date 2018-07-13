#include <iostream>
#include "Object.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "StrSplit.h"

using std::cout;
using std::endl;
using std::string;
using jmb::common::Object;
using jmb::common::Integer;
using jmb::common::Float;
using jmb::common::String;
using jmb::common::Sentence;

double GetValueOfFloat(Float* flt) {
	double retval = 0.0;
	double* dub = static_cast<double*>(flt->GetValue());
	retval = *dub;
	return retval;
}

int GetValueOfInteger(Integer* in) {
	int retval = 0;
	int* inref = static_cast<int*>(in->GetValue());
	retval = *inref;
	return retval;
}

void test1() {
	cout << "Test #1 - Hierarchy" << endl;
	Object root("root");
	Object* obj1 = new Object("obj1");
	root.AddOwnedObject(obj1);
	Object* obj2 = new Object("obj2");
	obj1->AddOwnedObject(obj2);
	Object* obj3 = new Object("obj3");
	obj2->AddOwnedObject(obj3);
	Object* obj4 = new Object("obj4");
	obj2->AddOwnedObject(obj4);
	Object* obj5 = new Object("obj5");
	obj2->AddOwnedObject(obj5);
	root.AddOwnedObject(obj2);
	root.Debug();
	//root.Dereference("obj1/obj2")->Debug();
	
	std::string ass = "bull^/shit";
	Sentence sent(ass);
	std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << ":\n";
	std::cout << "sent.subject = " << sent.subject << "\n";
	std::cout << "sent.op      = " << sent.op << "\n";
	std::cout << "sent.target  = " << sent.target << "\n";
	
	root.Command("obj2/obj5");
	
	root.Command("obj1=obj2");
	cout <<endl;
}

void test2() {
	cout << "Test #2:" << endl;
	Object root("root");
	Integer* n1 = new Integer("n1");
	Integer* n2 = new Integer("n2");

	root.AddOwnedObject(n1);
	root.AddOwnedObject(n2);
	root.Command("n2=6000");
	root.Command("n1=n2");
	cout << GetValueOfInteger(n1) << endl;

	root.Command("n1=100");
	root.Command("n2=10");
	root.Command("n1+=n2");
	cout << GetValueOfInteger(n1) << " should be '110'" << endl;

	root.Command("n1=100");
	root.Command("n2=10");
	root.Command("n1-=n2");
	cout << GetValueOfInteger(n1) << " should be '90'" << endl;

	root.Command("n1=0");
	root.Command("n2=10");
	root.Command("n1-=n2");
	cout << GetValueOfInteger(n1) << " should be '-10'" << endl;

	root.Command("n1=100");
	root.Command("n2=10");
	root.Command("n1*=n2");
	cout << GetValueOfInteger(n1) << " should be '1000'" << endl;
	
	root.Command("n1=100");
	root.Command("n2=-10");
	root.Command("n1*=n2");
	cout << GetValueOfInteger(n1) << " should be '-1000'" << endl;
	
	root.Command("n1=100");
	root.Command("n2=10");
	root.Command("n1/=n2");
	cout << GetValueOfInteger(n1) << " should be '10'" << endl;
	
	root.Command("n1=2");
	root.Command("n2=8");
	root.Command("n1^=n2");
	cout << GetValueOfInteger(n1) << " should be '256'" << endl;
	
	root.Debug();
	cout << endl;
}

void test3() {
	cout << "Test #3:" << endl;
	Object root("root");
	String* s1 = new String("s1");
	String* s2 = new String("s2");

	s1->Command("=Test123");
	s2->Command("=Test456");
	root.AddOwnedObject(s1);
	root.AddOwnedObject(s2);
	root.Command("s2=s1");
	cout << *(static_cast<std::string*>(s1->GetValue())) << " should be 'Test123'" << endl;
	root.Command("s2=bullhonkey");
	root.Command("s2+=s1");
	cout << *(static_cast<std::string*>(s2->GetValue())) << " should be 'bullhonkeyTest123'" << endl;
	root.Command("s1='s2'");
	cout << *(static_cast<std::string*>(s1->GetValue())) << " should be 's2' (without single quotes)" << endl;
	root.Command("s2/=s1");
	cout << *(static_cast<std::string*>(s2->GetValue())) << " should be 'bullhonkeyTest123' again" << endl;
	cout << endl;
}

void test4() {
	cout << "Test #4 - error edition!" << endl;
	Object root("root");
	String* v1 = new String("v1");
	Integer* v2 = new Integer("v2");
	root.AddOwnedObject(v1);
	root.AddOwnedObject(v2);
	v1->Command("=Test876");
	v2->Command("=543");
	root.Command("v1=v2");
	cout << *(static_cast<std::string*>(v1->GetValue())) << " better be 543" << endl;
	root.Command("v1+=v2");
	cout << *(static_cast<std::string*>(v1->GetValue())) << " better be 543543" << endl;
	
	cout << "now the other way..." << endl;
	Object r2("r2");
	Integer* v3 = new Integer("v3");
	String* v4 = new String("v4");
	r2.AddOwnedObject(v3);
	r2.AddOwnedObject(v4);
	r2.Command("v3=31415");
	r2.Command("v4=66667");
	r2.Command("v3=v4");
	cout << GetValueOfInteger(v3) << " should be '66667'" << endl;
	r2.Command("v3+=v4");
	cout << GetValueOfInteger(v3) << " should be '133334'" << endl;
	
	// Recursion Test:
	Object* lol = new Object("lol");
	r2.AddOwnedObject(lol);
	lol->AddOwnedObject(&r2);
	
	r2.Debug();
	cout << endl;
}

void test5() {
	cout << "Test 5:  The Testening" << endl;
	Object root("root");
	Float* f1 = new Float("f1");
	Float* f2 = new Float("f2");
	root.AddOwnedObject(f1);
	root.AddOwnedObject(f2);
	root.Command("f1=3.14159");
	root.Command("f2=0.12345");
	cout << GetValueOfFloat(f1) << " should be 3.14159" << endl;
	cout << GetValueOfFloat(f2) << " should be 0.12345" << endl;
	root.Command("f1+=f2");
	cout << GetValueOfFloat(f1) << " should be 3.26504" << endl;
	root.Command("f2*=f1");
	cout << GetValueOfFloat(f2) << " should be 0.403069188 but it might get truncated" << endl;
	
	Integer* i1 = new Integer("i1");
	root.AddOwnedObject(i1);
	root.Command("i1=400");
	root.Command("i1*=f2");
	// sinnce f2 gets rounded down before multiplication, the end result is zero
	cout << GetValueOfInteger(i1) << " should be 0" << endl;
	
	root.Command("i1=400");
	root.Command("f2=0.92345");
	root.Command("i1*=f2");
	cout << GetValueOfInteger(i1) << " should be 400" << endl;
	
	root.Command("i1=400");
	root.Command("f2=0.92345");
	root.Command("f2+=i1");
	cout << GetValueOfFloat(f2) << " should be 400.92345 (unless truncated)" << endl;
	
	root.Command("f2");
	Object* bob = new Object("bob");
	i1->AddOwnedObject(bob);
	root.Command("i1/bob");
	root.Debug();
	bob->Debug();
	
	cout << endl;
}

void test6() {
	cout << endl << "Test 6 - GetValueAsStdString" <<  endl;
	Object root("root");
	Integer* v1 = new Integer("v1");
	Float* v2 = new Float("v2");
	String* v3 = new String("v3");
	root.AddOwnedObject(v1);
	root.AddOwnedObject(v2);
	root.AddOwnedObject(v3);
	root.Command("v1=100");
	root.Command("v2=200");
	root.Command("v3=300");
	cout << "v1=" << v1->GetValueAsStdString() << " should be 100" << endl;
	cout << "v2=" << v2->GetValueAsStdString() << " should be 200.000..." << endl;
	cout << "v3=" << v3->GetValueAsStdString() << " should be 300" << endl;
}

int main (int argc, char * const argv[]) {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
    return 0;
}
