/*-----------------------------------------------------+      
 |     R E D I R E C C I O N . C                       |
 +-----------------------------------------------------+
 |     Version    :                                    |                      
 |     Autor :                                         |
 |     Asignatura :  SOP-GIIROB                        |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#include "defines.h"
#include "redireccion.h"
#include "ejecucion.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "profe.h"

// En la version sin ampliaciones NO tener en cuenta el parámetro bgnd (background)
int ejecutar (int nordenes , int *nargs , char **ordenes , char ***args , int bgnd)
{

	int val, i;
		
	// Proceso padre (shell), que crea un hijo para cada orden
	for(i = 0; i < nordenes; i++){
		val = fork();		
		
		if(val < 0)
			exit(1);
		
		// Hijo
		if(val == 0){
			// Antes de cambiar la imagen se han de resolver las redirecciones de las ordenes
			redirigir_entrada(i);		// i = orden 0, orden 1, orden 2, ...
			redirigir_salida(i);
			cerrar_fd();
			// ordenes[i] es el nombre del archivo ejecutable el cual contiene el nombre de la orden a ejecutar (e.g. ls, car, greo, etc.)
			// args[i] es un array de punteros a cadenas de caracteres (el conjunto de argumentos que se pasan al programa que se va a ejecutar)
			// e.g si yo pongo ls -l | grep profe, el execv seria execvp("ls", ["ls", "-l", NULL]); y esto reemplaza al hijo con el proceso que ejecuta ls -l.
			// Después el padre crearia con fork() el nuevo hijo que se sustituiría por grep profe, y así sucesivamente con cada nuevo comando que reciba la shell
   		 	if (execvp(ordenes[i], args[i]) == -1) {
        		perror("Error al ejecutar el comando");  // Mensaje específico de error
				exit(1);  // Finaliza el proceso hijo con un error
    		}

			// Si execvp tiene éxito, el proceso hijo ejecuta el nuevo programa y si falla el hijo continua ejecutandose 
		}

	}
	
	cerrar_fd();
	// Esperar a que los hijos acaben antes de continuar y devolver el OK
	while(wait(NULL) != -1);

	// Una vez el proceso padre salga de la espera deve devolver un OK (1)
	return OK;


} // Fin de la funcion "ejecutar"





