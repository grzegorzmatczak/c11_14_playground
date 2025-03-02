#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <QDebug>

using ::testing::AtLeast;

namespace gtest_cast
{
	class GTest_cast : public ::testing::Test
	{
	protected:
		GTest_cast() {}
		~GTest_cast() override {}
		void SetUp() override {}
		void TearDown() override {}
	};

} // namespace gtest_cast
