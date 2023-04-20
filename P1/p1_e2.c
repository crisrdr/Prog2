#include "map.h"

#define N_ROWS 4
#define N_COLS 3

#define Y_INPUT 1
#define X_INPUT 1
#define Y_OUTPUT 2
#define X_OUTPUT 1

int main (){
    Map *maps; 
    Point *x, *y;
    int i, j;

    /* Punto 1: Inicialización */
    if ((maps = map_new(N_ROWS,N_COLS))==NULL){     /* Prueba de errores */
        fprintf(stdout,"Run failed\n");
        return 1;
    }

    /* Punto 2: Inserción del laberinto */
    for(i=0; i<N_COLS; i++){
        for (j=0; j<N_ROWS; j++){
            y = point_new(j,i,BARRIER);
            if (i==X_INPUT && j==Y_INPUT){
                point_setSymbol(y,INPUT);
                if ((x = map_insertPoint(maps, y)) == NULL){      
                    fprintf(stdout,"Run failed\n");                                
                    map_free(maps);
                    return 1;
                }
            } else if (i==X_OUTPUT && j==Y_OUTPUT){
                point_setSymbol(y,OUTPUT);
                if ((x = map_insertPoint(maps, y)) == NULL){       
                    fprintf(stdout,"Run failed\n");                                    
                    map_free(maps);
                    return 1;
                }
            } else {
                if ((x = map_insertPoint(maps, y)) == NULL){      
                    fprintf(stdout,"Run failed\n");                  
                    map_free(maps);   
                    return 1;
                }    
            }   
            point_free(y);        
        }
    }

    /* Punto 3: Impresión del mapa */
    fprintf(stdout,"Map:\n");
 
    if (map_print(stdout,maps) == -1){
        fprintf(stdout,"Run failed\n");
        map_free(maps);
        return 1;
    }

    /* Punto 4: Vecinos del output */
    
    fprintf(stdout,"\nGet output neighboors:\n");
    if ((x = point_new(Y_OUTPUT, X_OUTPUT, OUTPUT)) == NULL){
        printf("Run failed\n");
        map_free(maps);
        return 1;
    }

    if (                                                                    /* Prueba de errores */
        (point_print(stdout, map_getNeighboor(maps, x, RIGHT)) == -1) ||
        (point_print(stdout, map_getNeighboor(maps, x, UP)) == -1) ||
        (point_print(stdout, map_getNeighboor(maps, x, LEFT)) == -1) ||
        (point_print(stdout, map_getNeighboor(maps, x, DOWN)) == -1))
    {
        printf("Run failed\n");
        point_free(x);
        map_free(maps);
        return 1;
    }
     
    fprintf(stdout,"\n");
                        
    point_free(x);
    map_free(maps);                                     /* Liberación final de memoria */
    
    return 0;
}