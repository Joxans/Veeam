#include "pch.h"
#include "CppUnitTest.h"
#include "../VeeamTest/HashTypes.h"
#include "../VeeamTest/BaseProcessor.cpp"
#include <queue>
#include <ctime> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(BaseProcessorTest)
    {
    public:

        TEST_METHOD(ProcessTest)
        {
            // Arrage
            std::string input = "../UnitTests/test2.txt";
            std::string output = "../UnitTests/test1.txt";            

            // Act
            BaseProcessor processor = BaseProcessor(input, output, 104, HashTypes::MD5);
            bool result = processor.run();            

            // Assert
            Assert::AreEqual(result, true);  // need to check output file;
        }
    };
}
