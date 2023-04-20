/* 
 * File:   point.h
 * Author: profesores
 *
 * Created on 21 de enero de 2022, 15:50
 */

#ifndef POINT_H
#define POINT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "types.h" 

#define ERRORCHAR 'E'
#define INPUT 'i'
#define OUTPUT 'o'
#define BARRIER '+'
#define SPACE '.'

/* START [_Point] */
typedef struct _Point Point;
/* END [_Point] */



/**
 * @brief Constructor. Initialize a point.
 * 
 * This function allocates memory for a point and sets its fields acoording 
 * its input parameter values.
 *
 * @code
 *  Example of use
 * Point * v;
 * v = point_new (0, 0, BARRIER);
 * @endcode
 *
 * @param x Point x coordinate 
 * @param y Point y coordinate 
 * @param symbol Point symbol 
 * 
 * @return Return the initialized point if it was done correctly, 
 * otherwise return NULL. A point is valid if its coordinates are grater than 
 * zero and its symbol is allowed. 
 * Allowed symbols are: BARRIER, INPUT, OUTPUT or SPACE 
*/
Point * point_new (int x, int y, char symbol);

/**
 * @brief Destructor. Free the dynamic memory reserved for a point .
 *
 * @param p Point to free
 */
void point_free (Point *p);


/**
 * @brief Gets the x coordinate of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the x coordinate of a given point, or INT_MAX in 
 * case of error.
 */
int point_getCoordinateX (const Point *p) ;


/**
 * @brief Gets the y coordinate of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the y coordinate of a given point, or INT_MAX in 
 * case of error.
 */
int point_getCoordinateY (const Point *p) ;


/**
 * @brief Gets the symbol of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the x coordinate of a given point, or ERRORCHAR in 
 * case of error.
 */
char point_getSymbol (const Point *p) ;


/**
 * @brief Modifies the x coordinate  of a given point.
 *
 * @param p Point pointer
 * @param x New x coordinate, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status point_setCoordinateX (Point *p, int x) ;


/**
 * @brief Modifies the y coordinate  of a given point.
 *
 * @param p Point pointer
 * @param y New y coordinate, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status point_setCoordinateY (Point *p, int y) ;


/**
 * @brief Modifies the symbol of a given point.
 *
 * @param p Point pointer
 * @param c New symbol, must be a valid symbol
 *
 * @return Returns OK or ERRORCHAR in case of error 
 */
Status  point_setSymbol (Point *p, char c) ;

Bool point_getVisited (const Point *p); /* DFS (P2) */
Status point_setVisited (Point *p, Bool bol);    /* DFS (P2) */


/**
 * @brief Reserves memory for a point where it copies the data from
 * the point src.
 * 
 * @code
 *  Example of use
 * Point *trg, *src;
 * src = point_new();
 * trg = point_hardcpy(src);
 *  .... aditional code ...
 *  free points
 * point_free(src);
 * point_free(trg);
 * @endcode
 * 
 * @param src Original Point pointer
 *
 * @return Returns the pointer of the copied Point if everything 
 * went well, or NULL otherwise.
 */
Point *point_hardcpy (const Point *src);


/**
 * @brief Compares two points.
 * 
 * @param p1,p2 Points to compare.
 *
 * @return Returns True or False. 
 * In case of error, returns FALSE. 
 */
Bool point_equal (const void *p1, const void *p2);


/** 
 * @brief Prints in pf the data of a point.
 * 
 * The format will be: [(x, y): symbol], without line break at the 
 * end.
 *
 * @code
 * Point * v;
 * v = point_new ();
 * point_print (stdout, v);
 * @endcode
 *
 * @param pf File descriptor
 * @param v Point to be printed
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int point_print (FILE *pf, const void *p); 


/***********************   P2 ********************/

/* START [_EUC] */
/** 
 * @brief Calculate the euclidean distance betweeen two points.
 * 
 * The euclidean distance is defined as sqrt ((x1-x2)^2 + (y1-y2)^2) 
 * where (x1, y1) and (x2, y2) are the coordinate of both points 
 *
 * @code
 *  Example of use
 * const Point *p1, *p2;
 * double d;
 * p1 = point_new (x1, y1, BARRIER);
 * p2 = point_new (x2, y2, SPACE);
 * point_euDistance (p1, p2, &d);
 * printf ("%lf", d);
 *  .... additional code ....
 * @endcode
 *
 * @param p1 pointer to point
 * @param p2 pointer to point
 * @param distance addresss
 *
 * @return Returns OK or ERROR in case of invalid parameters
 */
Status point_euDistance (const Point *p1, const Point *p2, double *distance);

/**
 * @brief Compares two points using their euclidean distances to the point (0,0).
 *
 * 
 * @param p1,p2 Points to compare.
 *
 * @return It returns an integer less than, equal to, or greater than zero if
 * the euclidean distance of p1 to the origin of coordinates is found,  
 * respectively, to be less than, to match or be greater 
 * than the euclidean distance of p2. In case of error, returns INT_MIN. 
 */
int point_cmpEuDistance (const void *p1, const void *p2); 

/* END [_EUC] */


#endif /* POINT_H */

