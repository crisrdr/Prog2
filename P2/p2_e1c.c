#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "point.h"
#include "stack_fDoble.h"

#define MAX_RAND 10

/*********************************** PROTOTIPOS FUNCIONES PRIVADAS ***********************************/

int int_cmp(const void *c1, const void *c2);

int int_print (FILE *pf, const void *a);

Stack *stack_order (Stack *s, int (*f_cmp)(const void *, const void *));

/*****************************************************************************************************/

int main (int argc, char *argv[]){
    Stack *stack=NULL, *new_stack=NULL;
    int n, i, m[MAX_RAND];

    if (argc < 2){
        fprintf(stdout,"Arguments missing\n");
        return 1;
    } else if (argc > 2){
        fprintf(stdout,"Too many arguments\n");
        return 1;
    }

    sscanf(argv[1],"%d",&n);        /* Asignación al primer argumento recibido al número de puntos a generar */

    if ((stack = stack_init ())==NULL){
        fprintf(stdout,"Run failed\n");
        return 1;
    }

    /* Generación e inserción de los enteros en la pila */
    srand(time(NULL));    
    for (i=0;i<n;i++){
        m[i] = rand() % MAX_RAND + 1;
        if ((stack_push(stack, &m[i]))==ERROR){
            fprintf(stdout,"Run failed\n");
            stack_free(stack);
            return 1;
        }
    }

    /* Impresión de la pila */
    fprintf(stdout,"Original stack:\n");
    if ((stack_print(stdout, stack, int_print)) < 0){
        fprintf(stdout,"Run failed\n");
        stack_free(stack);
        return 1;
    }

    /* Ordenación de los elementos de menor a mayor */
    if ((new_stack = stack_order(stack, int_cmp))==NULL){
        fprintf(stdout,"Run failed\n");
        stack_free(stack);
        return 1;
    }

    /* Impresión de la pila original (vacia) */
    fprintf(stdout,"Original stack:\n");
    if ((stack_print(stdout, stack, int_print)) < 0){
        fprintf(stdout,"Run failed\n");
        stack_free(stack);
        stack_free(new_stack);
        return 1;
    }

    /* Impresión de la pila ordenada */
    fprintf(stdout,"Ordered stack:\n");
    if ((stack_print(stdout, new_stack, int_print)) < 0){
        fprintf(stdout,"Run failed\n");
        stack_free(stack);
        stack_free(new_stack);
        return 1;
    }

    stack_free(stack);
    stack_free(new_stack);

    return 0;
}

/*********************************** DEFINICIONES FUNCIONES PRIVADAS ***********************************/

int int_cmp(const void *c1, const void *c2){
    if (!c1 || !c2)
        return INT_MIN;

    return (*(int *)c1 - *(int *)c2);
}

int int_print (FILE *pf, const void *a){
    if (!pf || !a) return -1;

    return fprintf(pf, "%d", *(int *)a);
}

Stack *stack_order (Stack *s, int (*f_cmp)(const void *, const void *)){
    Stack *sout=NULL;
    void *e, *ea;

    if (!s) return NULL;

    if ((sout = stack_init()) == NULL) return NULL;

    while (stack_isEmpty(s) == FALSE){
        if ((e = stack_pop (s)) == NULL){
            stack_free (sout);
            return NULL;
        } 
        while ((stack_isEmpty (sout) == FALSE) && (f_cmp(e,stack_top(sout)) < 0)){
            if ((ea = stack_pop (sout)) == NULL){
                stack_free(sout);
                return NULL;
            }
            if (stack_push(s, ea) == ERROR){
                stack_free(sout);
                return NULL;
            }
        }
        if (stack_push(sout, e) == ERROR){
            stack_free(sout);
            return NULL;
        }
    }
    return sout;
}
