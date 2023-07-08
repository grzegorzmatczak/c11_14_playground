#include "gtest_test.h"

using ::testing::AtLeast;


namespace gtest_test
{
	TEST_F(GTest_test, test_1)
	{
		bool opt1{false};
		bool opt2{false};
		EXPECT_EQ(opt1, opt2);

	}

}  // namespace gtest_configreader
