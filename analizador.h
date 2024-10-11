/*-----------------------------------------------------+
 |     A N A L I Z A D O R . H                         |
 +-----------------------------------------------------+
 |     Version    :                                    |
 |     Autor      :                                    |
 |     Asignatura :  SOP-GIIROB                        |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#ifndef ANALIZADOR_H
#define ANALIZADOR_H


/****************************************************************/
/*                       analizador_ini                         */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Inicializa el analizador.                                    */
/*                                                              */
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: void                                                 */
/*                                                              */
/* IMPORTANTE:                                                  */ 
/* La iniciacion solo es necesaria si se invocan funciones      */
/* de la fase 2 sin introducir una orden en la fase 1.          */
/*                                                              */
/****************************************************************/

extern void analizador_ini(void);


/****************************************************************/
/*                      SINTAXIS                                */
/*--------------------------------------------------------------*/
/*                                                              */
/* cmd [ < filename ] [ | cmd ]... [ (> OR >>) filename ] [ & ] */
/*                                                              */
/****************************************************************/

/****************************************************************/
/*                        analizar                              */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Analiza una orden segun la sintaxis arriba especificada.     */
/*                                                              */
/* ENTRADA: una cadena con una orden para el shell.             */
/*                                                              */
/* SALIDA: OK o ERROR.                                          */
/*                                                              */
/****************************************************************/

extern int  analizar (char *s);


/*-----------------------------------------------------+
 |     FASE 2                                          |
 +-----------------------------------------------------*/

/****************************************************************/
/*                        num_ordenes                           */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Devuelve el numero de ordenes que han sido introducidas por  */
/* la cadena s en en el procenimiento analizar anterior.        */
/*                                                              */
/* ENTRADA: void.                                               */
/*                                                              */
/* SALIDA: Un entero que devuelve el numero de ordenes.         */
/****************************************************************/

extern int  num_ordenes (void);

/****************************************************************/
/*                        get_ordenes                           */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Devuelve un vector con las ordenes han sido introducidas por */
/* la cadena s en el procenimiento analizar anterior.           */
/*                                                              */
/* ENTRADA: void.                                               */
/*                                                              */
/* SALIDA: Un vector de strings que contiene las ordenes.       */
/*                                                              */
/****************************************************************/

extern char **get_ordenes (void);

/****************************************************************/
/*                        num_argumentos                        */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Devuelve un vector con el  numero de argumentos de cada una  */
/* de las ordenes que han sido introducidas por la cadena s en  */
/* el procedimiento analizar anterior.                          */
/*                                                              */
/* ENTRADA: void.                                               */
/*                                                              */
/* SALIDA: Un vector de enteros que contiene en cada posicion   */
/* el numero de argumentos de cada orden.                       */
/*                                                              */
/****************************************************************/

extern int  *num_argumentos (void);

/****************************************************************/
/*                        get_argumentos                        */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Devuelve una matriz con los argumentos de cada una de las    */
/* ordenes que han sido introducidas por la cadena s en el      */
/* procedimiento analizar anterior.                             */
/*                                                              */
/* ENTRADA: void.                                               */
/*                                                              */
/* SALIDA: Una matriz de cadenas equivalente a la estructura de */
/* la linea de comando, es decir, en la posicion (i,0) se       */
/* encuentra la orden i-esima, y en la posicion (i,n)  con n>0  */
/* se encuentra el orgumento n de la posicion i-esima.          */
/*                                                              */
/****************************************************************/

extern char ***get_argumentos (void);

/****************************************************************/
/*                       fich_salida                            */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Indica el fichero de la salida de una orden.                 */
/*                                                              */
/* ENTRADA: void.                                               */
/*                                                              */
/* SALIDA: Una cadena.                                          */
/*                                                              */
/****************************************************************/

extern char *fich_salida (void);

/****************************************************************/
/*                       fich_entrada                           */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Indica el fichero de la entrada de una orden.                */
/*                                                              */
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: Una cadena                                           */
/*                                                              */
/****************************************************************/

extern char *fich_entrada (void);

/****************************************************************/
/*                       es_append                              */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Indica si la salida debe ser anyadida al fichero al que se   */
/* redirecciona o si el contenido de este debe ser machacado.   */
/*                                                              */
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: TRUE o FALSE                                         */
/*                                                              */
/****************************************************************/

extern int  es_append (void);

/****************************************************************/
/*                       es_background                          */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Indica si las ordenes analizadas se han lanzado en background*/
/*                                                              */           
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: TRUE o FALSE                                         */
/*                                                              */
/****************************************************************/

extern int  es_background (void);

/****************************************************************/
/*                       error_sintactico                       */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Devulve el error sintactico que se ha comentido cuando se    */ 
/* analizaba la cadena de entrada.                              */
/*                                                              */
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: Cadena que indica el error sintactico                */
/*                                                              */
/****************************************************************/

extern char *error_sintactico (void);



#endif

