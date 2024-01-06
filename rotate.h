image rotate_right(image p)
{
	// rotates whole image to the right by 90 degrees
	image result;
	copy_size(p, &result);
	result.height = p.width;
	result.width = p.height;
	result = alloc_matrix(result);

	for (int i = 0; i < result.height; i++) {
		for (int j = 0; j < result.width; j++) {
			for (int k = 0; k < result.pixel_no; k++) {
				result.matrix[i][j].val[k] = p.matrix[p.height - j - 1][i].val[k];
			}
		}
	}

	select_all(&result);
	// the selection will be different for the new image, since the
	// size has changed
	free_matrix(&p); // free the old image
	return result;
}

int get_angle(char *command, int *angle)
{
	// gets the needed parameter
	// returns -1 if there are too many or none
	// returns 1 if there's exactly one number
	fgets(command, 30, stdin);
	char *word = strtok(command, "\n ");
	if (is_number(word)) {
		*angle = atoi(word);
		word = strtok(NULL, "\n ");
		if (word) {
			return -1;
		}
		return 1;
	} else {
		return -1;
	}
}

image rotate_right_selection(image p)
{
	// returns a new image that has the selected part rotated
	// by 90 degrees clockwise
	image temp;
	copy_image(p, &temp);
	int n = p.x2 - p.x1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < temp.pixel_no; k++) {
				temp.matrix[i + p.y1][j + p.x1].val[k] = p.matrix[n - j - 1 + p.y1][i + p.x1].val[k];
			}
		}
	}


	free_matrix(&p);// free the old image
	return temp;
}

void rotate(image *p)
{
	char *command = (char *)malloc(sizeof(char) * 30);
	int angle;
	int valid = get_angle(command, &angle);
	free(command);
	if (!p->matrix){
		printf("No image loaded\n");
		return;
	}
	if (!selected_all(*p)) {
		if (p->x2 - p->x1 != p->y2 - p->y1) {
			printf("The selection must be square\n");
			return;
		}
	}

	if (valid == -1) {
		// check if the command has the right number of parameters
		printf("Invalid command\n");
		return;
	}

	if (abs(angle) > 360 || angle % 90 != 0) { // check if the angle is valid
		printf("Unsupported rotation angle\n");
		return;
	}
	image aux;
	copy_image(*p, &aux);
	if (angle == 90 || angle == -270) {
		if (selected_all(*p)) {
		aux = rotate_right(aux);
		} else {
			aux = rotate_right_selection(aux);
		}
	} else if (abs(angle) == 180) {
		if (selected_all(*p)) {
			// rotates it twice to right by 90 degrees
			aux = rotate_right(aux);
			aux = rotate_right(aux);
		}
		else {
			// rotates the selection twice to the right by 90 degrees
			aux = rotate_right_selection(aux);
			aux = rotate_right_selection(aux);
		}
	} else if (angle == 270 || angle == -90){
		if (selected_all(*p)) {
			// rotates it 3 times to right by 90 degrees
			aux = rotate_right(aux);
			aux = rotate_right(aux);
			aux = rotate_right(aux);

		} else {
			// rotates the selection 3 times to the right by 90 degrees
			aux = rotate_right_selection(aux);
			aux = rotate_right_selection(aux);
			aux = rotate_right_selection(aux);
		}
	}

	printf("Rotated %d\n", angle);

	free_matrix(p);
	*p = aux;
}
