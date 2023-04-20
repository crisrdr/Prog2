/*
Para probar la función crea el programa p1_e3.c que reciba 
como argumento el nombre de un fichero de texto, cree un 
Map de acuerdo a la descripción contenida en ese fichero, 
imprima el mapa por pantalla e imprima por pantalla los 
vecinos del punto output y los de la esquina inferior 
derecha del mapa.
La ejecución de este programa debefuncionar sin problemas, 
incluyendo una gestión adecuada de la memoria (valgrind no 
debería mostrar fugas ni errores). A continuación se muestra 
la salida del programa cuando se ejecuta en la terminal el
comando:
*/
#include "map.h"

int main(int argc, char *argv[]){
    Map *map=NULL;
    Point *x=NULL, *y=NULL;
    FILE *f;

    if (argc < 2){
        fprintf(stdout,"Arguments missing\n");
        return 1;
    } else if (argc > 2){
        fprintf(stdout,"Too many arguments\n");
        return 1;
    }

    if ((f = fopen(argv[1], "r"))==NULL){   /* Argumento en posicion 1, nombre del fichero de texto */
        fprintf(stdout,"Opening file failed\n");
        return 1;
    }

    if ((map = map_readFromFile(f))==NULL){ /* Creación del mapa a partir del fichero */
        fclose(f);
        return 1;
    }
    fclose(f);

    if ((map_print(stdout,map))==-1){       /* Impresión del mapa por pantalla */
        fprintf(stdout,"Run failed\n");
        map_free(map);
        return 1;
    }

    fprintf(stdout,"\nGet output neighboors:\n");
    if ((y = point_new(point_getCoordinateX(map_getOutput(map)), point_getCoordinateY(map_getOutput(map)), point_getSymbol(map_getOutput(map))))==NULL){
        fprintf(stdout,"Run failed\n");
        map_free(map);
        return 1;
    }
    if ((x = point_new (point_getCoordinateX(y), point_getCoordinateY(y), point_getSymbol(y)))==NULL){
        fprintf(stdout,"Run failed\n");
        map_free(map);
        point_free(y);
        return 1;
    }
    point_free(y);
    if (                                                                    /* Prueba de errores */
        (point_print(stdout, map_getNeighboor(map, x, RIGHT)) == -1) ||
        (point_print(stdout, map_getNeighboor(map, x, UP)) == -1) ||
        (point_print(stdout, map_getNeighboor(map, x, LEFT)) == -1) ||
        (point_print(stdout, map_getNeighboor(map, x, DOWN)) == -1))
    {
        printf("Run failed\n");
        map_free(map);
        point_free(x);
        return 1;
    }

    fprintf(stdout,"\n");  

    fprintf(stdout,"Get right inferior corner neighboors:\n");
    if ((x = point_new (map_getNrows(map)-1,map_getNcols(map)-1, BARRIER)) == NULL){
        map_free(map);
        
        return 1;
    }
    if (
        (point_print(stdout, map_getNeighboor(map, x, UP)) == -1) ||
        (point_print(stdout, map_getNeighboor(map, x, LEFT)) == -1)
    )

    fprintf(stdout,"\n");
    map_free(map);

    return 0;
}