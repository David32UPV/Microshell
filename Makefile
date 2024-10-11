machine = $(shell uname -m)
ifeq ("$(machine)","x86_64")
	lib_file=profe.a
else
	lib_file=profe.a
endif


all: ush

todo: ush 

ush: ush.c defines.h analizador.h redireccion.h $(lib_file) analizador.o redireccion.o ejecucion.o
	gcc ush.c $(lib_file) analizador.o redireccion.o ejecucion.o -o ush
	strip ush

analizador.o: analizador.c defines.h
	gcc -c analizador.c

redireccion.o: redireccion.c defines.h
	gcc -c redireccion.c

ejecucion.o: ejecucion.c defines.h analizador.c redireccion.h
	gcc -c ejecucion.c

clean:
	rm *.o ush 



