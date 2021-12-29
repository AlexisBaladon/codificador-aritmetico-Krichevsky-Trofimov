#include "../include/diccionarioGrande.h"

#include <stdlib.h>
#include <iterator>

DiccionarioGrande::DiccionarioGrande( int k ): Diccionario(k)
{

}

void DiccionarioGrande::preparar_historial( unsigned long long historial )
{
    std::unordered_map< unsigned long long, int* >::iterator cont = mapa.find( historial );
    if( cont == mapa.end() )
    {
        int* nuevo_contador = new int[2];
        nuevo_contador[0] = nuevo_contador[1] = 0;
        mapa.insert( { historial, nuevo_contador } );
        contador_cache = nuevo_contador;
    }
    else
    {
        contador_cache = cont->second;
    }
}

DiccionarioGrande::~DiccionarioGrande()
{
    for( std::unordered_map< unsigned long long, int* >::iterator it = mapa.begin(); it != mapa.end(); it++ )
    {
        delete [] it->second;
    }
    contador_cache = NULL;
}