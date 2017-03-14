/*
 ============================================================================
 Name        : LabConcurrency01.c
 Author      : Llopis. Translated by Sergio Galvez Rojas.
 Version     :
 Copyright   : UMA. ETSII.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "MemoryManager.h"

int main () {
	T_handler handler;
	unsigned ok;
	unsigned ad; // Stands for "simulated" (ad)dress
	printf("The program has started.\n");
	Create(&handler);
	Show(handler);

	Allocate(&handler,50,&ad,&ok);
	printf("Allocated 50\n");
	if (ok) {
		Show(handler);
		printf("Starting address is: %d\n", ad);
	} else {
		printf("Unable to allocate such a memory\n");
	}

	Deallocate(&handler, 20,0);
	printf("Deallocated 20, 0\n");
	Show (handler);

	Allocate(&handler,25,&ad,&ok);
	printf("Allocated 25\n");
	if (ok) {
		Show(handler);
		printf("Starting address is: %d\n", ad);
	} else {
		printf("Unable to allocate such a memory\n");
	}

	Deallocate(&handler,10,50);
	printf("Deallocated 10, 50\n");
	Show(handler);

	Allocate(&handler,25,&ad,&ok);
	printf("Allocated 25\n");
	if (ok) {
		Show(handler);
		printf("Starting address is: %d\n", ad);
	} else {
		printf("Unable to allocate such a memory\n");
	}

	Deallocate(&handler, 20,75);
	printf("Deallocated 20, 75\n");
	Show(handler);


	Destroy(&handler);
	Show (handler);

	printf("End Of Program\n");

	system("PAUSE");

	return 0;
}

