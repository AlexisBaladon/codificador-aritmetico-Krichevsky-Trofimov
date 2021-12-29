#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>

#include "include/coder.h"
#include "include/bitio.h"
#include "include/fabrica.h"

void compress( int k, char* nombre_archivo_descomprimido, char* nombre_archivo_comprimido );
void expand( int k, char *nombre_archivo_comprimido, char *nombre_archivo_descomprimido );
void convert_int_to_symbol( bool b, SYMBOL *s );
bool convert_symbol_to_int( unsigned int count, SYMBOL *s );
void error_exit( char* message );

struct {
          unsigned long int low;
          unsigned long int high;
       } probabilities[]= {{  0,  1  },
                           {  1,  2  }
                          };

int main() {

    //Nombres de archivos
    char *A = new char[20];
    memset(A,0,20);
    strcat(A,"A.pbm");
    char *B = new char[20];
    memset(B,0,20);
    strcat(B,"B.pbm");
    char *C = new char[20];
    memset(C,0,20);
    strcat(C,"C.pbm");
    char *D = new char[20];
    memset(D,0,20);
    strcat(D,"D.pbm");
    char * comprimido = new char[20];
    memset(comprimido,0,20);
    strcat(comprimido,"comprimido.bin");

    //Recolección de datos en un archivo .csv
    std::ofstream excel;
    excel.open("datosA.csv",std::ios::app);

    //A.pbm
	for(int i = 0; i < 65; i++) {
        compress(i,A,comprimido);
        FILE * recolector;
        recolector = fopen("comprimido.bin","rb");
        fseek(recolector,0, SEEK_END);
        excel << ftell( recolector ) << ",";
        fclose(recolector);
    }
    excel.close();

    //B.pbm
    excel.open("datosB.csv",std::ios::app);
    for(int i = 0; i < 65; i++) {
        compress(i,B,comprimido);
        FILE * recolector;
        recolector = fopen("comprimido.bin","rb");
        fseek(recolector,0, SEEK_END);
        excel << ftell( recolector ) << ",";
        fclose(recolector);
    }
    excel.close();

    //C.pbm
    excel.open("datosC.csv",std::ios::app);
    for(int i = 0; i < 65; i++) {
        compress(i,C,comprimido);
        FILE * recolector;
        recolector = fopen("comprimido.bin","rb");
        fseek(recolector,0, SEEK_END);
        excel << ftell( recolector ) << ",";
        fclose(recolector);
    }
    excel.close();

    //D.pbm
    excel.open("datosD.csv",std::ios::app);
    for(int i = 0; i < 65; i++) {
        compress(i,D,comprimido);
        FILE * recolector;
        recolector = fopen("comprimido.bin","rb");
        fseek(recolector,0, SEEK_END);
        excel << ftell( recolector ) << ",";
        fclose(recolector);
    }
    excel.close();

    delete [] A;
    delete [] B;
    delete [] C;
    delete [] D;
    delete [] comprimido;
    
    return 0;
}

void compress(  int k, char* nombre_archivo_descomprimido, char* nombre_archivo_comprimido )
{
    //Inicializaciones
    FILE *compressed_file;
    FILE *original_file;
    original_file=fopen( nombre_archivo_descomprimido, "rb" );
    compressed_file=fopen( nombre_archivo_comprimido, "wb" );
    initialize_output_bitstream();
    initialize_arithmetic_encoder();

    //Se pasa al archivo comprimido el largo del original
    long int largo_archivo;
    fseek( original_file, 0, SEEK_END );
    largo_archivo = ftell( original_file );
    fprintf( compressed_file, "%ld", largo_archivo );
    fprintf( compressed_file, " " );
    fseek( original_file,0, SEEK_SET );
    
    //Se obtiene la instancia de fábrica y se construye el buffer según k
    Fabrica * fabrica = Fabrica::get_instance();
    Buffer * buffer = fabrica->fabricar_buffer( k );

    //Elementos utilizados a partir de ahora
    bool b;
    int c;
    SYMBOL s;

    //Se imprimen los bits necesarios para obtener un estado de tamaño k
    int stop = ( ( k-1 )>>3 )+1; //Divido entre 8 y hago techo para saber cuantos caracteres imprimir para llenar k bits
    for( int i=0; i < stop; i++ )
    {
        c = fgetc( original_file );
        for( int j=7; j>=0; j-- )
            {
                b = ( (unsigned char)c&( 1<<j ) );
                convert_int_to_symbol( b, &s );
                encode_symbol( compressed_file, &s );
                buffer->actualizar_historial( b ); //Se actualizan datos del buffer
            }
    }
    
    //Se fábrica diccionario según k
    Diccionario * diccionario = fabrica->fabricar_diccionario( k );

    //Continuación de compresión
    while( ( ( c = fgetc(original_file) )!= EOF ) )
    {
        for( int i=7; i>=0; i-- ) //Se leen bits en orden de pixeles de la imagen
        {
            //Se obtiene el siguiente pixel y se obtienen contadores internamente (ver implementación)
        	b = ( ( unsigned char )c&( 1<<i ) );
            diccionario->preparar_historial( buffer->get_buffer() );

            //Se utiliza Krichevsky-Trofimov
            int contador[2] = { diccionario->get_cantidad_ceros(), diccionario->get_cantidad_unos() };
            probabilities[ 0 ].high = probabilities[ 1 ].low = ( contador[ 0 ]<<1 )+1;
            probabilities[ 1 ].high = ( contador[ 0 ]+contador[1]+1 )<<1;
            s.scale = probabilities[ 1 ].high;

            //Se comprime el símbolo actual
            convert_int_to_symbol( b, &s );
            s.scale = probabilities[ 1 ].high;
            encode_symbol( compressed_file, &s );

            //Se actualizan datos dentro del diccionario y buffer
            diccionario->actualizar_contadores( b );
            buffer->actualizar_historial( b );
        }
    }

    //Procesos finales y liberación de memoria
    flush_arithmetic_encoder( compressed_file );
    flush_output_bitstream( compressed_file );
    fclose( compressed_file );
    fclose( original_file );
    delete diccionario;
    delete buffer;

    //Reseteo de vector de probabilidades para posterior uso
    probabilities[ 0 ].low = 0;
    probabilities[ 0 ].high = 1;
    probabilities[ 1 ].low = 1;
    probabilities[ 1 ].high = 2;
}

