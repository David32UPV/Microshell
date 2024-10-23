/*-----------------------------------------------------+
 |     U S H. C                                        
 +-----------------------------------------------------+
 |     Versión :                                       |                      
 |     Autor :                                         |
 |     Asignatura :  SOP-GIIROB                        |                               
 |     Descripción :                                   |
 +-----------------------------------------------------*/
#include "defines.h"
#include "analizador.h"
#include "redireccion.h"
#include "ejecucion.h"
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "profe.h"

#include <stdio.h>
#include <limits.h>		// Para usar PATH_MAX


//
// Declaraciones de funciones locales
//
void visualizar( void );
int leerLinea( char *linea, int tamanyLinea );


//
// Prog. ppal.
// 
int main(int argc, char * argv[])
{
    
  char line[255];
  int res;
  char **m_ordenes;
  char ***m_argumentos;
  int *m_num_arg;
  int m_n;

  while(1)
  {
    
    do
    {
        res=leerLinea(line,MAXLINE);    
        if (res==-2) {
      		fprintf(stdout,"logout\n");
		      exit(0);
        }
	
    	  if (res==-1){
		      fprintf(stdout,"linea muy larga\n");
	      }
     }while(res<=0);

     if (analizar(line)==OK){
       m_n=num_ordenes();
	     m_num_arg=num_argumentos();
	     m_ordenes=get_ordenes();
	     m_argumentos=get_argumentos();
	     if(m_n>0)
	     {
          if (pipeline(m_n,fich_entrada(),fich_salida(),es_append(),es_background())==OK)
                    ejecutar(m_n,m_num_arg,m_ordenes,m_argumentos,es_background());
        }

      	visualizar();
     }
 }    

  return 0;
}





/****************************************************************/
/*                       leerLinea                             
  --------------------------------------------------------------
                                                               
   DESCRIPCIÓN:                                                 
   Obtiene la línea de órdenes para el mShell.    
   Util para depuracion.                                        
                                                                
   ENTRADA:                                                 
    linea - puntero a un vector de carácteres donde se almancenan los caracteres 
   leídos del teclado
    tamanyLinea - tamaño máximo del vector anterior

   SALIDA:
    -- linea - si termina bien, contiene como último carácter el retorno de carro.
    -- leerLinea -  Entero que representa el motivo de finalización de la función:
     > 0 - terminación correcta, número de caracteres leídos, incluído '\n'
     -1 - termina por haber alcanzado el número máximo de caracteres que se 
    espera leer de teclado, sin encontrar '\n'.
     -2 - termina por haber leído fin de fichero (EOF).
*/
/****************************************************************/
//char * getline(void)
int leerLinea( char *linea, int tamanyLinea )
{
	// PRIMERO, se tiene que mostrar el PROMPT por pantalla, compuesto por: 1) directorio actual de trabajo y 2) la cte PROMPT de defines.h
	// La cte PROMP se tiene que actualizar para que contenga el nombre del estudiante
	// getcwd() nos da el directorio actual de trabajo

	char cwd[PATH_MAX];		// Longitud máxima de una ruta en el sistema

	// Obtener el directorio de trabajo actual
	if(getcwd(cwd, sizeof(cwd)) != NULL)		// Si la llamada tiene éxito, la ruta se imprime en la consola
		printf("%s%s", cwd, PROMPT);
	else
		printf("Error al leer cwd");
		

	//SEGUNDO, tenemos que leer la linea con una iteracion y guardar los caractéres en el vector linea[]
	char c, *p;		// *p = *linea (esto lo hacemos bien hecho en la línea 121: puntero = puntero).
	int i = 0;
	int pipe_flag = 0;		// Variable que nos servirá para realizar un seguimiento de cuando se encuetra una tubería o pipe(|)
	p = linea;
	// Si i = tamanyLinea, debe haber un espacio para el terminador nulo '\0'
	while((c = getchar()) != EOF && c != '\n' && i < (tamanyLinea - 1)){
		// Almacenamos el carácter leído
		*p = c;	 // Almacena el carácter c en la posición actual de p
		p++;	// Mueve p a la siguiente posición en el buffer
		i++;	// Incrementa el contador de caracteres leídois

		// Detectamos si el carácter leído es un pipe '|'
		if(c =='|')
			pipe_flag = 1;
		else if (c != ' ' && pipe_flag == 1)	// Si después del pipe encontramos otro caráceter que no es un espacio en blanco -> el comando es correcto
			pipe_flag = 0;
			
	}
	
	// Condiciones para cuando se sale del bucle:

	// Si el usuario pulsa Ctrl + D (EOF)
	if(c == EOF){
		// Si no se ha leido nada antes del EOF
		if(i == 0)
			return -2;
		// Si sí se ha leido algo antes de EOF, devuelvo las líneas leídas
		else
			return i;
	}

	// Si se encuentra un pipe al final de la línea sin comando siguiente se produce un error
	if(pipe_flag == 1){
		printf("Error sintáctico: pipe (|) sin comando posterior\n");
		return -1;
	}

	if(c == '\n'){
		*p = '\n';		// Finaliza la cadena con '\n'
		return i + 1;	// Devuelves i + 1 porque tienes que incluir el salto de linea '\n'
	}

	 if(i >= tamanyLinea)
		return -1;

	// Como la función es de tipo int al final siempre ha de dolver un int
	return i;

}


/****************************************************************/
/*                       visualizar                             */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCIÓN:                                                 */
/* Visualiza los distintos argumentos de la orden analizada.    */
/* Util para depuracion.                                        */
/*                                                              */
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: void                                                 */
/*                                                              */
/****************************************************************/
void visualizar( void )
{   

	// Llamamos a las funciones 
	int n_ord = num_ordenes();
	int *n_arg = num_argumentos();
	char **ordenes = get_ordenes();
	char ***argumentos = get_argumentos();

	// Bucle anidado
	/*
	j < n_arg NO es válido pues j es un int y n_arg es un puntero, luego n_arg[i] es el contenido que hay
	 en ese puntero, el cual es de tipo int
	*/

	// Bucle que recorre cada orden
	for(int i = 0; i < n_ord; i++){	
		printf("Orden: %d: %s\n", i+1, ordenes[i]);		// i+1 y no i para que el usuario vea que empieza con la orden 1 y no 0
		printf("Número de argumentos: %d\n", n_arg[i]);

		for(int j = 0; j < n_arg[i]; j++){		
			printf("Argumento: %d: %s\n", j+1, argumentos[i][j]);
			
		}	
	}
		
	// Si hay redirección de entrada se indica el fichero de la redirección
	char *f_entrada = fich_entrada();
	if(f_entrada != NULL && strlen(f_entrada) > 0){
		printf("Redirección de entrada: %s\n", f_entrada);
	} else
		printf("No hay redirección de entrada\n");

	// Si hay redirección de salida se indica el fichero de la redirección + indicar si la redirección se ha realizado en modo append o en modo trunc
	char *f_salida = fich_salida();
	if(f_salida != NULL && strlen(f_salida) > 0){
		printf("Redirección de salida: %s\n", f_salida);
		if(es_append())
			printf("Modo de redirección de salida: Append\n");
		else
			printf("Modo de redirección de salida: Trunc\n");
	} else
		printf("No hay redirección de salida\n");

	// Si la orden se ha lanzado en foreground (primer plano) o en background (segundo plano)
	if(es_background())
		printf("La orden se ha lanzado en modo background\n");
	else
		printf("La orden se ha lanzado en modo foreground\n");

} // Fin de "visualizar"



