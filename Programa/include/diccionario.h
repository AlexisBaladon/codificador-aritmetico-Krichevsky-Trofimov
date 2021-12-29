#ifndef DICCIONARIO
#define DICCIONARIO

class Diccionario 
{
    protected:
        int k;
        int *contador_cache;
        Diccionario( int k );
    public:
        virtual void preparar_historial( unsigned long long historial )=0;
        int get_cantidad_ceros();
        int get_cantidad_unos();
        void actualizar_contadores( bool elemento_visto_por_ultimo );
        virtual ~Diccionario()=0;
};

#endif
