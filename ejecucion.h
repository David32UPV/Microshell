/*-----------------------------------------------------+      
 |     E J E C U C I O N . H                           |
 +-----------------------------------------------------+
 |     Version    :                                    |
 |     Autor      :                                    |
 |     Asignatura :  SOP-GIIROB                        |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#ifndef EJECUCION_H
#define EJECUCION_H



/*******************************************************************/
/*                        ejecutar                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/* DESCRIPCION:                                                    */
/* Crea los procesos para ejecutar el argumento especificado en    */
/* "ordenes".                                                      */          
/*                                                                 */
/* ENTRADA:                                                        */
/* nordenes: numero de ordenes del pipe que se quiere ejecutar.    */
/* nargs: vector con el numero de argumentos de cada orden.        */
/* ordenes: vector de cadenas con el nombre de las ordenes.        */
/* args: matriz de cadenas con los argumentos de cada orden,       */
/* es decir, en la posicion (i,0) se encuentra la orden i-esima,   */ 
/* y en la posicion (i,n)  con n>0 se encuentra el orgumento n de  */
/* la posicion i-esima.                                            */
/* bgnd: (TRUE o FALSE) indica si la instruccion se ejecuta en     */
/* modo backgroung.                                                */
/*                                                                 */
/* SALIDA: OK o ERROR.                                             */ 
/*                                                                 */
/* IMPORTANTE:                                                     */
/* * Depende del modulo "redireccion".                             */
/* * Se asume que se han creado las tuberias necesarias para su    */
/* ejecucion: pipeline() ha sido invocada.                         */
/*                                                                 */
/*******************************************************************/


extern int ejecutar (int nordenes , int *nargs , char **ordenes , char ***args , int bgnd);

#endif

