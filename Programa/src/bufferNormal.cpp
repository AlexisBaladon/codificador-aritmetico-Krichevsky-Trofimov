#include "../include/bufferNormal.h"

#include <climits>

BufferNormal::BufferNormal( int k ): Buffer( k )
{

}

void BufferNormal::actualizar_historial( bool b )
{
        buffer = buffer << 1;
        buffer = buffer & ( ULLONG_MAX-( (unsigned long long)1<<k ) ); //Evito que historial sobrepase los k bits
        if( b == 1 ) 
        {
            buffer = buffer | 1;
        }
}

BufferNormal::~BufferNormal()
{

}
