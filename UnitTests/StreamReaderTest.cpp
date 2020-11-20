#include "pch.h"
#include "CppUnitTest.h"
#include "../VeeamTest/Block.h"
#include "../VeeamTest/Header.h"
#include "../VeeamTest/HashTypes.h"
#include "../VeeamTest/StreamReader.cpp"
#include <fstream>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(StreamReaderTest)
	{
	public:

		TEST_METHOD(NextBlockTest)
		{
            // Arrage
            std::string path = "../UnitTests/test1.txt";
            std::ofstream ouput;
            ouput.open(path);
            ouput.write("Data string for hashing", 24);
            ouput.close();

            // Act
            StreamReader* streamReader = new StreamReader(path, 9);
            int blocksCount = ceil(streamReader->getLength() / (9 + 0.0));
            Block* block1 = streamReader->getBlock();
            Block* block2 = streamReader->getBlock();
            Block* block3 = streamReader->getBlock();
            delete streamReader;

            // Assert
            Assert::AreEqual(blocksCount, 3);
            Assert::AreEqual((int)strlen(block1->data.get()), 9);
            Assert::AreEqual((int)strlen(block2->data.get()), 9);
            Assert::AreEqual((int)strlen(block3->data.get()), 5);
            delete block1;
            delete block2;
            delete block3;
        }
	};
}