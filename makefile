# Directorio de archivos fuente
SRCDIR = ./
# "all" es el objetivo por defecto. Sus dependencias se comprueban cuando ejecute la orden "make" en el directorio actual. Puede haber más de una dependencia.
all : ejecutable
#### Reglas secundarias para compilar cada una de las dependencias.
ejecutable : main.o aeropuerto.o
	gcc -ggdb -Wall main.o aeropuerto.o -o ejecutable
main.o: $(SRCDIR)main.c
	gcc -c $(SRCDIR)main.c
aeropuerto.o: $(SRCDIR)aeropuerto.c
	gcc -c $(SRCDIR)aeropuerto.c
# "limpiar" es un objetivo falso. Sirve para borrar los archivos .o (objeto).
limpiar :
	rm *.o