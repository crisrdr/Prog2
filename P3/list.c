#include "list.h"


struct _Node {
    void * info ;
    struct _Node * next ;
};

typedef struct _Node Node ;

Node *node_new(){
    Node *pn = NULL;
    
    pn = (Node*) malloc (sizeof(Node));
    if (!pn) return NULL ;

    pn->info = NULL;
    pn->next = NULL;

    return pn;
}

struct _List {
    Node * first ;
    Node * last ;
};

List *list_new (){
    List *pl = NULL;

    pl = (List*) malloc (sizeof (List));
    if (pl == NULL) return NULL;

    pl->first = NULL;
    pl->last = NULL;
    
    return pl;
}

Bool list_isEmpty (const List *pl){
  if (pl == NULL) return TRUE ;

  if ((pl->first == NULL) && (pl->last == NULL)) return TRUE;
  
  return FALSE ;
}

Status list_pushFront ( List * pl , const void *e){
    Node *pn = NULL;
    
    if (pl == NULL || e == NULL) return ERROR;

    pn = node_new();
    if (pn == NULL) return ERROR;

    pn->info = (void*)e;
    pn->next = pl->first;

    pl->first = pn;

    return OK;
}

Status list_pushBack (List *pl, const void *e){
    Node *pn = NULL;

    if (pl == NULL || e == NULL) return ERROR;

    pn = node_new();
    if (pn == NULL) return ERROR;

    pn->info = (void*)e;
    if (list_isEmpty(pl) == TRUE){
        pl->first = pn;
        pl->last = pn;

        return OK;        
    }
    
    pl->last->next = pn;
    pn->next = NULL;

    return OK ;
}

void *list_popFront (List *pl){
    Node *pn = NULL;
    void *pe = NULL;

    if (pl == NULL || list_isEmpty (pl) == TRUE) return NULL ;

    pn = pl->first;
    
    pe = pn->info;               /* Equivalently : pe = pl ->first - > info */
    pl->first = pn->next;

    free (pn);

    return pe;
}

void *list_popBack ( List *pl){
    Node *pn = NULL;
    void *pe = NULL;

    if (pl == NULL || list_isEmpty (pl) == TRUE) return NULL;

    /* Case 1: List with one single element - extract the first element : */
    if (pl->first->next == pl->last){
        pe = pl->first->info;

        free(pl->first);
        free(pl->last);

        pl->first = NULL;
        pl->last = NULL;
        
        return pe ;
    }
    /* Case 2: List with more than one element - traverse the List and extract : */
    pn = pl->first;
    while (pn->next != pl->last){
        pn = pn->next;
    }
    pe = pn->next->info;

    free (pn->next);

    pn->next = NULL;

    return pe ;
}

void *list_getFront(List *pl){
    if (pl == NULL || list_isEmpty(pl) == TRUE) return NULL;

    return pl->first->info;
}

void *list_getBack(List *pl){
    if (pl == NULL || list_isEmpty(pl) == TRUE) return NULL;

    return pl->last->info;
}

void list_free (List *pl){
    if (pl == NULL) return;

    while (list_isEmpty(pl) == FALSE){
        list_popFront(pl);
    }

    pl->first = NULL;
    pl->last = NULL;

    free(pl);
}

int list_size(const List *pl){
    int i;
    Node *pn = NULL;

    if (pl == NULL || list_isEmpty(pl) == TRUE) return -1;

    pn = pl->first;

    if (pn == pl->last) return 1;

    for (i=2; pn->next != pl->last; i++){
        pn = pn->next;
    }

    return i;      
}

int list_print(FILE *fp, const List *pl, p_list_ele_print f){
    int n;
    Node *pn = NULL;

    if (fp == NULL || pl == NULL) return -1;

    pn = pl->first;

    for (n=0; n < list_size(pl); n++){
        f(fp, pn->info);
        pn = pn->next;
    }
    
    return n;
}