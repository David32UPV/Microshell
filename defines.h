/*-----------------------------------------------------+
 |     defines . H                                     |
 +-----------------------------------------------------+
 |     Version    :                                    |
 |     Autor      :                                    |
 |     Asignatura :  SOP-GIIROB                        |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define max(a,b) (((a)>(b)) ? (a): (b))

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define LOGO "MICRO SHELL (c)2023 Tu nombre\n"
#define PROMPT " : david_ush_$ "

#define MAXLINE 200
#define MAXARG 20
#define MAXNAME 100
#define PIPELINE 10


typedef struct
{
  int infd;
  int outfd;
}CMDFD[PIPELINE-1];


#endif

