#include "point.h"

struct _Point {
    int x, y;
    char symbol;

    Bool visited;  /* for DFS */
};

Point * point_new (int x, int y, char symbol){
    Point *pointer;

    if ((symbol!=INPUT && symbol!=OUTPUT && symbol!=BARRIER && symbol!=SPACE)){
        return NULL;
    }

    if ((pointer = (Point *) malloc (sizeof(Point))) == NULL)
        return NULL;    

    pointer->x = x;
    pointer->y = y;
    pointer->symbol = symbol;
    pointer->visited = FALSE;

    return pointer;
}

void point_free (Point *p){
    free(p);
}

int point_getCoordinateX (const Point *p){
    if (p==NULL)
        return __INT_MAX__;
    else return p->x;
}

int point_getCoordinateY (const Point *p){
    if (p==NULL)
        return __INT_MAX__;
    else return p->y;
}

char point_getSymbol (const Point *p){
    if (p==NULL)
        return ERRORCHAR;
    else return p->symbol;
}

Status point_setCoordinateX (Point *p, int x){
    if (x<0 || p == NULL)
        return ERROR;
    p->x=x;
    return OK;
}

Status point_setCoordinateY (Point *p, int y){
    if (y<0 || p == NULL)
        return ERROR;
    p->y=y;
    return OK;
}

Status  point_setSymbol (Point *p, char c){
    if ( !p || (c!=INPUT && c!=OUTPUT && c!=BARRIER && c!=SPACE))
        return ERROR;
    p->symbol = c;
    return OK;
}

Point *point_hardcpy (const Point *src){
    Point *p;
    
    if (src == NULL){
        return NULL;
    } 
    
    if ((p = point_new(src->x, src->y, src->symbol)) == NULL){
        return NULL;
    }  
    
    return p;
}

Bool point_equal (const void *p1, const void *p2){
    Point *_p1 = (Point *) p1;
    Point *_p2 = (Point *) p2;
    if (p1 == NULL || p2 == NULL) return FALSE;

    if ((_p1->x ==_p2->x) && (_p1->y ==_p2->y) && (_p1->symbol ==_p2->symbol) )
        return TRUE;    
    else 
        return FALSE;
}

int point_print (FILE *pf, const void *p){
    Point *pAux = (Point*)p;

    if (!pf || !p){
        return -1;
    }    

    return fprintf (pf, "[(%d, %d): %c]", pAux->x, pAux->y, pAux->symbol);
    
}  /* Print Stack */
