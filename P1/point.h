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

#include "types.h" 

#define ERRORCHAR 'E'
#define INPUT 'i'
#define OUTPUT 'o'
#define BARRIER '+'
#define SPACE '.'

/* START [_Point] */
typedef struct _Point Point;
/* END [_Point] */


/** YA ESTA
 * @brief Constructor. Initialize a point.
 * 
 * This function allocates memory for a point and sets its fields acoording 
 * its input parameter values.
 *
 * @code
 ************* Example of use
 * Point * v;
 * v = point_new (0, 0, BARRIER);
 * @endcode
 *
 * @param x Point x coordinate 
 * @param y Point y coordinate 
 * @param symbol Point symbol 
 * 
 * @return Return the initialized point if it was done correctly, 
 * otherwise return NULL.
*/
Point * point_new (int x, int y, char symbol);

/** YA ESTA
 * @brief Destructor. Free the dynamic memory reserved for a point .
 *
 * @param p Point to free
 */

void point_free (Point *p);


/** YA ESTA
 * @brief Gets the x coordinate of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the x coordinate of a given point, or INT_MAX in 
 * case of error.
 */
int point_getCoordinateX (const Point *p) ;


/** YA ESTA
 * @brief Gets the y coordinate of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the y coordinate of a given point, or INT_MAX in 
 * case of error.
 */
int point_getCoordinateY (const Point *p) ;


/** YA ESTA
 * @brief Gets the symbol of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the symbol coordinate of a given point, or ERRORCHAR in 
 * case of error.
 */
char point_getSymbol (const Point *p) ;


/** YA ESTA
 * @brief Modifies the x coordinate  of a given point.
 *
 * @param p Point pointer
 * @param x New x coordinate, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status point_setCoordinateX (Point *p, int x) ;


/** YA ESTA
 * @brief Modifies the y coordinate  of a given point.
 *
 * @param p Point pointer
 * @param y New y coordinate, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status point_setCoordinateY (Point *p, int y) ;


/** YA ESTA
 * @brief Modifies the symbol of a given point.
 *
 * @param p Point pointer
 * @param c New symbol, must be a valid symbol
 *
 * @return Returns OK or ERROR in case of error 
 */
Status  point_setSymbol (Point *p, char c) ;

Bool point_getVisited (const Point *p);             /* DFS (P2) */
Status point_setVisited (Point *p, Bool bol);       /* DFS (P2) */


/** YA ESTA
 * @brief Reserves memory for a point where it copies the data from
 * the point src.
 * 
 * @code
 * ***** Example of use
 * Point *trg, *src;
 * src = point_new();
 * trg = point_hardcpy(src);
 * **** .... aditional code ...
 * **** free points
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


/** YA ESTA
 * @brief Compares two points.
 * 
 * @param p1,p2 Points to compare.
 *
 * @return Returns True or False. 
 * In case of error, returns FALSE. 
 */
Bool point_equal (const void *p1, const void *p2);



/** YA ESTA
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
int point_print (FILE *pf, const void *p);  /* Print Stack */

#endif /* POINT_H */

