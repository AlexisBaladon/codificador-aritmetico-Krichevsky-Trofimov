#include "../include/fabrica.h"

Fabrica::Fabrica()
{

}

Fabrica * Fabrica::get_instance()  //Singleton estatico
{
    static Fabrica fabrica;
    return &fabrica;
}

Diccionario * Fabrica::fabricar_diccionario( int k )
{
    Diccionario * diccionario;
    if( k>=16 ) //Eleccion de estrategias
    {
        diccionario = new DiccionarioGrande( k );
    }
    else
    {
        diccionario = new DiccionarioPequenio( k );
    }
    return diccionario;
}

Buffer * Fabrica::fabricar_buffer( int k )
{
    Buffer * buffer;
    if(k == 0) //Eleccion de estrategias
    {
        buffer = new BufferNulo( k );
    }
    else if( k == 64)
    {
        buffer = new BufferMax( k );
    }
    else
    {
        buffer = new BufferNormal( k );
    }
    return buffer;
}

Fabrica::~Fabrica()
{
    
}
