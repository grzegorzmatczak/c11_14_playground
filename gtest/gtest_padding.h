#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <QDebug>

using ::testing::AtLeast;

namespace gtest_padding
{
	class GTest_padding : public ::testing::Test
	{
	protected:
		GTest_padding() {}
		~GTest_padding() override {}
		void SetUp() override {}
		void TearDown() override {}
	};

} // namespace gtest_padding
