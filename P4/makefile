####################### VARIABLES #######################

EXE = p4
OBJ = $(EXE).o bstree.o point.o

GCC = gcc -Wall -ansi -pedantic -c -g
GCC_MATH = g++ -L /usr/lib
VAL = valgrind --leak-check=full

##################### COMANDOS MAKE ######################

all: $(EXE)

p4: $(OBJ)
	$(GCC_MATH) -o $(EXE) $(OBJ)

p4.o: p4.c bstree.h types.h point.h
	$(GCC) p4.c

bstree.o: bstree.c bstree.h types.h
	$(GCC) bstree.c

point.o: point.c point.h types.h
	$(GCC) point.c

run:
	./$(EXE) tree_example.txt

val:
	$(VAL) ./$(EXE) tree_example.txt

clean:
	rm *.o $(EXE)