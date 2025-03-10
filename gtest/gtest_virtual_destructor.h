#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <QDebug>

using ::testing::AtLeast;

namespace gtest_virtual_destructor
{
	class CBazowa
	{
	public:
		CBazowa();
		~CBazowa();
		//virtual ~CBazowa();
	}; // class CBazowa

	class CPochodna
		: public CBazowa
	{
	public:
		CPochodna();
		~CPochodna();
	}; // class CPochodna

	class GTest_virtual_destructor : public ::testing::Test
	{
	protected:
		GTest_virtual_destructor() {}
		~GTest_virtual_destructor() override {}
		void SetUp() override {}
		void TearDown() override {}
	};

} // namespace gtest_virtual_destructor
