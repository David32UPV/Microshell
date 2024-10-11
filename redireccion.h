/*-----------------------------------------------------+      
 |     R E D I R E C C I O N . H                       |
 +-----------------------------------------------------+
 |     Version    :                                    |
 |     Autor      :                                    |
 |     Asignatura :  SOP-GIIROB                        |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#ifndef REDIRECCION_H
#define REDIRECCION_H


/*-----------------------------------------------------+
 |     FASE 1                                          |
 +-----------------------------------------------------*/


/*************************************************************************/
/*                       redireccion_ini                                  */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRIPCION:                                                          */
/* Inicializa la redireccion.                                            */
/*                                                                       */
/* ENTRADA: void                                                         */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

extern void redireccion_ini(void);


/*************************************************************************/
/*                      pipeline                                         */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRIPCION:                                                          */
/* Crea los tubos necesarios (n-1) para ejecutar n ordenes en tuberia y  */ 
/* abre los ficheros si existe redirección de entrada o de salida        */
/* Deben tener en cuenta la redirección de entrada si la orden es en     */
/* background.                                                           */
/*                                                                       */
/* ENTRADA:                                                              */
/* nmcd: numero de ordenes del pipe.                                     */
/* infile: fichero a donde se redirecciona la STD_INPUT.                 */
/* outfile: fichero a donde se redirecciona la STD_OUTPUT.               */
/* append: (TRUE o FALSE) indica si el fichero al que se redirecciona la */
/* salida standard se a?de la salida al final o debe ser sobreescrito.   */
/* bgnd: (TRUE o FALSE) indica si la instruccion se ejecuta en modo      */
/* background.                                                           */
/*                                                                       */
/* SALIDA: OK o ERROR.                                                   */
/*                                                                       */
/*************************************************************************/



extern int pipeline(int ncmd, char * infile, char * outfile, int append, int bgnd);


/*-----------------------------------------------------+
 |     FASE 2                                          |
 +-----------------------------------------------------*/


/*************************************************************************/
/*                       redirigir_entrada                               */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRPCION:                                                           */
/* Redirige la STD_INPUT del proceso i al descriptor fd del tubo/fichero */
/* correspondiente de la tuberia.                                        */
/*                                                                       */
/* ENTRADA: entero que identifica el proceso                             */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/*************************************************************************/

extern int redirigir_entrada(int i);

/*************************************************************************/
/*                       redirigir_salida                                */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRPCION:                                                           */
/* Redirige la STD_OUTPUT del proceso i al descriptor fd del tubo/fichero*/
/* correspondiente de la tuberia.                                        */
/*                                                                       */
/* ENTRADA: entero que identifica el proceso                             */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/*************************************************************************/

extern int redirigir_salida(int i);




/*************************************************************************/
/*                       cerrar_fd                                       */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRPCION:                                                           */
/* Cierra los descriptores fd de los tubos creados con pipeline y de los */
/* ficheros de las redirecciones.                                        */
/*                                                                       */
/* ENTRADA: void                                                         */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/* IMPORTANTE:                                                           */
/* * Es imprescindible cerrar TODOS los descriptores de fichero creados  */
/* o heredados de pipeline y las redirecciones que no van a utilizarse.  */  
/* Mientras no se cierren todos los fd de escritura sobre el tubo, el    */
/* lector del tubo no recibira EOF y permanecera esperando masdatos.     */ 
/*  El padre debe invocarlo despues de crear todos los hijos.            */
/* Los hijos deben invocarlo depues de redirigir STD_INPUT y STD_OUTPUT  */
/*                                                                       */
/*************************************************************************/


extern int cerrar_fd(void);


#endif

