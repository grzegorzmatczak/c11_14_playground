#include "gtest_move.h"

#include <memory>

using ::testing::AtLeast;


namespace gtest_move
{

	TEST_F(GTest_move, test_move1)
	{
		bool opt1{false};
		bool opt2{false};
		int int1{123};
		logAndProcess(int1);                  // call with lvalue
		logAndProcess(std::move(int1));       // call with rvalue

		EXPECT_EQ(opt1, opt2);
	}
}  // namespace gtest_move