void expand( int k, char *nombre_archivo_comprimido, char *nombre_archivo_descomprimido )
{
    //Inicializaciones
    FILE *compressed_file;
    FILE *original_file;
    compressed_file=fopen( nombre_archivo_comprimido, "rb" );
    original_file=fopen( nombre_archivo_descomprimido, "wb" );

    //Se obtiene el largo del archivo original
    long int tamanio;
    char auxi;
    fscanf( compressed_file, "%ld", &tamanio );
    fscanf( compressed_file, "%c", &auxi );
    initialize_input_bitstream();
    initialize_arithmetic_decoder( compressed_file );

    //Se obtiene la instancia de fábrica y se construye el buffer según k
    Fabrica * fabrica = Fabrica::get_instance();
    Buffer * buffer = fabrica->fabricar_buffer( k );

    //Elementos utilizados a partir de ahora
    bool b;
    SYMBOL s;
    int c;
    unsigned int count;

    //Se leen los bits necesarios para obtener un estado de tamaño k
    int stop = ( ( k-1 )>>3 )+1; //Divido entre 8 y hago techo para saber cuantos caracteres imprimir para llenar k bits
    tamanio-= stop;
    for ( int i=0; i < stop; i++ )
    {
    	c = 0;
        for( int j=7; j>=0; j--)
        {
            s.scale = probabilities[ 1 ].high;
            count = get_current_count( &s );
            b = convert_symbol_to_int( count, &s );
            buffer->actualizar_historial( b ); //Se actualizan datos del buffer
            if(b == 1){
                c = c | ( 1<<j );
            }
            remove_symbol_from_stream( compressed_file, &s );
        }
        fprintf( original_file, "%c", c );
    }

    //Se fábrica diccionario según k
    Diccionario * diccionario = fabrica->fabricar_diccionario( k );

    //Continuación de descompresión
    for ( int j = 0; j < tamanio; j++ )
    {
    	c = 0;
        for( int i=7; i>=0; i--)
        {
            //Se obtiene el siguiente pixel y se obtienen contadores internamente (ver implementación)
            diccionario->preparar_historial( buffer->get_buffer() );

            //Se utiliza Krichevsky-Trofimov
            int contador[ 2 ] = { diccionario->get_cantidad_ceros(), diccionario->get_cantidad_unos() };
            probabilities[ 0 ].high = probabilities[ 1 ].low = ( contador[ 0 ]<<1 )+1;
            probabilities[ 1 ].high = ( contador[ 0 ] + contador[1] + 1 )<<1;
            s.scale = probabilities[ 1 ].high;

            //Se descomprime el símbolo actual
            count = get_current_count( &s );
            b = convert_symbol_to_int( count, &s );
            if( b == 1 )
            {
                c = c | ( 1<<i );
            }
            remove_symbol_from_stream( compressed_file, &s );

            //Se actualizan datos dentro del diccionario y buffer
            buffer->actualizar_historial( b );
            diccionario->actualizar_contadores( b );

            
        }
        fprintf( original_file, "%c", c );
    }
    
    //Procesos finales y liberación de memoria
    fclose( compressed_file );
    fclose( original_file );
    delete diccionario;
    delete buffer;

    //Reseteo de vector de probabilidades para posterior uso
    probabilities[ 0 ].low = 0;
    probabilities[ 0 ].high = 1;
    probabilities[ 1 ].low = 1;
    probabilities[ 1 ].high = 2;
}

void convert_int_to_symbol( bool b, SYMBOL *s )
{
    s->low_count = probabilities[ b ].low;
    s->high_count = probabilities[ b ].high;
    s->scale = probabilities[ 1 ].high;
}

bool convert_symbol_to_int( unsigned int count, SYMBOL *s )
{
    bool i = 0;
    for ( ; ; i=1 )
    {
        if ( count < probabilities[ i ].high ) //Solo se checkea si es menor o mayor ya que hay 2 símbolos posibles
        {
            s->low_count = probabilities[ i ].low;
            s->high_count = probabilities[ i ].high;
            s->scale = probabilities[ 1 ].high;
            break;
        }
    }
    return i;
}

void error_exit( char* message )
{
    puts( message );
    exit( -1 );
}
