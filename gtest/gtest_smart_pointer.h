#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <QDebug>

using ::testing::AtLeast;

namespace gtest_smart_pointer
{
	class CBazowa
	{
	public:
		CBazowa(int i);
		~CBazowa();
		int getValue(){return x;}
		// virtual ~CBazowa();
	private:
		int x{0};
	}; // class CBazowa

	class GTest_smart_pointer : public ::testing::Test
	{
	protected:
		GTest_smart_pointer() {}
		~GTest_smart_pointer() override {}
		void SetUp() override {}
		void TearDown() override {}
	};

} // namespace gtest_smart_pointer
