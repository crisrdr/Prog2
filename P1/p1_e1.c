#include "point.h"

void fail_function (Point *x, Point *y){
    fprintf(stdout,"Run failed\n");
        point_free (x);
        point_free (y);
}

int main(){
    int i, j;
    char c;
    /* Punto 1: Array de 4 punteros */
    Point *p[4];

    /* Punto 2: Inicialización de los dos primeros puntos */
    if ((p[0] = point_new (0, 0, BARRIER)) == NULL){          /* Comprobación de la salida de la función */
        fprintf(stdout,"Run failed\n");
        return 1;
    }
    if ((p[1] = point_new (0, 1, BARRIER)) == NULL){
        fprintf(stdout,"Run failed\n");
        point_free (p[0]);
        return 1;
    }

    /* Punto 3: Impresión de puntos */
    if (point_print (stdout, p[0]) == -1){
        fail_function (p[0],p[1]);
        return 1;
    }
    if (point_print (stdout, p[1]) == -1){
        fail_function (p[0],p[1]);
        return 1;
    }
    fprintf(stdout,"\n");

    /* Punto 4: Comparación de puntos */
    fprintf(stdout,"Equal points p[0] and p[1]? ");
    if (point_equal(p[0],p[1]) == TRUE)
        fprintf(stdout,"Yes\n");
    else fprintf(stdout,"No\n");
    

    /* Punto 5: Asignación al tercer elemento del primero */
    fprintf(stdout,"Creating p[2]: ");
    /* Primero se obtiene cada elemento del primer punto */
    if ((i = point_getCoordinateX(p[0])) == __INT_MAX__){
        fail_function (p[0],p[1]);
        return 1;
    }
    if ((j = point_getCoordinateY(p[0])) == __INT_MAX__){
        fail_function (p[0],p[1]);
        return 1;
    }
    if ((c = point_getSymbol(p[0])) == ERRORCHAR){
        fail_function (p[0],p[1]);
        return 1;
    }
    /* Después se crea un punto en la tercera posición con estos elementos */
    if ((p[2] = point_new (i, j, c)) == NULL){
        fail_function (p[0],p[1]);
        return 1;
    }

    /* TAMBIÉN SE PUEDE HACER:
    
    if ((p[0] = point_hardcpy(p[2]))==NULL){
        fail_function(p[0],p[1]);
        return 1;
    }

     */

    /* Punto 6: Impresión del tercer punto */
    if (point_print (stdout, p[2]) == -1){
        fail_function (p[0],p[1]);
        point_free(p[2]);
        return 1;
    }
    fprintf(stdout,"\n");

    /* Punto 7: Comparación del primer y el tercer punto */
    fprintf(stdout,"Equal points p[0] and p[2]? ");
    if (point_equal(p[0],p[2]) == TRUE)
        fprintf(stdout,"Yes\n");
    else 
        fprintf(stdout,"No\n");

    /* Punto 8: Modificación del símbolo de p[2] */
    fprintf(stdout,"Modifying p[2]: ");
    if ((point_setSymbol(p[2], SPACE)) == ERROR){
        fail_function (p[0],p[1]);
        point_free(p[2]);
        return 1;
    }
    if ((point_print (stdout, p[2])) == -1){
        fail_function (p[0],p[1]);
        point_free(p[2]);
        return 1;
    }
    fprintf(stdout,"\n");

    /* Punto 9: Comparación del primer y el tercer punto (de nuevo, con el símbolo del tercero cambiado) */
    fprintf(stdout,"Equal points p[0] and p[2]? ");
    if (point_equal(p[0],p[2]) == TRUE)
        fprintf(stdout,"Yes\n");
    else
        fprintf(stdout,"No\n");

    /* Punto 10: Asignación al cuarto elemento del primero */
    fprintf(stdout,"Assign p[3] = p[0]\n");
    p[3]=p[0];

    /* Punto 11: Modificación del símbolo de p[3] */
    fprintf(stdout,"Modifying p[3]: ");
    if ((point_setSymbol(p[3], OUTPUT)) == ERROR){
        fail_function (p[0],p[1]);
        point_free(p[2]);
        point_free(p[3]);
        return 1;
    }
    if ((point_print (stdout, p[3])) == -1){
        fail_function (p[0], p[1]);
        point_free(p[2]);
        point_free(p[3]);
        return 1;
    }
    fprintf(stdout,"\n");

    /* Punto 12: Impresión de los 4 puntos */
    for (i=0; i<4; i++){
        if ((point_print (stdout, p[i])) == -1){
            fail_function (p[0], p[1]);
            point_free(p[2]);
            point_free(p[3]);
            return 1;
        }
    } 
    fprintf(stdout,"\n"); 

    /* Liberación final de memoria */
    for (i=0; i<3; i++){
        point_free (p[i]);
    }   

    return 0;
}