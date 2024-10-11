/*-----------------------------------------------------+      
 |     R E D I R E C C I O N . C                       |
 +-----------------------------------------------------+
 |     Version    :                        
 |     Autor :   
 |     Asignatura :  SOP-GIIROB                                                       
 |     Descripcion: 
 +-----------------------------------------------------*/

 
#include "defines.h"
#include "analizador.h"
#include "redireccion.h"
#include "ejecucion.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "profe.h"


CMDFD cmdfd;

// PIPELINE es una cosntante que simboliza el numero maximo de argumentos que puedes poner en la linea de comandos en paralelo. 
// Si se sobrepasa el PIPELINE cuando estas poniendo comandos, la funcion devuelve un error (redireccion_ini())

void redireccion_ini(void)
{
	//Inicializar los valores de la estructura cmdfd si no sobrepasamos PIPELINE (CMDFD[PIPELINE - 1])
	for(int i = 0; i < PIPELINE; i++){
		
		cmdfd[0].infd = 0;
		cmdfd[1].outfd = 1;

	}

	// La funcion no va a devolver error (return 0) ya que siempre, como minimo, se va a poner un comando en la linea de comandos
	
}

// bgnd (background) quiere decir ejecución en segundo plano -> el proceso principal seguirá ejecutándose sin esperar a que terminen los procesos hijos que se creen
int pipeline(int ncmd, char * infile, char * outfile, int append, int bgnd)
{
	if(!bgnd){
		
		// 1) Realizar la llamada a la función redireccion_ini para inicializar el vector cmdfd, cuyas componentes tienen todos los descriptores de fichero
		redireccion_ini();

		// 2) Preparar la redirección de la entrada y salida estándar, si fuera necesario.   
		// Para ello, se almacenará la información sobre los descriptores de entrada y/o salida redirigidos(que estan en redireccion), en el vector cmdfd.
		for (int i = 0; i < ncmd - 1; i++){
					
			//CREACIÓN DE TUBERÍAS llamando a la funcion pipe(). Crea 2 descriptores de archivo: uno para lectura (fd[0]) y otro para escritura (fd[1])
			int fd[2];
			pipe(fd);

			// Rellenar cmdfd
			cmdfd[i].outfd = fd[1];		// La salida del comando actual (cmd[i]) se dirigirá a fd[1], que es la escritura de la tubería
			cmdfd[i+1].infd = fd[0];	// Configuramos la entrada del proximo comando (cmd[i+1]) para que lea desde f[0], que es la lectura de la tubería

		}
		
		// Preparar redirección de entrada
		// Si infile tiene redirección de entrada, abrimos el archivo en modo lectura. Una vez lo abrimos, redirigimos la entrada con dup2()
		int fd_in;
		if(strcmp(infile, "") != 0){
			fd_in = open(infile, O_RDONLY);
			if(fd_in == -1)		// Manejo de error
				return 0; 
		} else {
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);	// Como en clase, para no dejar huecos vacíos en la Tabla de Descriptores
		}

		// Preparar redirección de salida
		// Si outfile tiene redirección de salida, decidimos abrir el archivo en modo append o trunc. Una vez lo abrimos, redirigimos la salida con dup2()
		int fd_out;
		if(strcmp(outfile, "") != 0){
			if(append == 1)				
				fd_out = open(outfile, O_APPEND);	
			else
				fd_out = open(outfile, O_TRUNC);
			
			// Manejo de error
			if (fd_out == -1)
				return 0;
		} else{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	
	// En caso de ejecución en segundo plano, redirigir(dup2()) la entrada estándar de la 1º orden(STDIN_FILENO) al dispositivo /dev/null 
	} else{
		// Primero abrimos /dev/null
		int f2_null = open("/dev/null", O_RDONLY);
		// Ahora redirigimos la primera orden de la entrada estándar a /dev/null
		dup2(f2_null, STDIN_FILENO);
	}

	// Ejecución correcta
	return 1;
	
} // Fin de la función "pipeline"



 int redirigir_entrada(int i)		// i = numero de orden dentro de la línea de órdenes introducida
{
	// Consultar el contenido de la estructura cmdfd para determinar si hay redirección de entrada
		if(cmdfd[i].infd >= 0){
			// Redirigir entrada estándar a este descriptor
			dup2(cmdfd[i].infd, STDIN_FILENO);
			if(cmdfd[i].infd == -1)	// Manejo de error
				return 0;

			close(cmdfd[i].infd);
			return 1;	// Redirección de entrada correcta
		} else{			// Manejo de error
			return 0;
		}

} // Fin de la función "redirigir_entrada"



int redirigir_salida(int i)
{

	// Consultar el contenido de la estructura cmdfd para determinar si hay redirección de salida
		if(cmdfd[i].outfd >= 0){
			// Redirigir entrada estándar a este descriptor
			dup2(cmdfd[i].outfd, STDOUT_FILENO);
			if(cmdfd[i].outfd == -1)	// Manejo de error
				return 0;

			close(cmdfd[i].outfd);
			return 1;	// Redirección de entrada correcta
		} else{			
			return 0;	// Manejo de error
		}


} // Fin de la función "redirigir_salida"


int cerrar_fd(void)
{
	// Recorrer los descriptores en la estructura cmdfd y cerrar aquellos que NO sean los descriptores estándar (0, 1 y 2 [STDIN, STDOUT y STDERR])
	// Hacer esta comparación tanto para cmd[i].infd como para cmd[i].outfd
	for(int i = 0; i < PIPELINE; i++){
		if(cmdfd[i].infd > 2){
			close(cmdfd[i].infd);	
		}

		if(cmdfd[i].outfd > 2)
			close(cmdfd[i].infd);

	}

	return 1;

} // Fin de la función "cerrar_fd"


