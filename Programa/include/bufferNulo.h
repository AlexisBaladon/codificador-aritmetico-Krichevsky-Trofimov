#ifndef BUFFERNULO
#define BUFFERNULO

#include "buffer.h"

class BufferNulo: public Buffer
{
    private:
    public:
        BufferNulo( int k );
        void actualizar_historial( bool b );
        ~BufferNulo();
};

#endif