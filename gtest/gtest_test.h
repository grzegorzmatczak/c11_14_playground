#include "gtest/gtest.h"
#include "gmock/gmock.h" 

#include <QDebug>

using ::testing::AtLeast;


namespace gtest_test
{
	class GTest_test : public ::testing::Test
	{
		protected:
			GTest_test(){}
			~GTest_test() override {}
			void SetUp() override{}
			void TearDown() override {}
			
	};

}  // namespace gtest_test
