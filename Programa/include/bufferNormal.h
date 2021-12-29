#ifndef BUFFERNORMAL
#define BUFFERNORMAL

#include "buffer.h"

class BufferNormal: public Buffer
{
    private:
    public:
        BufferNormal( int k );
        void actualizar_historial( bool b );
        ~BufferNormal();
};

#endif