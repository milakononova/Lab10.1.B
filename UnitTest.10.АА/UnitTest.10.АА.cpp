#include "pch.h"
#include "CppUnitTest.h"

#define UNIT_TEST
#include "../Lab10.1.B/Lab10.1.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest)
    {
    public:

        TEST_METHOD(TestPercentExcellent)
        {
            Student s[4]{};

            s[0].physics = 5;
            s[0].mathematics = 5;

            s[1].physics = 4;
            s[1].mathematics = 5;

            s[2].physics = 5;
            s[2].mathematics = 5;

            s[3].physics = 5;
            s[3].mathematics = 4;

            Assert::AreEqual(
                50.0,
                PercentExcellent(s, 4),
                0.001);
        }
    };
}