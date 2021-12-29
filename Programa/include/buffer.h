#ifndef BUFFER
#define BUFFER

//Todos los buffers se implementan igual con la diferencia de que las acciones tomadas al actualizar el historial varían lévemente
class Buffer
{
    protected:
        int k;
        unsigned long long buffer;
    public:
        Buffer( int k );
        unsigned long long get_buffer();
        virtual void actualizar_historial( bool b )=0;
        ~Buffer();
};

#endif