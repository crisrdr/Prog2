####################### VARIABLES #######################

EXE_1 = p2_e1a
OBJ_1 = point.o $(EXE_1).o

EXE_2 = p2_e1b
OBJ_2 = point.o $(EXE_2).o

EXE_3 = p2_e1c
OBJ_3 = point.o $(EXE_3).o

EXE_4 = p2_e2
OBJ_4 = point.o map.o $(EXE_4).o

EXE_5 = p2_e3_e1b
OBJ_5 = point.o map.o stack_fDoble.o $(EXE_2).o

GCC = gcc -Wall -ansi -pedantic -c -g 
GCC_MATH = g++ -L /usr/lib

VAL = valgrind --leak-check=full

##################### COMANDOS MAKE ######################

## GENERAL ##

all: $(EXE_1) $(EXE_2) $(EXE_3) $(EXE_4) $(EXE_5)

all_5: $(EXE_5)

all_4: $(EXE_4)			# EJERCICIO 3 #

all_3: $(EXE_3)			# EJERCICIO 1 - APARTADO C #

all_2: $(EXE_2)			# EJERCICIO 1 - APARTADO B #

all_1: $(EXE_1)			# EJERCICIO 1 - APARTADO A #

point.o: point.c point.h types.h
	$(GCC) point.c

map.o: map.c map.h point.h types.h stack_fDoble.h
	$(GCC) map.c

clean:
	rm *.o $(EXE_1) $(EXE_2) $(EXE_3) $(EXE_4) $(EXE_5)

## EJERCICIO 1 - APARTADO A ##

p2_e1a: $(OBJ_1)
	$(GCC_MATH) -o $(EXE_1) $(OBJ_1)
	
p2_e1a.o: $(EXE_1).c point.h types.h
	$(GCC) $(EXE_1).c

run1:
	./$(EXE_1) 5

val1:
	$(VAL) ./$(EXE_1) 5

## EJERCICIO 1 - APARTADO B ##

p2_e1b: $(OBJ_2) libstack_fDoble.a 
	$(GCC_MATH) -o $(EXE_2) $(OBJ_2) libstack_fDoble.a 
	
p2_e1b.o: $(EXE_2).c point.h types.h stack_fDoble.h
	$(GCC) $(EXE_2).c

run2:
	./$(EXE_2) 5

val2:
	$(VAL) ./$(EXE_2) 5

## EJERCICIO 1 - APARTADO C ##

p2_e1c: $(OBJ_3) libstack_fDoble.a
	$(GCC_MATH) -o $(EXE_3) $(OBJ_3) libstack_fDoble.a

p2_e1c.o: $(EXE_3).c point.h types.h stack_fDoble.h
	$(GCC) $(EXE_3).c

run3:
	./$(EXE_3) 5

val3: 
	$(VAL) ./$(EXE_3) 5

## EJERCICIO 2 ##

p2_e2: $(OBJ_4) libstack_fDoble.a
	$(GCC_MATH) -o $(EXE_4) $(OBJ_4) libstack_fDoble.a

p2_e2.o: $(EXE_4).c point.h map.h types.h stack_fDoble.h
	$(GCC) $(EXE_4).c

run4:
	./$(EXE_4) laberinto_1.txt

val4: 
	$(VAL) ./$(EXE_4) laberinto_1.txt

## EJERCICIO 3 ##ibstack_fDoble.o

p2_e3_e1b: $(OBJ_5)
	$(GCC_MATH) -o $(EXE_5) $(OBJ_5) 

run5:
	./$(EXE_5) 5

val5:
	$(VAL) ./$(EXE_5) 5



