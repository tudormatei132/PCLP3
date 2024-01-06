image equalize(image *p)
{
	if (!p->matrix) {
		printf("No image loaded\n");
		return *p;
	}
	// make no changes if the image has color
	if (p->pixel_no == 3) {
		printf("Black and white image needed\n");
		return *p;
	}

	image result;
	// copying the size and other information about the old image into the new
	// one and alloc'ing it
	copy_size(*p, &result);
	result = alloc_matrix(result);
	if (!result.matrix) {
		printf("malloc failed()");
		return *p;
	}


	int *fr = (int *)malloc(sizeof(int) * 256);
	// frequency array that will store the amount of times a value is
	// encountered in the pixel matrix
	if (!fr) {
		printf("malloc failed()");
		return *p;
	}

	for (int i = 0; i < 256; i++)
		fr[i] = 0;
	// we will check only for the first element of the array 'val'
	// because the image has no color
	for (int i = 0; i < p->height; i++) {
		for (int j = 0; j < p->width; j++) {
			fr[(int)p->matrix[i][j].val[0]]++;
		}
	}

	for (int i = 0; i < p->height; i++) {
		for (int j = 0; j < p->width; j++) {
			int sum = 0;
			for (int k = 0; k <= p->matrix[i][j].val[0]; k++) {
				sum += fr[k];
			}
			//get the new value for every pixel
			result.matrix[i][j].val[0] = 255./(p->width * p->height) * sum;
		}
	}
	free(fr);
	free_matrix(p);
	printf("Equalize done\n");

	return result;
}
