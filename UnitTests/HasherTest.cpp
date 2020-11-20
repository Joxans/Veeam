#include "pch.h"
#include "CppUnitTest.h"
#include "../VeeamTest/Hasher.cpp"
#include "../VeeamTest/CommonHasher.h"
#include "../VeeamTest/HashTypes.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(HasherTest)
    {
    public:

        TEST_METHOD(MD5HashTest)
        {
            // Arrage
            Hasher* hasher = Hasher::getHasher(HashTypes::MD5);
            std::shared_ptr<char> source(new char[25] {"Data string for hashing"});       
            std::shared_ptr<char> target(new char[34]{ "5FDC6B0BF22892F6D7ACC119549A9054" });
 
            // Act
            std::shared_ptr<char> result = hasher->getHash(source);
            delete hasher;
            hasher = Hasher::getHasher(HashTypes::MD5);

            // Assert
            Assert::AreEqual(hasher->verifyHash(source, result), true);
            Assert::AreEqual(!strcmp(target.get(), result.get()), true);
            delete hasher;
        }

        TEST_METHOD(SHA1HashTest)
        {
            // Arrage
            Hasher* hasher = Hasher::getHasher(HashTypes::SHA1);
            std::shared_ptr<char> source(new char[25]{ "Data string for hashing" });
            std::shared_ptr<char> target(new char[42]{ "60BC260AC170F0C2E6328B06126A432150BE56C7" });

            // Act
            std::shared_ptr<char> result = hasher->getHash(source);
            delete hasher;
            hasher = Hasher::getHasher(HashTypes::SHA1);

            // Assert
            Assert::AreEqual(hasher->verifyHash(source, result), true);
            Assert::AreEqual(!strcmp(target.get(), result.get()), true);
            delete hasher;
        }
    };
}