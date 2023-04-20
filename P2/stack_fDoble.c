#include "stack_fDoble.h"
#include <stdlib.h>


#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {
    void **item;             /*!<Dynamic array of elements*/
    int top;                 /*!<index of the top element in the stack*/
    int capacity;            /*!<xcapacity of the stack*/
};

Stack *stack_init (){
    Stack *s = NULL;
    int i;

    if ((s = (Stack*) malloc (sizeof(Stack))) == NULL) return NULL;

    s->capacity = INIT_CAPACITY;
    s->item = (void*) malloc ((s->capacity) * sizeof(void));
  

    for (i=0; i<s->capacity; i++){
        s->item[i] = NULL;
    }

    s->top = -1;
    return s;  
}

void stack_free (Stack *s){
    free (s->item);
    free (s);
}

Status stack_push (Stack *s, const void *ele){
    if (!s || !ele) return ERROR;

    s->top++;
    if (s->top == s->capacity){
        s->capacity *= FCT_CAPACITY;
        if ((s->item = (void**) realloc (s->item, (s->capacity) * sizeof(void*))) == NULL){
            return ERROR;
        }
    }
    s->item[s->top] = (void*)ele;
    return OK;
}

void *stack_pop (Stack *s){
    void *e;

    if (!s || stack_isEmpty(s) == TRUE) return NULL;

    e = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;

    return e;
}

void *stack_top (const Stack *s){
    if (!s || stack_isEmpty(s) == TRUE) return NULL;

    return s->item[s->top];
}

Bool stack_isEmpty (const Stack *s){
    if (!s) return TRUE;

    if (s->top == -1) return TRUE;

    return FALSE;
}

size_t stack_size (const Stack *s){
    if (!s) return -1;

    return s->top + 1;
}

int stack_print(FILE *fp, const Stack *s,  P_stack_ele_print f){
    int i=0;
    Stack *sAux = NULL;
    Status st = OK;
    void *e = NULL;

    if (!fp || !s) return -1;

    if ((sAux = stack_init()) == NULL) return -1;

    while (stack_isEmpty(s) == FALSE){
        st = stack_push(sAux, stack_pop((Stack*)s));
        if (st == ERROR){
            stack_free(sAux);
            return -1;
        }
    }
    while (stack_isEmpty(sAux) == FALSE){
        e = stack_pop(sAux);
        f(fp, e);
        i++;
        st = stack_push((Stack*)s,e);
        if (st == ERROR){
            stack_free(sAux);
            return -1;
        }
    }

    return i;
}