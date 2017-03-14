/*
 * MemoryManager.c
 *
 *  Created on: 10 mar. 2017
 *      Author: Ricardo Holthausen
 */

#include <stdio.h>
#include <stdlib.h>
#include "MemoryManager.h"

#define false 	0
#define true 	1
#define MAX 	99

// Creates the required structure to manage the available memory
void Create(T_handler* pHandler) {
	// We create a node with values 0 and MAX
	T_handler ptr = (T_handler) malloc(sizeof(struct T_Node));

	ptr->start = 0;
	ptr->end = MAX;
	ptr->next = NULL;

	*pHandler = ptr;
}

// Frees the required structure
void Destroy(T_handler* handler) {
	T_handler prev = NULL;

	while (*handler != NULL) {
		prev = *handler;
		*handler = (*handler)->next;
		free(prev);
	}
}

/* Returns in "ad" the memory address where the required block of memory with length "size" starts.
 * If this operation finishes successfully then "ok" holds a TRUE value; FALSE otherwise.
 */
void Allocate(T_handler* pHandler, unsigned size, unsigned* ad, unsigned* ok) {
//	T_handler ptr = *pHandler;
//	T_handler prev;
//	if (*pHandler == NULL) {
//		*ok = 0;
//		return;
//	} else if (((*pHandler)->end - (*pHandler)->start + 1) >= size) {
//		// There is enough space in the first T_Nide
//		if (((*pHandler)->end - (*pHandler)->start + 1) == size) {
//			// The first T_Node should be removed
//			(*ad) = (*pHandler)->start;
//			(*ok) = true;
//			*pHandler = ptr->next;
//			free(ptr);
//		} else {
//			(*ad) = ptr->start;
//			(*ok) = true;
//			(*pHandler)->start += size;
//		}
//	} else {
//		prev = ptr;
//		ptr = ptr->next;
//		while (ptr != NULL) {
//			if ((ptr->end - ptr->start + 1) >= size) {
//				// There is enough space in the first T_Nide
//				if ((ptr->end - ptr->start + 1) == size) {
//					// The first T_Node should be removed
//					(*ad) = (*pHandler)->start;
//					(*ok) = true;
//					prev->next = ptr->next;
//					free(ptr);
//					return;
//				} else {
//					(*ad) = ptr->start;
//					(*ok) = true;
//					ptr->start += size;
//					return;
//				}
//			} else {
//				prev = ptr;
//				ptr = ptr->next;
//			}
//		}
//		(*ok) = false;
//	}

	T_handler ptr = *pHandler;
	T_handler prev = NULL;

	while (ptr != NULL && ptr->end - ptr->start + 1 < size) {
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == NULL){
		*ok = false;
		return;
	}
	*ad = ptr->start;
	ptr->start += size;
	*ok = true;
	if (ptr->end < ptr->start) {
		if (prev != NULL) {
			prev->next = ptr->next;
			free(ptr);
		} else {
			prev = ptr;
			ptr = ptr->next;
			*pHandler = ptr;
			free(prev);
		}
	}
}

/* Frees a block of memory with length "size" which starts at "ad" address.
 * If needed, can be assumed to be a previous allocated block
 */
void Deallocate(T_handler* handler, unsigned size, unsigned ad) {
	T_handler node = (T_handler) malloc(sizeof(struct T_Node));
	T_handler ptr = *handler;

	node->start = ad;
	node->end = ad+size-1;

	while (ptr != NULL && ptr->next != NULL && ptr->next->end < node->start)
		ptr = ptr->next;

	if (ptr->start > node->start){
		node->next = ptr;
		(*handler) = node;
	}else{
		node->next = ptr->next;
		ptr->next = node;
	}
	if (ptr->end == node->start){
		ptr->end = node->end;
		ptr->next = node->next;
		free(node);
	}
}

// When Deallocating:
//  2 steps
//		1) Create a new T_Node, then connect the node
//		2) After connecting the node, check if two nodes are contiguous, expand one and remove the other

/* Shows the current status of the memory */
void Show(T_handler handler) {
	while (handler != NULL) {
		// Show the current T_Node
		printf("[%d, %d] ", handler->start, handler->end);
		// Go to the next T_Node
		handler = handler->next;
	}
	printf("\n");
}

