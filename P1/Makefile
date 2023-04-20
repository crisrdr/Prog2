####################### VARIABLES #######################

EXE_1 = p1_e1
OBJ_1 = point.o $(EXE_1).o

EXE_2 = p1_e2
OBJ_2 = point.o map.o $(EXE_2).o

EXE_3 = p1_e3
OBJ_3 = point.o map.o $(EXE_3).o

GCC = gcc -Wall -ansi -pedantic -c -g

##################### COMANDOS MAKE #####################

## GENERAL ##

all_3: $(EXE_3)

all_2: $(EXE_2)

all_1: $(EXE_1)

clean:
	rm *.o $(EXE_1) $(EXE_2) $(EXE_3)

## EJERCICIO 1 ##

p1_e1: $(OBJ_1)
	gcc -o $(EXE_1) $(OBJ_1)
	
p1_e1.o: $(EXE_1).c
	$(GCC) $(EXE_1).c

point.o: point.h point.c
	$(GCC) point.c

run1:
	./$(EXE_1)

val1:
	valgrind --leak-check=full -s ./$(EXE_1)

## EJERCICIO 2 ##

p1_e2: $(OBJ_2)
	gcc -o $(EXE_2) $(OBJ_2)

p1_e2.o: $(EXE_2).c
	$(GCC) $(EXE_2).c

map.o: map.h map.c
	$(GCC) map.c

run2:
	./$(EXE_2)

val2:
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(EXE_2)

## EJERCICIO 3 ##

p1_e3: $(OBJ_3)
	gcc -o $(EXE_3) $(OBJ_3)

p1_e3.o: $(EXE_3).c
	$(GCC) $(EXE_3).c

run3:
	./$(EXE_3) laberinto_1.txt

val3:
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(EXE_3) laberinto_1.txt