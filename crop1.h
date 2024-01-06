image crop(image *p)
{
	if (!p->matrix) {
		printf("No image loaded\n");
		return *p;
	}
	// return the original image if trying to crop the whole one
	if(selected_all(*p)) {
		printf("Image cropped\n");
		return *p;
	}

	image result;
	copy_size(*p, &result);
	// modify the size of the new image and alloc'ing it
	result.width = p->x2 - p->x1;
	result.height = p->y2 - p->y1;
	result = alloc_matrix(result);

	for (int i = 0; i < result.height; i++) {
		for (int j = 0; j < result.width; j++) {
			for (int k = 0; k < result.pixel_no; k++) {
				//get the selected part into the new matrix
				result.matrix[i][j].val[k] = p->matrix[p->y1 + i][p->x1 + j].val[k];
			}
		}
	}

	select_all(&result);
	free_matrix(p);// free our old image
	printf("Image cropped\n");
	return result;
}
