#include <iostream>
#include "classes.h"

VIRTUAL_CLASS(Base)

int a = 5;

DECLARE_METHOD(Base, Both)
std::cout << ptr_->a;
END_DECLARE

DECLARE_METHOD(Base, OnlyBase)
END_DECLARE

CONSTRUCTOR_BASE(Base, ADD_METHOD(Base, Both) ADD_METHOD(Base, OnlyBase))

END(Base)

VIRTUAL_CLASS_DERIVED(Derived, Base)

int b = 10;

DECLARE_METHOD(Derived, Both)
std::cout << ptr_->b;
END_DECLARE

DECLARE_METHOD(Derived, OnlyDerived)
END_DECLARE

CONSTRUCTOR_DERIVED(Derived, Base,
                    ADD_METHOD(Derived, Both) ADD_METHOD(Derived, OnlyDerived))

END(Derived)

int main() {
  Base base;
  Derived derived;
  Base* reallyDerived = reinterpret_cast<Base*>(&derived);

  VIRTUAL_CALL((&base), Both);
  VIRTUAL_CALL(reallyDerived, Both);
  VIRTUAL_CALL(reallyDerived, OnlyBase);
  VIRTUAL_CALL(reallyDerived, OnlyDerived);

  system("pause");
  return 0;
}