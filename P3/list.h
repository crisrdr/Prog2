/**
 * @file list.h
 * @author Programming II Teaching Team
 * @date 16 Mar 2022
 * @brief Public interface for a Circular Linked List implementation.
 */

#ifndef LIST_H
#define LIST_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * List type definition: a list of arbitrary elements.
 */
typedef struct _List List;

/**
 * p_list_ele_print type definition: pointer to a function that prints a
 * List element to an output stream. It is assumed that this function returns:
 * (1) the number of characters printed upon success; or
 * (2) a negative number in case of error.
 */
typedef int (*p_list_ele_print)(FILE *, const void*);

/**
 * @brief Public function that creates a new List.
 *
 * Allocates memory for the new List.
 *
 * @return Returns the address of the new list, or NULL in case of error.
 */
List *list_new();

/**
 * @brief Public function that checks if a List is empty.
 *
 * Note that the return value is TRUE for a NULL List.
 *
 * @param pl Pointer to the List.
 *
 * @return Boolean value TRUE if the list is empty or NULL, Boolean value FALSE
 * otherwise.
 */
Bool list_isEmpty(const List *pl);

/**
 * @brief Public function that pushes an element into the front position of a
 * List.
 *
 * Inserts into the front position the element received as argument.
 *
 * @param pl Pointer to the List.
 * @param e Element to be inserted into the List.
 *
 * @return Status value OK if the insertion could be done, Status value ERROR
 * otherwise.
 */
Status list_pushFront(List *pl, const void *e);

/**
 * @brief Public function that pushes an element into the back position of a
 * List.
 *
 * Inserts into the back position the element received as argument.
 *
 * @param pl Pointer to the List.
 * @param e Element to be inserted into the List.
 *
 * @return Status value OK if the insertion could be done, Status value ERROR
 * otherwise.
 */
Status list_pushBack(List *pl, const void *e);

/**
 * @brief Public function that pops the front element from a List.
 *
 * Extracts the front element from the List, returning it.
 *
 * @param pl Pointer to the List.
 *
 * @return Extracted element, NULL if the List is empty or NULL.
 */
void *list_popFront(List *pl);

/**
 * @brief Public function that pops the back element from a List.
 *
 * Extracts the back element from the List, returning it.
 *
 * @param pl Pointer to the List.
 *
 * @return Extracted element, NULL if the List is empty or NULL.
 */
void *list_popBack(List *pl);

/**
 * @brief This function is used to get a reference to the element in the front 
 * position of a list. 
 *
 * @param pl A pointer to the list.
 *
 * @return A pointer to the element in the front position, NULL in case of error.
 * */
void *list_getFront(List *pl);

/**
 * @brief This function is used to get a reference to the element in the back 
 * position of a list.
 *
 * @param pl A pointer to the list.
 *
 * @return A pointer to the element in the back position, NULL in case of error.
 * */
void *list_getBack(List *pl);

/**
 * @brief Public function that frees a List.
 *
 * Frees the memory allocated for the List.
 *
 * @param pl Pointer to the List.
 */
void list_free(List *pl);

/**
 * @brief Public function that returns the number of elements in a List.
 * Time complexity: O(1)
 *
 * @param pl Pointer to the List.
 *
 * @return Returns the number of elements in the List, or -1 if the List is NULL.
 */
int list_size(const List *pl);

/**
 * @brief Public function that prints the contenf of a List.
 *
 * Prints all the elements in the List, from front to rear, to an output stream.
 * To print an element this function calls the function specified when creating
 * the List, P_ele_print.
 *
 * Note that this function simply calls the P_ele_print function for each List
 * element, without printing any additional information. Any desired format must
 * be included in the P_ele_print function.
 *
 * @param fp Output stream.
 * @param pl Pointer to the List.
 *
 * @return The sum of the return values of all the calls to P_ele_print if these
 * values are all positive; the first negative value encountered otherwise. If the
 * function P_ele_print is well constructed, this means that, upon successful return,
 * this function returns the number of characters printed, and a negative value if
 * an error occurs.
 */
int list_print(FILE *fp, const List *pl, p_list_ele_print f);

#endif	/* LIST_H */
