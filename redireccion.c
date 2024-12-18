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
		
		cmdfd[i].infd = 0;
		cmdfd[i].outfd = 1;

	}	
}

// bgnd (background) quiere decir ejecuci�n en segundo plano -> el proceso principal seguir� ejecut�ndose sin esperar a que terminen los procesos hijos que se creen
int pipeline(int ncmd, char * infile, char * outfile, int append, int bgnd)
{	

	if(!bgnd){
		
		// 1) Realizar la llamada a la funci�n redireccion_ini para inicializar el vector cmdfd, cuyas componentes tienen todos los descriptores de fichero
		redireccion_ini();

  		// 2) Preparar la redirecci�n de la entrada y salida est�ndar, si fuera necesario.   
		// Para ello, se almacenar� la informaci�n sobre los descriptores de entrada y/o salida redirigidos(que estan en redireccion), en el vector cmdfd.
		for (int i = 0; i < ncmd - 1; i++){
					
			//CREACI�N DE TUBER�AS llamando a la funcion pipe(). Crea 2 descriptores de archivo: uno para lectura (fd[0]) y otro para escritura (fd[1])
			int fd[2];
			pipe(fd);

			// Rellenar cmdfd
			cmdfd[i].outfd = fd[1];		// La salida del comando actual (cmd[i]) se dirigir� a fd[1], que es la escritura de la tuber�a
			cmdfd[i+1].infd = fd[0];	// Configuramos la entrada del proximo comando (cmd[i+1]) para que lea desde f[0], que es la lectura de la tuber�a
		}
		
		// Preparar redirecci�n de entrada
		// Si infile tiene redirecci�n de entrada, abrimos el archivo en modo lectura. Una vez lo abrimos, redirigimos la entrada con dup2()
		if(strcmp(infile, "") != 0){
			cmdfd[0].infd = open(infile, O_RDONLY);
			if(cmdfd[0].infd == -1)		// Manejo de error
				return 0; 
		}

		// Preparar redirecci�n de salida		
		// Si outfile tiene redirecci�n de salida, decidimos abrir el archivo en modo append o trunc. Una vez lo abrimos, redirigimos la salida con dup2()
		if(strcmp(outfile, "") != 0){
			if(append == 1)				
				cmdfd[ncmd - 1].outfd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);	
			else
				cmdfd[ncmd - 1].outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
			
			// Manejo de error
			if (cmdfd[ncmd - 1].outfd == -1)
				return 0;
		}

	
	// En caso de ejecuci�n en segundo plano, redirigir(dup2()) la entrada est�ndar de la 1� orden(STDIN_FILENO) al dispositivo /dev/null 
	} else{
		// Primero abrimos /dev/null
		cmdfd[0].infd = open("/dev/null", O_RDONLY);
		if (cmdfd[0].infd == -1) 
			return 0;
	}

	// Ejecuci�n correcta
	return 1;
	
} // Fin de la funci�n "pipeline"



 int redirigir_entrada(int i)		// i = numero de orden dentro de la l�nea de �rdenes introducida
{
	// Consultar el contenido de la estructura cmdfd para determinar si hay redirecci�n de entrada
		if(cmdfd[i].infd != 0){
			// Redirigir entrada est�ndar a este descriptor
			dup2(cmdfd[i].infd, STDIN_FILENO);
		}
		else{			// Manejo de error
			return 0;
		}
	
		return 1;	// Redirecci�n de entrada correcta

} // Fin de la funci�n "redirigir_entrada"



int redirigir_salida(int i)
{

	// Consultar el contenido de la estructura cmdfd para determinar si hay redirecci�n de salida
		if(cmdfd[i].outfd != 1){
			// Redirigir entrada est�ndar a este descriptor
			dup2(cmdfd[i].outfd, STDOUT_FILENO);
		}
		else{			
			return 0;	// Manejo de error
		}

		return 1;	// Redirecci�n de salida correcta

} // Fin de la funci�n "redirigir_salida"


int cerrar_fd(void)
{
	// Recorrer los descriptores en la estructura cmdfd y cerrar aquellos que NO sean los descriptores est�ndar (0, 1 y 2 [STDIN, STDOUT y STDERR])
	// Hacer esta comparaci�n tanto para cmd[i].infd como para cmd[i].outfd
	for(int i = 0; i < PIPELINE; i++){
		if(cmdfd[i].infd > 2){
			close(cmdfd[i].infd);
		}

		if(cmdfd[i].outfd > 2){
			close(cmdfd[i].outfd);
		}
			
	}

	return 1;

} // Fin de la funci�n "cerrar_fd"


