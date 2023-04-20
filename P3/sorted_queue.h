#ifndef SORTED_QUEUE_H
#define	SORTED_QUEUE_H

#include <stdio.h>
#include "queue.h"
#include "types.h"

typedef Queue SortedQueue;

typedef int (*p_queue_ele_cmp)(const void *, const void *);

SortedQueue *squeue_new();
void squeue_free(SortedQueue *q);
Bool squeue_isEmpty(const SortedQueue *q);
Status squeue_push(SortedQueue *q, void *ele, p_queue_ele_cmp pcmp);
void *squeue_pop(SortedQueue *q);
void *squeue_getFront(const SortedQueue *q);
void *squeue_getBack(const SortedQueue *q);
size_t squeue_size(const SortedQueue *q);
int squeue_print(FILE *fp, const SortedQueue *q, p_queue_ele_print f);

#endif	/* SORTED_QUEUE_H */
