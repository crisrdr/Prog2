#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorted_queue.h"
#include "point.h"

#define MAX_RAND 100 
#define MAX_RAND_P 10
#define MAX_ELE 10
#define MAX_CHAR 120

/*--------PROTOTIPOS DE FUNCIONES PRIVADAS-------*/

int string_cmp(const void *s1, const void *s2);

int int_cmp(const void *c1, const void *c2);

int int_print (FILE *pf, const void *a);

int str_print(FILE *f, const void *x);

/*----------------------------------------------*/

int main(){
  Queue *q = NULL;
  Status st = OK;
  int *ele;
  int i, n;
  Point **p = NULL, *origin = NULL;
  double distance=0;
  char array[MAX_ELE][MAX_CHAR]={"nata","queso","vaca","zumo","maiz","cereza","trigo","tomate","azucar","tarta"};

  /* Solicitud de enteros a insertar */
  printf("Introduzca el número de enteros a insertar en la cola (entre 1 y 10): ");
  scanf("%d", &n);
  while (n<1 || n>10){
    printf("Debe encontrarse en el intervalo [1,10]: ");
    scanf("%d", &n);
  }

  if ((ele = (int*) malloc (n*sizeof(int))) == NULL) return EXIT_FAILURE;

  if ((q = queue_new()) == NULL){
    free(ele);
    return EXIT_FAILURE;
  }

  /* Inserción de los enteros en la cola de forma ordenada con squeue_push */
  srand(time(NULL));
  for (i=0; i < n; i++){
    ele[i] = rand() % MAX_RAND + 1;
    st = squeue_push(q, &ele[i], int_cmp);
    if (st == ERROR){
      free(ele);
      queue_free(q);
      return EXIT_FAILURE;
    }
  }

  /* Impresión de la cola de enteros ordenada */
  fprintf(stdout,"----ORDERED QUEUE OF INT----\n");
  fprintf(stdout,"Queue size: %ld\n",queue_size(q));
  queue_print(stdout, q, int_print);
  fprintf(stdout,"\n");

  free(ele);
  queue_free(q);

  /* Solicitud de enteros a insertar */
  printf("Introduzca el número de puntos a insertar en la cola (entre 1 y 10): ");
  scanf("%d", &n);
  while (n<1 || n>10){
    printf("Debe encontrarse en el intervalo [1,10]: ");
    scanf("%d", &n);
  }

  if ((p = (Point**) malloc (n*sizeof(Point*))) == NULL) return EXIT_FAILURE;

  if ((q = queue_new()) == NULL){
    free(p);
    return EXIT_FAILURE;
  }

  origin = point_new(0, 0, BARRIER);

  /* Generación e inserción de los puntos de forma ordenada en la cola */
  srand(time(NULL));          
  for (i=0; i < n; i++,distance=0){
    if ((p[i] = point_new(rand() % MAX_RAND_P + 1, rand() % MAX_RAND_P + 1, BARRIER)) == NULL){
      queue_free(q);
      point_free(origin);
      for (;i>=0;i--){
        point_free(p[i]);
      }
      free(p);
      return EXIT_FAILURE;
    }

    fprintf(stdout, "Point p[%d]=",i);
    point_print(stdout,p[i]);
    if ((point_euDistance(origin, p[i], &distance)) == ERROR){      /* Distancia de los puntos al origen */
      fprintf(stdout,"Run failed\n");     
      queue_free(q);
      point_free(origin);        
      for (;i>=0;i--){
        point_free(p[i]);
      }
      free(p);
      return EXIT_FAILURE;
    }
    fprintf(stdout," distance: %.6f\n", distance);

    st = squeue_push(q, p[i], point_cmpEuDistance);
    if (st == ERROR){
      queue_free(q);
      point_free(origin);        
      for (;i>=0;i--){
        point_free(p[i]);
      }
      free(p);
      return EXIT_FAILURE;
    }
  }

  /* Impresión de la cola de puntos ordenada */
  fprintf(stdout,"----ORDERED QUEUE OF POINTS----\n");
  fprintf(stdout,"Queue size: %ld\n",queue_size(q));
  queue_print(stdout, q, point_print);
  fprintf(stdout,"\n");

  queue_free(q);
  point_free(origin);
  for (i=0;i<n;i++){
    point_free(p[i]);
  }
  free(p);

  if ((q = queue_new()) == NULL){
    free(p);
    return EXIT_FAILURE;
  }

  /* Inserción de las palabras de forma ordenada en la cola */
  for (i=0; i< MAX_ELE; i++){
    st = squeue_push(q, array[i], string_cmp);
    if (!st) return st;
  }

  /* Impresión de la cola de cadenas */
  fprintf(stdout,"----ORDERED QUEUE OF STRINGS----\n");
  fprintf(stdout,"Queue size: %ld\n",queue_size(q));
  queue_print(stdout, q, str_print);
  fprintf(stdout,"\n");

  queue_free(q);

  return EXIT_SUCCESS;
}

/*--------DEFINICIONES DE FUNCIONES PRIVADAS-------*/

int string_cmp(const void *s1, const void *s2){
  return strcmp((char *)s1, (char *)s2);
}

int int_cmp(const void *c1, const void *c2){
  if (!c1 || !c2) return -1;

  return (*(int *)c1 - *(int *)c2);
}

int int_print (FILE *pf, const void *a){
    if (!pf || !a) return -1;

    return fprintf(pf, "%d ", *(int *)a);
}

int str_print(FILE *f, const void *x) {
  char *z = (char *) x;
  return fprintf(f, "%s ", z);
}