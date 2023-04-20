/* 
 * File:   map.h
 * Author: profesores
 *
 * Created on 21 de enero de 2022, 15:44
 */

#ifndef MAP_H
#define MAP_H

#include "point.h"

typedef enum {
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3,       
    STAY = 4
} Position;

typedef struct _Map Map;


/** YA ESTÁ
 * @brief  Creates a new empty Map with nrows and ncols.
 *
 * Allocates memory for a new map and initializes it to be empty 
 * (no points).
 * 
 * @param nrows, ncols Dimension of the map 
 *
 * @return A pointer to the graph if it was correctly allocated, 
 * NULL otherwise.
 **/
Map * map_new (unsigned int nrows,  unsigned int ncols);


/** YA ESTÁ
 * @brief Frees a graph.
 *
 * Frees all the memory allocated for the graph, including its points
 *
 * @param g Pointer to graph to be freed.
 **/
void map_free (Map *);

/** YA ESTÁ
 * @brief Inserts a point in a map.
 *
 * Insert a point in the map at the coordinates indicated by the point. 
 * The upper left corner point of the map has (0,0) coordinates.
 *
 * @param mp Pointer to the map.
 * @param p Pointer to the point to be inserted.
 *
 * @return Returns a pointer to the inserted point, NULL otherwise.
 **/
Point *map_insertPoint (Map *mp, Point *p);



/** YA ESTÁ
 * @brief  Returns the total number of columns
 * in the map.
 *
 * @param mp Pointer to the map.
 *
 * @return Returns The number of columns in the map, or -1 if 
 * there is any error.
 **/
int map_getNcols (const Map *mp);

/** YA ESTÁ
 * @brief  Returns the total number of rows
 * in the map.
 *
 * @param mp Pointer to the map.
 *
 * @return Returns The number of rows in the map, or -1 if 
 * there is any error.
 **/
int map_getNrows (const Map *mp); 

/*YA ESTA*/
Point * map_getInput(const Map *mp);   

/* YA ESTA*/     
Point * map_getOutput (const Map *mp);      


/** YA ESTA
 * @brief  Returns the map point with the same p coordinates.
 *
 * @param mp Pointer to the map.
 * @param p Pointer to the point
 *
 * 
 * @return Returns pointer to the map point , or NULL if 
 * there is any error.
 **/
Point *map_getPoint (const Map *mp, const Point *p);


/**YA ESTA
 * @brief  Returns the neighboor of the point p at the position pos
 * in the map.
 *
 * @param mp Pointer to the map.
 * @param p Pointer to the point
 * @param pos Neighboor position relative to the point being
 *  RIGHT = 0, UP = 1, LEFT = 2, DOWN = 3,STAY = 4,
 * 
 * @return Returns pointer to the neighboor, or NULL if 
 * there is any error.
 **/
Point *map_getNeighboor(const Map *mp, const Point *p, Position pos);

/* setters */
/*Ya está*/
Status map_setInput(Map *mp, Point *p);
/*Ya está*/
Status map_setOutput (Map *mp,Point *p);

/* START [map_readFromFile] */
/**
 * @brief Reads a map definition from a text file.
 *
 * Reads a map description from the text file pointed to by pf,
 * and fills the map. 
 * This function allocates memory for the map and its points.
 *
 * The file contains a header with the map number of rows and cols. 
 * The next file lines corresponds with the points of the map.
 *.
 * For example the file:
 *
 * 4 3
 * ++++
 * +io+
 * ++++
 *
 * Represents a map with 4 rows, 3 columns and the points:  
 * [(0, 0): +][(1, 0): +][(2, 0): +][(3, 0): +][(0, 1): +][(1, 1): i]
 * [(2, 1): o][(3, 1): +][(0, 2): +][(1, 2): +][(2, 2): +][(3, 2): +]
 *
 * @param pf, Pointer to the input stream.
 *
 * @return the map or NULL if there is any error
 */
Map * map_readFromFile (FILE *pf);   

/* END [map_readFromFile] */

/** YA ESTA
 * @brief Compares two maps.
 * 
 * @param p1,p2 Pointers to maps to compare.
 *
 * @return Returns True or False. 
 * In case of error, returns FALSE. 
 */
Bool map_equal (const void *_mp1, const void *_mp2); 
/* END [_map_readFromFile] */

/** YA ESTÁ
 * @brief Prints in pf a map
 * 
 * Prints the total number rows and columns and after a new line
 * the map points
 *
 * @code
 * Map * mp;
 *..... ********  additional code 
 * map_print (stdout, mp);
 * @endcode
 *
 * @param pf File descriptor
 * @param mp map to be printed
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int map_print (FILE*pf, Map *mp);   

/* DFS (P2) */
Point * map_dfs (Map *mp);  

#endif /* MAP_H */

