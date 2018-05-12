#include "virtual.h"

VIRTUAL_CLASS(Base)
int a;
END(Base)

VIRTUAL_CLASS_DERIVED(Derived, Base)
int b;
END(Derived, Base)


int main() {
	DECLARE_METHOD(Base, Both)
	DECLARE_METHOD(Base, OnlyBase)
	DECLARE_METHOD(Derived, Both)
	DECLARE_METHOD(Derived, OnlyDerived)

	Base base;
	base.a = 0;

	Derived derived;
	derived.b = 1;

	Base* reallyDerived = reinterpret_cast<Base*>(&derived);

	VIRTUAL_CALL(&base, Both);
	VIRTUAL_CALL(reallyDerived, Both);
	VIRTUAL_CALL(reallyDerived, OnlyBase);
	VIRTUAL_CALL(reallyDerived, OnlyDerived);

	system("pause");
	return 0;
}