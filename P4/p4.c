#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "point.h"


BSTree * tree_read_points_from_file(FILE * pf);


int main (int argc, char *argv[]){
    FILE *f = NULL;
    BSTree *tree = NULL;
    Point *min = NULL, *max = NULL, *p = NULL;
    int x, y;
    Bool st;
    char r;

    if (argc < 2){
        fprintf(stdout,"Faltan argumentos\n");
        return EXIT_FAILURE;
    } else if (argc > 2){
        fprintf(stdout,"Demasiados argumentos\n");
        return EXIT_FAILURE;
    }

    if ((f = fopen(argv[1], "r")) == NULL){   /* Argumento en posicion 1, nombre del fichero de texto */
        fprintf(stdout,"Error al abrir el archivo\n");
        return EXIT_FAILURE;
    }

    tree = tree_read_points_from_file(f);
    if (!tree){
        fclose(f);
        return EXIT_FAILURE;
    }

    fclose(f);

    tree_preOrder(stdout,tree);

    min = tree_find_min(tree);
    max = tree_find_max(tree);

    if (!min || !max){
        fprintf(stdout, "Error al ejecutar el programa\n");
        tree_destroy(tree);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Tamaño del árbol: %ld\n", tree_size(tree));

    fprintf(stdout,"Mínimo del árbol: ");
    point_print(stdout, min);
    fprintf(stdout,"\n");

    fprintf(stdout,"Máximo del árbol: ");
    point_print(stdout, max);
    fprintf(stdout,"\n");

    fprintf(stdout, "\nIntroduce la coordenada x del punto a buscar: ");
    scanf("%d", &x);
    fprintf(stdout, "Introduce la coordenada y del punto a buscar: ");
    scanf("%d", &y);

    p = point_new (x, y, BARRIER);
    if (!p){
        fprintf(stdout, "Error al ejecutar el programa\n");
        tree_destroy(tree);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "¿Se encuentra el punto ");
    point_print(stdout, p);
    fprintf(stdout, " en el árbol?: %s\n", tree_contains(tree, p) ? "TRUE" : "FALSE");
    
    point_free(p);
    p = NULL;

    do {        /* Bucle para eliminar tantos puntos como se deseé*/
        do {
            fprintf(stdout, "\nIntroduce la coordenada x del punto a eliminar: ");
            scanf("%d", &x);
            fprintf(stdout, "Introduce la coordenada y del punto a eliminar: ");
            scanf("%d", &y);

            p = point_new (x, y, BARRIER);
            if (!p){
                fprintf(stdout, "Error al ejecutar el programa\n");
                tree_destroy(tree);
                return EXIT_FAILURE;
            }

            st = tree_contains(tree, p);

            if (!st){
                fprintf(stdout, "\nEl punto ");
                point_print(stdout, p);
                fprintf(stdout, " no se encuentra en el árbol.\n");
                point_free(p);
            }
        } while (!st);

        tree_remove(tree, p);

        tree_preOrder(stdout, tree);

        min = tree_find_min(tree);
        max = tree_find_max(tree);

        if (!min || !max){
            fprintf(stdout, "Error al ejecutar el programa\n");
            tree_destroy(tree);
            return EXIT_FAILURE;
        }

        fprintf(stdout, "Tamaño del árbol: %ld\n", tree_size(tree));

        fprintf(stdout,"Mínimo del árbol: ");
        point_print(stdout, min);
        fprintf(stdout,"\n");

        fprintf(stdout,"Máximo del árbol: ");
        point_print(stdout, max);
        fprintf(stdout,"\n");

        fprintf(stdout, "\n¿Se encuentra el punto ");
        point_print(stdout, p);
        fprintf(stdout, " en el árbol?: %s\n", tree_contains(tree, p) ? "TRUE" : "FALSE");

        fprintf(stdout, "\n¿Desea eliminar otro punto? (S/N): ");
        scanf("\n%c", &r);

    } while (((r == 's') || (r == 'S')) && !tree_isEmpty(tree));
    
    point_free(p);

    tree_destroy(tree);

    return EXIT_SUCCESS;
}


BSTree * tree_read_points_from_file(FILE * pf){
    BSTree * t;
    int nnodes=0, i;
    Status st = OK;
    int x, y;
    char symbol;
    Point * p;

    if (!pf){
        return NULL;
    }

    /* Read number of nodes */
    if (fscanf(pf, "%d\n", &nnodes) != 1) return NULL;

    /* Create tree */
    t = tree_init(point_print, point_cmpEuDistance);
    if(!t) return NULL;

    /* Read nodes */
    for (i=0; i<nnodes && st==OK ;i++){
        if(fscanf(pf, "%d %d %c", &x, &y, &symbol)!=3){
            return NULL;
        }
        p = point_new(x, y, symbol);
        if(!p){
            tree_destroy(t);
            return NULL;
        }

        st=tree_insert(t, p); 
        if(st==ERROR){
            tree_destroy(t);
            point_free(p);
            return NULL;      
        }
    }

    return t;
}