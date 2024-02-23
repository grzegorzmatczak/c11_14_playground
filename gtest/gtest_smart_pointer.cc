#include "gtest_smart_pointer.h"

#include <memory>

using ::testing::AtLeast;

namespace gtest_smart_pointer
{
	CBazowa::CBazowa(int i)
		: x(i)
	{
		qDebug() << "CBazowa(" << i << ")";
	}

	// virtual
	CBazowa::~CBazowa()
	{
		qDebug() << "~CBazowa(" << x << ")";
	}
	TEST_F(GTest_smart_pointer, test_unique_ptr)
	{
		std::unique_ptr<CBazowa> pointerToClass(new CBazowa(1));

		pointerToClass.reset(new CBazowa(2));
		pointerToClass.reset(new CBazowa(3));
		pointerToClass.reset(new CBazowa(4));
	}

	TEST_F(GTest_smart_pointer, test_make_unique_ptr)
	{
		std::unique_ptr<CBazowa> pointerToClass = std::make_unique<CBazowa>(1);
	}

	TEST_F(GTest_smart_pointer, test_shared_ptr)
	{
		std::shared_ptr<CBazowa> pointerToClass(new CBazowa(1));

		pointerToClass.reset(new CBazowa(2));
		pointerToClass.reset(new CBazowa(3));
		pointerToClass.reset(new CBazowa(4));
	}

	TEST_F(GTest_smart_pointer, test_make_shared_ptr)
	{
		std::shared_ptr<CBazowa> pointerToClass = std::make_shared<CBazowa>(1);
	}

	TEST_F(GTest_smart_pointer, test_weak_ptr)
	{
		std::shared_ptr<CBazowa> pointerToClass(new CBazowa(1));

		// get pointer to data without taking ownership
		std::weak_ptr<CBazowa> weak1 = pointerToClass;

		pointerToClass.reset(new CBazowa(2));

		// get pointer to new data without taking ownership
		std::weak_ptr<CBazowa> weak2 = pointerToClass;

		if (auto tmp = weak1.lock())
			std::cout << "weak1 value is " << tmp->getValue() << '\n';
		else
			std::cout << "can not lock weak1\n";

		if (auto tmp = weak1.expired())
			std::cout << "weak1 is expired " << '\n';
		else
			std::cout << "weak1 is not expired\n";

		if (auto tmp = weak2.lock())
			std::cout << "weak2 value is " << tmp->getValue() << '\n';
		else
			std::cout << "can not lock weak2\n";
	}

} // namespace gtest_smart_pointer
