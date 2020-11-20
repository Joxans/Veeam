#include <iostream>
#include "BaseProcessor.h"
using namespace std;

int main()
{
	char rep;

	cout << "!!! Welcome to the data hashing program !!!" << endl;
	cout << "to do work please input the following data:" << endl;
	cout << "\t 1. Input file path" << endl;
	cout << "\t 2. Output file path" << endl;
	cout << "\t 3. Data block size" << endl;
	cout << "\t 4. Hash function type" << endl;

	do
	{
		std::string input;
		std::string output;
		int blocksSize;
		int hashType;

		cout << endl << "Let's start" << endl;
		cout << "Input file path: ";
		cin >> input;
		cout << "Output file path: ";
		cin >> output;
		cout << "Data block size: ";
		cin >> blocksSize;
		cout << "Hash functions:" << endl;
		cout << "\t 1. SHA1" << endl;
		cout << "\t 2. MD5" << endl;
		cout << "Input an index of hash function: ";
		cin >> hashType;
		cout << endl;

		BaseProcessor processor = BaseProcessor(input, output, blocksSize, hashType == 1 ? HashTypes::SHA1 : HashTypes::MD5);
		bool result = processor.run();

		if (result)
			cout << "Hashing was successful";
		else
		{
			cout << "There is some error with hashing";
			return 0;
		}

		cout << endl << "Would you like to go again?" << endl;
		cin >> rep;
	} while (rep != 'N' && rep != 'n');
}
