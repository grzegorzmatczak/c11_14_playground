#include "gtest/gtest.h"
#include "gmock/gmock.h" 

#include <QDebug>

using ::testing::AtLeast;


namespace gtest_move
{
	class GTest_move : public ::testing::Test
	{
		protected:
			GTest_move(){}
			~GTest_move() override {}
			void SetUp() override{}
			void TearDown() override {}

			void process(const int& lvalArg)     // process lvalues
			{
				qDebug() << "process lvalues:";
			}
			void process(int&& rvalArg)          // process rvalues
			{
				qDebug() << "rvalues:";
			}

			template<typename T>                     // template that passes
			void logAndProcess(T&& param)            // param to process
			{
				auto now =std::chrono::system_clock::now();
				process(std::forward<T>(param));
			}
	};

}  // namespace gtest_move
