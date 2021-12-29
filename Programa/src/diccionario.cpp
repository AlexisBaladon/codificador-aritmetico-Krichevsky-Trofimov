#include "../include/diccionario.h"
#include "../include/fabrica.h"

#include <stdlib.h>

Diccionario::Diccionario( int k )
{
    this->k = k;
    contador_cache = NULL;
}

int Diccionario::get_cantidad_ceros()
{
    return contador_cache[0];
}

int Diccionario::get_cantidad_unos()
{
    return contador_cache[1];
}

void Diccionario::actualizar_contadores( bool elemento_visto_por_ultimo )
{
    if( contador_cache[0] + contador_cache[1] >= 8192 ) //Ya que 2(contador(0) + contador(1)) + 1 esta delimitado por 2^14 en el programa original
    {
        contador_cache[0] = contador_cache[0]>>1;
        contador_cache[1] = contador_cache[1]>>1;
    }
    contador_cache[elemento_visto_por_ultimo]++;
}

Diccionario::~Diccionario()
{

}
