#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main (int argc, char *argv[]){
    FILE *f;
    Map *map = NULL;

    if (argc < 2){
        fprintf(stdout,"Arguments missing\n");
        return EXIT_FAILURE;
    } else if (argc > 2){
        fprintf(stdout,"Too many arguments\n");
        return EXIT_FAILURE;
    }

    if ((f = fopen(argv[1], "r")) == NULL){   /* Argumento en posicion 1, nombre del fichero de texto */
        fprintf(stdout,"Opening file failed\n");
        return EXIT_FAILURE;
    }

    if ((map = map_readFromFile(f)) == NULL){ /* Creación del mapa a partir del fichero */
        fprintf(stdout,"Run failed\n");
        fclose(f);
        return EXIT_FAILURE;
    }
    fclose(f);

    /* Impresión del mapa leido */
    fprintf(stdout, "Maze:\n");
    if (map_print (stdout, map) == -1){
        fprintf(stdout,"Run failed\n");
        map_free(map);
        return EXIT_FAILURE;
    }
    fprintf(stdout, "\n");

    /* Salida de la búsqueda en anchura */
    fprintf(stdout, "BFS:\n");
    if (map_bfs(stdout, map) == NULL){
        map_free(map);
        return EXIT_FAILURE;
    }
    map_free(map);

    return EXIT_SUCCESS;
}