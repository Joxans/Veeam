#include "pch.h"
#include "CppUnitTest.h"
#include "../VeeamTest/Block.h"
#include "../VeeamTest/HashTypes.h"
#include "../VeeamTest/BlocksHandler.cpp"
#include <queue>
#include <ctime> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(BlocksHandlerTest)
    {
    public:
        std::shared_ptr<char> gen_random(int len)
        {
            std::shared_ptr<char> tmp_s(new char[len + 1]{ '\0' });
            static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

            for (int i = 0; i < len; ++i)
                *(tmp_s.get() + i) = alphanum[rand() % (sizeof(alphanum) - 1)];

            return tmp_s;
        }

        TEST_METHOD(BlocksTest)
        {
            // Arrage
            std::vector<Block*> input = std::vector<Block*>(30);
            std::vector<Block*> copy = std::vector<Block*>(30);
            for (int i = 0; i < input.size(); i++)
            {
                int id = i + 1;
                int originBlockSize = std::rand();

                input[i] = new Block();
                input[i]->id = id;
                input[i]->originBlockSize = originBlockSize;
                input[i]->hash = std::shared_ptr<char>(new char[1]{ '\0' }, std::default_delete<char[]>());
                input[i]->data = gen_random(4);

                copy[i] = new Block();
                copy[i]->id = id;
                copy[i]->originBlockSize = originBlockSize;
                copy[i]->hash = std::shared_ptr<char>(new char[1]{ '\0' }, std::default_delete<char[]>());
                copy[i]->data = std::shared_ptr<char>(new char[5], std::default_delete<char[]>());
                strcpy_s(copy[i]->data.get(), 5, input[i]->data.get());
            }

            // Act
            BlocksHandler* handler = new BlocksHandler(3, HashTypes::MD5);
            std::vector<Block*> output = std::vector<Block*>(30);
            for (int i = 0; i < input.size(); i++)
            {
                handler->addUnhandledBlock(input[i]);
                if (i == 4)
                    handler->start();
                if (i >= 9)
                    output[i-9] = handler->getHandledBlock();
                if(i == input.size() - 1)
                    for(int j = input.size() - 9; j < input.size(); j++)
                        output[j] = handler->getHandledBlock();
            }
            delete handler;

            // Assert
            for (int i = 0; i < input.size(); i++)
            {
                Assert::AreEqual(copy[i]->id, input[i]->id);
                Assert::AreEqual(copy[i]->originBlockSize, input[i]->originBlockSize);
                Assert::AreEqual(strlen(copy[i]->hash.get()) == 0, true);
                Assert::AreEqual(strlen(input[i]->hash.get()) != 0, true);
                Assert::AreEqual(!strcmp(copy[i]->data.get(), input[i]->data.get()), true);
                delete copy[i];
                delete input[i];
            }
        }
    };
}
