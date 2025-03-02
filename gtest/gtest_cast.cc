#include "gtest_cast.h"

#include <memory>
#include <iostream>
#include <typeinfo>

using ::testing::AtLeast;

struct Foo { virtual ~Foo() {} };
struct Bar { virtual ~Bar() { std::cout << "~Bar\n"; } };
struct Pub : Bar { ~Pub() override { std::cout << "~Pub\n"; } };

namespace gtest_cast
{
	TEST_F(GTest_cast, test_cast_1)
	{
		// (typ) – rzutowanie wymuszone
		// static_cast – rzutowanie odwrotne; niesprawdzane
		// dynamic_cast – rzutowanie polimorficzne
		// const_cast – rzutowanie przeciwwariancyjne
		// reinterpret_cast – rzutowanie zmieniające interpretację reprezentacji


		//dynamic_cast:
		Pub pub;
		try
		{
			[[maybe_unused]]
			Bar& r1 = dynamic_cast<Bar&>(pub); // OK, upcast
	
			[[maybe_unused]]
			Foo& r2 = dynamic_cast<Foo&>(pub); // throws
		}
		catch (const std::bad_cast& e)
		{
			std::cout << "e.what(): " << e.what() << '\n';
		}
	}

} // namespace gtest_cast
