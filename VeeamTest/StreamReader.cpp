#include "StreamReader.h"

StreamReader::StreamReader(std::string file, int blockSize)
{
	this->stream.open(file.data());
	this->blockSize = blockSize;
    this->counter = 0;

    if (!this->stream.good())
        throw std::invalid_argument("Cannot open input file.");

    this->stream.seekg(0, this->stream.end);    
    this->length = this->stream.tellg();
    this->stream.seekg(0, this->stream.beg);
}

StreamReader::~StreamReader()
{
    this->stream.close();
}

int StreamReader::getLength()
{
    return this->length;
}

int StreamReader::getPosition()
{
    return this->stream.tellg();
}

Block* StreamReader::getBlock()
{
    std::shared_ptr<char> buffer = this->getBlockBytes();

    Block* block = new Block();
    block->id = this->counter++;
    block->originBlockSize = strlen(buffer.get());
    block->data = buffer;

    return block;
}

std::shared_ptr<char> StreamReader::getBlockBytes()
{
    std::shared_ptr<char> buffer(new char[this->blockSize + 1]{ '\0' }, std::default_delete<char[]>());
    this->stream.read(buffer.get(), this->blockSize);
    int length = strlen(buffer.get());

    if (length == 0)
        return NULL;

    if (length == this->blockSize)
        return buffer;

    std::shared_ptr<char> result(new char[length + 1], std::default_delete<char[]>());
    strcpy_s(result.get(), length + 1, buffer.get());
    return result;
}