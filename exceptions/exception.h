#pragma once

#include <vector>
#include <setjmp.h>
#include <iostream>

class Object {
public:
	Object();
	virtual ~Object();
};

class Exception {
public:
	Exception() {};
	virtual ~Exception() {};
};

std::vector<jmp_buf*> environments;
jmp_buf* environment = nullptr;
std::vector<int> shifts;
std::vector<Object*> objects;
Exception* exception = nullptr;
int returnValue = 0;

Object::Object() { objects.push_back(this); }

Object::~Object() {
	std::cout << "Calling local object destruction" << std::endl;
	objects.pop_back();
}

#define TRY                           \
  shifts.push_back(objects.size());   \
  environment = new jmp_buf[1];       \
  returnValue = setjmp(*environment); \
  if (returnValue == 0) {             \
    environments.push_back(environment);

#define CATCH(type, name)                     \
  }                                           \
  delete environments.back();                 \
  environments.pop_back();                    \
  type* ptr = dynamic_cast<type*>(exception); \
  if (ptr != nullptr) {                       \
    exception = nullptr;                      \
    type name = *ptr;

#define CATCH_END                        \
  }                                      \
  if (exception != nullptr) {            \
    std::cout << "THROWED" << std::endl; \
    system("pause");                     \
    THROW(exception)                     \
  }

#define THROW(e)                                                \
  if (exception != nullptr || environments.size() == 0) {       \
    exit(1);                                                    \
  } else {                                                      \
    for (int i = objects.size() - 1; i >= shifts.back(); --i) { \
      objects[i]->~Object();                                    \
    }                                                           \
    shifts.pop_back();                                          \
    exception = e;                                              \
    longjmp(*environments.back(), 1);                           \
  }