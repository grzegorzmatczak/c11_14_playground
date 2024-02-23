#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <QDebug>

using ::testing::AtLeast;

namespace gtest_rule_of_five
{
	class GTest_rule_of_five : public ::testing::Test
	{
	protected:
		GTest_rule_of_five() {}
		~GTest_rule_of_five() override {}
		void SetUp() override {}
		void TearDown() override {}
	};

} // namespace gtest_rule_of_five
