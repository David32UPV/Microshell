/*-----------------------------------------------------+
 |     A N A L I Z A D O R . C                         |
 +-----------------------------------------------------+
 |     Version    :                                    |
 |     Autor      :                                    |
 |     Asignatura :  SOP-GIIROB                        |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/


#include "defines.h"
#include "analizador.h"
#include <string.h>


char line[MAXLINE+1];
char * lineptr;
char avline[MAXLINE+1];
char * avptr =avline ;
char *cmdlin[PIPELINE][MAXARG];
char *cmdlinorden[PIPELINE];
char **cmdlinargumentos[PIPELINE];
int  ncmd = 0;
int  narg[PIPELINE];


char infile[MAXNAME+1] = "";
char outfile[MAXNAME+1] = "";
int backgnd = FALSE;
int append = FALSE;


#define MAXERR 7
int errnum = 0;
 char *errstr[MAXERR] = {
   "Sintaxis correcta",
   "Se esperaba una orden",
   "Redireccion de entrada inesperada",
   "Pipeline inesperado", 
   "Redireccion de salida inesperada",  
   "Background inesperado",
   "Orden inesperada"  
 };



void inicializar(void);
int command(int i);
int check(char * ptr);
void getname(char * name);



int  analizar (char *s ) 
{
   int i, charok, cmdok;
   
   lineptr = s;
   
   analizador_ini();


   /*  1 */
   if ( cmdok=command(ncmd) ) ncmd++;
   
   if (cmdok) {
     /* 2 */
     if (check("<")) getname(infile);
    
     /* 3 */
     while ( check("|") && ncmd<PIPELINE && cmdok){ 
          if(cmdok = command(ncmd)) ncmd++;
     }
   }
  
   if (cmdok){
     /* 4 */
     if (check(">")) {
       if (check(">")) append = TRUE;
       getname(outfile);
     }
     
     /* 5 */
     if (check("&"))  backgnd = TRUE;
   
     /* 6 */
     if (check("\n")) return(OK);
   }
   if (ncmd==0) return (OK);
 
   fprintf(stderr,PROMPT);
   charok=lineptr-line;
   for(i=0; i<charok; i++) fprintf(stderr," ");
   fprintf(stderr,"^ inesperado.\n");
        
   if (!cmdok)          errnum=1;
   else if (check("<")) errnum=2;
   else if (check("|")) errnum=3;
   else if (check(">")) errnum=4;
   else if (check("&")) errnum=5;
   else errnum=6;
   fprintf(stderr, "Error de sintaxis en orden: %s.", cmdlin[ncmd-1][0]);
   fprintf(stderr, " %s\n", errstr[errnum]);
   return (ERROR);


}


void analizador_ini(void)
{
  int i;


   avptr=avline;
   ncmd=0;
   for(i=0; i<PIPELINE; i++) narg[i]=0;
   infile[0]='\0';
   outfile[0]='\0';
   backgnd = FALSE;
   append = FALSE;
   errnum=0;
}



int command(int i) 
{
  int j, flag, inword=FALSE, incmd=FALSE;
  
  narg[i]=0;
  for(j=0; j<MAXARG-1; ++j) {
      while(*lineptr==' ' || *lineptr=='\t')  ++lineptr;
      
      cmdlin[i][j] = avptr;
      cmdlin[i][j+1] = NULL;


      for(flag=0; flag==0;) {
         switch(*lineptr) {
         case '>':
         case '<':
         case '|':
         case '&':
         case '\n':
                if (inword==FALSE) cmdlin[i][j]= NULL;
                *avptr++ = '\0';
                return incmd;
         case ' ':
         case '\t':
                inword = FALSE;
                *avptr++ = '\0';
                flag = 1 ;
                break;
        default:
               inword = TRUE;
               incmd=TRUE;
               *avptr++ = *lineptr++;
               break;
       }
       narg[i] = j+1;
     }       
  }
  return incmd;
}    


int check(char * ptr)
{
   char *tptr;
   
   while (*lineptr==' ') lineptr++;
   tptr = lineptr;
   
   while (*ptr!='\0' && *ptr==*tptr) {
       ptr++;
       tptr++;
   }
   
   if (*ptr!='\0') return (FALSE);
   else {
         lineptr = tptr;
         return (TRUE);
   }
}


void getname(char * name)
{
   int i;
   while (*lineptr==' ') lineptr++;
   for (i=0; i<MAXNAME; ++i) {
       switch (*lineptr) {
        case ' ':
        case '>':
        case '<':
        case '|':
        case '&':
        case '\n':
        case '\t':
                *name = '\0';
                return;
        default:
                *name++ = *lineptr++;
                break;
       }
       *name = '\0';
   }
}


int  num_ordenes ()
{
  return ncmd;
}


char **get_ordenes (void)
{
  int i;


  for (i=0;i<num_ordenes();i++)
    cmdlinorden[i]=cmdlin[i][0];
  return cmdlinorden;
}


int  *num_argumentos (void)
{
  return narg;
}


char ***get_argumentos (void)
{
  int i,j;


  for(i=0;i<PIPELINE;i++)
    cmdlinargumentos[i] = (char * *) malloc(sizeof(char *) *  MAXARG);


  for (i=0;i<num_ordenes();i++)
    for (j=0;j<narg[i];j++)
        cmdlinargumentos[i][j]=cmdlin[i][j];
  return cmdlinargumentos; 
}


char *fich_salida ()
{
  return outfile;
}


char *fich_entrada ()
{
  return infile;
}


extern int  es_append ()
{
  return append;
}


int  es_background ()
{
  return backgnd;
}


char *error_sintactico ()
{
  return errstr[errnum];
}
