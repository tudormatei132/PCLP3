void r_trail_whites(char *p)
{
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] == '\n') {
			p[i] = '\0';
			return;
		}
	}
}

int selected_all(image p)
{
	if (p.x1 != 0) {
		return 0;
	}
	if (p.x2 != p.width ) {
		return 0;
	}
	if (p.y1 != 0) {
		return 0;
	}
	if (p.y2 != p.height ) {
		return 0;
	}
	return 1;
}

int is_number(char *text)
{
	if (text == NULL) {
		return 0;
	}
	for (int i = 0; text[i] != '\0'; i++) {
		if (!isdigit(text[i])) {
			if (i != 0)
				return 0;
			else {
				if (text[i] != '-')
					return 0;
			}
		}
	}
	return 1;
}

void print_matrix(image p)
{
	for (int i = 0; i < p.height; i++) {
		for (int j = 0; j < p.width; j++) {
			for (int k = 0; k < p.pixel_no; k++) {
				printf("%lf ", p.matrix[i][j].val[k]);
			}
		}
		printf("\n");
	}
}

void copy_size(image source, image *dest)
{
	dest->x1 = source.x1;
	dest->x2 = source.x2;
	dest->y1 = source.y1;
	dest->y2 = source.y2;
	dest->width = source.width;
	dest->height = source.height;
	dest->pixel_no = source.pixel_no;
	dest->type = source.type;
	dest->scale = source.scale;
}

void copy_image(image source, image *dest)
{
	copy_size(source, dest);
	*dest = alloc_matrix(*dest);
	for (int i = 0; i < source.height; i++) {
		for (int j = 0; j < source.width; j++) {
			for (int k = 0; k < source.pixel_no; k++) {
				dest->matrix[i][j].val[k] = source.matrix[i][j].val[k];
			}
		}
	}
}

double clamp(double val)
{
	if (val > 255)
		return 255;
	if (val < 0)
		return 0;
	return val;
}

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

void swap_d(double *a, double *b)
{
	double temp = *a;
	*a = *b;
	*b = temp;
}
