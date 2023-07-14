#include "gtest_smart_pointer.h"

#include <memory>

using ::testing::AtLeast;


namespace gtest_smart_pointer
{
	TEST_F(GTest_smart_pointer, test_unique_ptr)
	{
		std::unique_ptr<int> pointerToInt(new int(2));
		qDebug() << "pointerToInt:" << pointerToInt.get() << " value:" << pointerToInt.get();
		bool opt1{false};
		bool opt2{false};
		EXPECT_EQ(opt1, opt2);

	}

}  // namespace gtest_configreader
