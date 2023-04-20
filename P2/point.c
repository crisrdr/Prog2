#include "point.h"

/* FUNCION PRIVADA POTENCIA DE NUMERO num ELEVADO A i */

int pot_num (int num, int i){
    int p=num;
    while (i>1){
        p*=num;
        i--;
    }
    return p;
}

/*******************************************************/

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

Bool point_getVisited (const Point *p){
    if (!p) return FALSE;

    return p->visited;    
}

Status point_setVisited (Point *p, Bool bol){
    if (!p || (bol != TRUE && bol != FALSE)) return ERROR;

    p->visited = bol;

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
    
}

Status point_euDistance (const Point *p1, const Point *p2, double *distance){
    if (!p1 || !p2 || distance == NULL){
        return ERROR;
    }

    (*distance) = sqrt(pot_num((p1->x)-(p2->x),2) + pot_num((p1->y)-(p2->y),2));

    return OK;
}

int point_cmpEuDistance (const void *p1, const void *p2){
    Point *origin;
    double d1, d2;
    if ((origin = point_new(0,0,BARRIER)) == ERROR){
        return INT_MIN;
    }

    if ((point_euDistance(p1, origin, &d1) == ERROR) || ((point_euDistance(p2, origin, &d2)) == ERROR)){
        return INT_MIN;
    }

    point_free(origin);

    return (d1-d2);
}