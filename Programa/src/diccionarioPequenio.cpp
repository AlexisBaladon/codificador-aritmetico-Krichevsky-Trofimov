#include "../include/diccionarioPequenio.h"

#include <stdlib.h>

DiccionarioPequenio::DiccionarioPequenio( int k ): Diccionario(k)
{
    int potencia = 1 << k;
    contadores = new int*[ potencia ];
    for( int i = 0; i < potencia; i++ )
    {
        contadores[ i ] = NULL;
    }
}

void DiccionarioPequenio::preparar_historial( unsigned long long historial )
{
	if(contadores[historial] == NULL)
	{
		contadores[ historial ] = new int[ 2 ];
        contadores[ historial ][ 0 ] = contadores[ historial ][ 1 ] = 0;
	}
    contador_cache = contadores[historial];
}

DiccionarioPequenio::~DiccionarioPequenio()
{
    int potencia = 1<<k;
    for( int i = 0; i < ( potencia ); i++ )
    {
        delete [] contadores[i];
    }
    delete [] contadores;
    contador_cache = NULL;
}
