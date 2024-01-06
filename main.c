//Copyright Matei Tudor-Andrei 314CAa
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"
#include "memory_allocation.h"
#include "utils.h"
#include "select.h"
#include "load_save.h"
#include "histogram.h"
#include "equalize.h"
#include "crop1.h"
#include "apply_kernel.h"
#include "rotate.h"

int main()
{
	char *command, *p = (char *)malloc(sizeof(char) * 256);
	command = (char *)malloc(sizeof(char) * 20);
	scanf("%s", command);
	// get our first command
	FILE *x = NULL;
	image p1; // our image
	p1.matrix = NULL;

	while (1) {
		if (!strcmp(command, "LOAD")) {
			if (p1.matrix) {
				free_matrix(&p1);
			}
			scanf("\n");
			fgets(p, 256, stdin);// get the name of file we are trying to load
			r_trail_whites(p);// remove the trailing whitespaces
			x = load_file(p);
			if (x != NULL) {
				//check if the file was loaded
				p1 = load_image(&x, p);
				fclose(x);
			}
		} else if (!strcmp(command, "SELECT")) {
			select_f(&p1);
		} else if (!strcmp(command, "EXIT")) {
			// free the memory
			if (p1.matrix) { //
				free_matrix(&p1);
			}
			   else {
				printf("No image loaded\n");
			}
			free(p);
			free(command);
			break;
		} else if (!strcmp(command, "HISTOGRAM")) {
			print_histogram(p1);
		} else if (!strcmp(command, "EQUALIZE")) {
			p1 = equalize(&p1);
		} else if (!strcmp(command, "CROP")) {
			p1 = crop(&p1);
		} else if (!strcmp(command, "APPLY")) {
			apply(&p1);
		} else if (!strcmp(command, "SAVE")) {
			scanf("%s", p);
			save(p1, p);
		} else if (!strcmp(command, "ROTATE")) {
			rotate(&p1);
		} else {
			//get the rest of the invalid command
			fgets(command, 20, stdin);
			printf("Invalid command\n");
		}
		// read the next command
		scanf("%s", command);
	}

	return 0;
}
