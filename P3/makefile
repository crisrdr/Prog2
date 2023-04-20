####################### VARIABLES #######################

EXE_1 = p3_e1b
OBJ_1 = $(EXE_1).o sorted_queue.o libqueue.a point.o

EXE_2 = p3_e2
OBJ_2 = $(EXE_2).o sorted_queue.o libqueue.a point.o map.o

GCC = gcc -Wall -ansi -pedantic -c -g
GCC_MATH = g++ -L /usr/lib

VAL = valgrind --leak-check=full

##################### COMANDOS MAKE ######################

all: $(EXE_1) $(EXE_2)

sorted_queue.o: sorted_queue.c sorted_queue.h queue.h types.h
	$(GCC) sorted_queue.c

point.o: point.c point.h types.h
	$(GCC) point.c

map.o: map.c map.h point.h types.h queue.h
	$(GCC) map.c

list.o: list.c list.h types.h
	$(GCC) list.c

queue.o: queue.c list.h types.h queue.h
	$(GCC) queue.c

clean:
	rm *.o $(EXE_1) $(EXE_2)

# EJERCICIO 1 #

p3_e1b: $(OBJ_1)
	$(GCC_MATH) -o $(EXE_1) $(OBJ_1)

p3_e1b.o: $(EXE_1).c sorted_queue.h queue.h types.h point.h
	$(GCC) $(EXE_1).c

run1: 
	./$(EXE_1)

val1:
	$(VAL) ./$(EXE_1)

# EJERCICIO 2 #

p3_e2: $(OBJ_2)
	$(GCC_MATH) -o $(EXE_2) $(OBJ_2)

p3_e2.o: $(EXE_2).c map.h point.h types.h
	$(GCC) $(EXE_2).c

run2: 
	./$(EXE_2) laberinto_1.txt

val2:
	$(VAL) ./$(EXE_2) laberinto_1.txt