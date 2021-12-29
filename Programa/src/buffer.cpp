#include "../include/buffer.h"

Buffer::Buffer( int k )
{
    buffer = 0;
    this->k = k;
}

unsigned long long Buffer::get_buffer()
{
    return buffer;
}

Buffer::~Buffer()
{

}
