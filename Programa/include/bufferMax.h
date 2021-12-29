#ifndef BUFFERMAX
#define BUFFERMAX

#include "buffer.h"

class BufferMax: public Buffer
{
    private:
    public:
        BufferMax( int k );
        void actualizar_historial( bool b );
        ~BufferMax();
};

#endif