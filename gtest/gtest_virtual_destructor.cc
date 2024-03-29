#include "gtest_virtual_destructor.h"

#include <memory>
#include <cstdio>

using ::testing::AtLeast;

namespace gtest_virtual_destructor
{
	CBazowa::CBazowa()
	{
		printf("CBazowa()\n");
	}

	// virtual
	CBazowa::~CBazowa()
	{
		printf("~CBazowa()\n");
	}

	CPochodna::CPochodna()
	{
		printf("CPochodna()\n");
	}

	CPochodna::~CPochodna()
	{
		printf("~CPochodna()\n");
	}

	TEST_F(GTest_virtual_destructor, test_move1)
	{
		CBazowa *pBase = new CPochodna;
		delete pBase;
	}
} // namespace gtest_virtual_destructor
