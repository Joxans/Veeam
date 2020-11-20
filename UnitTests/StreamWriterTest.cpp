#include "pch.h"
#include "CppUnitTest.h"
#include "../VeeamTest/Block.h"
#include "../VeeamTest/Header.h"
#include "../VeeamTest/HashTypes.h"
#include "../VeeamTest/StreamWriter.cpp"
#include <fstream>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(StreamWriterTest)
	{
	public:
		
		TEST_METHOD(HeaderTest)
		{
            // Arrage
            Header* header = new Header();            
            header->blocksCount = 10;
            header->hashType = HashTypes::MD5;
            header->hashSize = 16;

            // Act
            std::string path = "../UnitTests/test1.txt";
            StreamWriter* streamWriter = new StreamWriter(path);
            streamWriter->writeHeader(header);
            delete streamWriter;

            std::ifstream input;
            std::shared_ptr<char> buffer(new char[16]);
            input.open(path);
            input.read(buffer.get(), 16);
            input.close();

            int bloksCount;
            HashTypes hashType;
            int hashSize;
            memcpy_s(&bloksCount, sizeof(int), buffer.get() + 4, sizeof(int));
            memcpy_s(&hashType, sizeof(int), buffer.get() + 8, sizeof(int));
            memcpy_s(&hashSize, sizeof(int), buffer.get() + 12, sizeof(int));
            
            // Assert
            Assert::AreEqual(header->blocksCount, bloksCount);
            Assert::AreEqual((char)header->hashType, (char)hashType);
            Assert::AreEqual(header->hashSize, hashSize);
            delete header;
		}

        TEST_METHOD(BlockTest)
        {
            // Arrage
            Block* block = new Block();
            block->id = 1;
            block->originBlockSize = 1024;
            block->hash = std::shared_ptr<char>(new char[5]{ "1234" });
            block->data = std::shared_ptr<char>(new char[5]{ "5678" });

            // Act
            std::string path = "../UnitTests/test1.txt";
            StreamWriter* streamWriter = new StreamWriter(path);
            streamWriter->writeBlock(block);
            delete streamWriter;

            std::ifstream input;
            std::shared_ptr<char> buffer(new char[22]);
            input.open(path);
            input.read(buffer.get(), 22);
            input.close();

            int id;
            int originBlockSize;          
            memcpy_s(&id, sizeof(int), buffer.get() + 4, sizeof(int));            
            memcpy_s(&originBlockSize, sizeof(int), buffer.get() + 8, sizeof(int));
            std::string hash(buffer.get() + 12);
            std::string data(buffer.get() + 17);

            // Assert
            Assert::AreEqual(block->id, id);
            Assert::AreEqual(block->originBlockSize, originBlockSize);
            Assert::AreEqual(block->hash.get(), hash.data());
            Assert::AreEqual(block->data.get(), data.data());
            delete block;
        }
	};
}
