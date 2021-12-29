#include "../include/bufferMax.h"

BufferMax::BufferMax( int k ): Buffer( k )
{

}

void BufferMax::actualizar_historial( bool b )
{
    buffer = buffer << 1;
    if( b == 1 ) 
    {
        buffer = buffer | 1;
    }
}

BufferMax::~BufferMax()
{

}