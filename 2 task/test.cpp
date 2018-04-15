#include "exception.h"

#include <iostream>
#include <string>


class myObject : public Object {
public:
	int n_ = 10;
};


class StrExcep : public Exception {
public:
	StrExcep(std::string str) : str_(str) {}
	std::string str_;
};


class NumberExcep : public Exception {
public:
	NumberExcep(int n) : n_(n) {}
	int n_;
};


void test1() {
	TRY THROW(new StrExcep("7sasa"));
	CATCH(StrExcep, e) std::cout << e->str_ << std::endl;
}

void test2() {
	TRY myObject obj;
	THROW(new NumberExcep(8));
	CATCH(StrExcep, e) std::cout << e->str_ << std::endl;
}

void test3() {
	TRY std::cout << "OUTER TRY:" << std::endl;
	TRY std::cout << "INNER TRY:" << std::endl; 
	THROW(new NumberExcep(10));
	CATCH(StrExcep, e) std::cout << e->str_ << std::endl;
	CATCH(NumberExcep, e) std::cout << e->n_ << std::endl;
}


void test4() {
	TRY myObject obj;
	TRY myObject object;
	THROW(new NumberExcep(12));
	CATCH(StrExcep, e) std::cout << e->str_ << std::endl;
	CATCH(NumberExcep, e) std::cout << e->n_ << std::endl;
}


int main() {
	test2();
	system("pause");
}