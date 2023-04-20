#include <stdio.h>
#include "point.h"
#include "stack_fDoble.h"

#define MAX_RAND 10

/************************** FUNCIÓN PRIVADA ****************************/

/**
 * @brief: Does an ordered stack with the greatest element at the top.
 * The origenal stack will be emptied.
 * 
 * @param sin, input stack
 * @return The function returns an ordered stack or NULL otherwise
 */ 
Stack *stack_orderPoints (Stack *sin);

/***********************************************************************/

int main (int argc, char *argv[]){
    Point **p, *origin;
    Stack *stack=NULL, *new_Stack=NULL;
    int n, i, j;    
    double distance;      

    if (argc < 2){
        fprintf(stdout,"Arguments missing\n");
        return 1;
    } else if (argc > 2){
        fprintf(stdout,"Too many arguments\n");
        return 1;
    }

    sscanf(argv[1],"%d",&n);        /* Asignación al primer argumento recibido al número de puntos a generar */

    if ((p = (Point **) malloc (n*sizeof(Point*)))==NULL){
        fprintf(stdout,"Run failed\n");
        return 1;
    }

    if ((origin = point_new(0, 0, BARRIER))==NULL){
        fprintf(stdout,"Run failed\n");
        free(p);
        return 1;
    }

    /* Generación e impresión de los puntos */
    for (i=0;i<n;i++,distance=0){
        if ((p[i] = point_new (rand() % MAX_RAND+1, rand() % MAX_RAND+1, BARRIER)) == NULL){
            fprintf(stdout,"Run failed\n");
            free(p);
            point_free(origin);
            for (j=0;j<i;j++){
                point_free(p[j]);
            }
            return 1;
        }
        fprintf(stdout, "Point p[%d]=",i);
        point_print(stdout,p[i]);
        if ((point_euDistance(origin, p[i], &distance)) == ERROR){      /* Distancia de los puntos al origen */
            fprintf(stdout,"Run failed\n");     
            free(p);
            point_free(origin);        
            for (i=0;i<n;i++){
                    point_free(p[i]);
            }
            return 1;
        }
        fprintf(stdout," distance: %.6f\n", distance);
    }

    /* Almacenar puntos en una pila */

    /* Creación de la pila */
    if ((stack = stack_init())==NULL){
        fprintf(stdout,"Run failed\n"); 
        free(p);
        point_free(origin);
        for (i=0;i<n;i++){
            point_free(p[i]);
        }
        return 1;
    }

    /* Inserción de los puntos en la pila */
    for (i=0;i<n;i++){
        if ((stack_push(stack,p[i]))==ERROR){
            fprintf(stdout,"Run failed\n");  
            free(p);
            point_free(origin); 
            for (i=0;i<n;i++){
                point_free(p[i]);
            }
            stack_free(stack);  
            return 1;
        }
    }

    /* Imprimir pila con los puntos */
    fprintf(stdout,"Original stack:\n");
    if ((stack_print(stdout, stack, point_print)) < 0){
        fprintf(stdout,"Run failed\n");  
        free(p);
        point_free(origin); 
        for (i=0;i<n;i++){
            point_free(p[i]);
        }
        stack_free(stack);  
        return 1;
    }   

    /* Ordenar elementos de la pila de menor a mayor según dist euclidea al origen */
    if ((new_Stack = stack_orderPoints(stack))==NULL){
        fprintf(stdout,"Run failed\n");  
        free(p);
        point_free(origin); 
        for (i=0;i<n;i++){
            point_free(p[i]);
        }
        stack_free(stack);  
        stack_free(new_Stack);
        return 1;
    }

    /* Imprimir pila ordenada */
    fprintf(stdout,"\nOrdered stack:\n");
    if ((stack_print(stdout, new_Stack, point_print)) < 0){
        fprintf(stdout,"Run failed\n");  
        free(p);
        point_free(origin); 
        for (i=0;i<n;i++){
            point_free(p[i]);
        }
        stack_free(stack); 
        stack_free(new_Stack);
        return 1;
    }

    /* Imprimir pila original (vacía) */
    fprintf(stdout,"\nOriginal stack:\n");
    if ((stack_print(stdout, stack, point_print)) < 0){
        fprintf(stdout,"Run failed\n");  
        free(p);
        point_free(origin); 
        for (i=0;i<n;i++){
            point_free(p[i]);
        }
        stack_free(stack); 
        return 1;
    }

    /* Liberación final de memoria */
    for (i=0;i<n;i++){
        point_free(p[i]);
    }
    point_free(origin);
    free(p);
    stack_free(stack);
    stack_free(new_Stack);

    return 0;
}

/********************** DEFINICIÓN FUNCIÓN PRIVADA **********************/

Stack *stack_orderPoints (Stack *sin){
    Stack *sout = NULL;
    Point *origin = NULL;
    const Point *e = NULL, *eaux = NULL;
    double de, dtop;

    if (!sin) return NULL;

    if ((sout = stack_init()) == NULL) return NULL;

    if ((origin = point_new(0, 0, BARRIER)) == NULL){
        stack_free(sout);
        return NULL;
    }

    while (stack_isEmpty(sin) == FALSE){
        if ((e = stack_pop(sin)) == NULL){
            stack_free(sout);
            point_free(origin);
            return NULL;
        }
        point_euDistance(origin, e, &de);
        point_euDistance(origin, stack_top(sout), &dtop);

        while ((stack_isEmpty(sout) == FALSE) && (de < dtop)) {
            if ((eaux = stack_pop(sout)) == NULL){
                stack_free(sout);
                point_free(origin);
                return NULL;
            }
            if ((stack_push(sin, eaux)) == ERROR){
                stack_free(sout);
                point_free(origin);
                return NULL;
            }
            
        } 

        if ((stack_push (sout, (const void*)e)) == ERROR){
            stack_free(sout);
            point_free(origin);
            return NULL;
        }
    }
    point_free(origin);
    return sout;
}