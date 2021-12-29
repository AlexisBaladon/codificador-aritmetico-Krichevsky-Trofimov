#ifndef FABRICA
#define FABRICA

#include "diccionarioGrande.h"
#include "diccionarioPequenio.h"
#include "bufferMax.h"
#include "bufferNormal.h"
#include "bufferNulo.h"

class Fabrica
{
    private:
        Fabrica();
    public:
        static Fabrica * get_instance();
        Diccionario * fabricar_diccionario( int k );
        Buffer * fabricar_buffer( int k );
        ~Fabrica();
};

#endif