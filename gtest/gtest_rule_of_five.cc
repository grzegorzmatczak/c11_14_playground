#include "gtest_smart_pointer.h"

#include <memory>

using ::testing::AtLeast;


namespace gtest_rule_of_five
{
	TEST_F(GTest_rule_of_five, test_unique_ptr)
	{
		bool opt1{false};
		bool opt2{false};
		EXPECT_EQ(opt1, opt2);

	}

}  // namespace gtest_rule_of_five
