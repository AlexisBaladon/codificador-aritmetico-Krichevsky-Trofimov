#ifndef DICCIONARIOPEQUENIO
#define DICCIONARIOPEQUENIO

#include "diccionario.h"

//Diccionario implementado con arreglos de tamaño 1<<k de arreglos de tamaño 2 (contadores de 0 y 1)
class DiccionarioPequenio: public Diccionario
{
    private:
        int **contadores;
    public:
        DiccionarioPequenio( int k );
        void preparar_historial( unsigned long long historial );
        ~DiccionarioPequenio();
};

#endif
