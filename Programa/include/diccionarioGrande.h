#ifndef DICCIONARIOGRANDE
#define DICCIONARIOGRANDE

#include "diccionario.h"
#include <unordered_map>

//Diccionario implementado con un "unordered_map" (implementado con tablas de hash) de arreglos de tamaño 2 (contadores de 0 y 1)
class DiccionarioGrande: public Diccionario
{
    private:
        std::unordered_map< unsigned long long, int* > mapa;
    public:
        DiccionarioGrande( int k );
        void preparar_historial( unsigned long long historial );
        ~DiccionarioGrande();
};

#endif
