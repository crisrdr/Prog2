#include <stdio.h>
#include "point.h"

#define MAX_RAND 100

int main(int argc, char *argv[])
{
    Point **p, *origin;
    int n, i, j, x;
    double distance;

    if (argc < 2)
    {
        fprintf(stdout, "Arguments missing\n");
        return 1;
    }
    else if (argc > 2)
    {
        fprintf(stdout, "Too many arguments\n");
        return 1;
    }

    sscanf(argv[1], "%d", &n); /* Asignación al primer argumento recibido al número de puntos a generar */

    p = (Point **)malloc(n * sizeof(Point *));

    origin = point_new(0, 0, BARRIER);

    /* Generación e impresión de los puntos */
    for (i = 0; i < n; i++, distance = 0)
    {
        if ((p[i] = point_new(rand() % MAX_RAND + 1, rand() % MAX_RAND + 1, BARRIER)) == NULL)
        {
            fprintf(stdout, "Run failed\n");
            for (j = 0; j < i; j++)
            {
                point_free(p[j]);
            }
            point_free(origin);
            free(p);
            return 1;
        }
        fprintf(stdout, "Point p[%d]=", i);
        point_print(stdout, p[i]);
        if ((point_euDistance(origin, p[i], &distance)) == ERROR)
        {
            fprintf(stdout, "Run failed\n");
            for (i = 0; i < n; i++)
            {
                point_free(p[i]);
            }
            point_free(origin);
            free(p);
            return 1;
        }
        fprintf(stdout, " distance: %.6f\n", distance);
    }

    /* Comparación de las distancias euclideas para todos los pares de puntos e impresión */

    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            if ((x = point_cmpEuDistance(p[i], p[j])) == INT_MIN)
            {
                fprintf(stdout, "Run failed\n");
                for (i = 0; i < n; i++)
                {
                    point_free(p[i]);
                }
                point_free(origin);
                free(p);
                return 1;
            }
            if (x <= 0)
            {
                fprintf(stdout, "p[%d] < p[%d]: False\n", i, j);
            }
            else
                fprintf(stdout, "p[%d] < p[%d]: True\n", i, j);
        }
    }

    /* Liberación final de memoria */
    for (i = 0; i < n; i++)
    {
        point_free(p[i]);
    }
    point_free(origin);
    free(p);

    return 0;
}