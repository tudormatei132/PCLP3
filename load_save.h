FILE *load_file(char *p)
{
	
	FILE *f;
	f = fopen(p, "rw");

	if (f == NULL)
	{
		printf("Failed to load %s\n", p);
		return NULL;
	}
	
	return f;
}

int image_type(char *magic_word)
{
	char plain[] = "P1P2P3";

	//will return 1 for plain, 2 for binary
	if (strstr(plain, magic_word)) {
		return 1;
	}
	return 2;
	
}

int pixel_count(char *magic_word)
{
	if (strstr("P3P6", magic_word)) {
		return 3; 
	} else if (strstr("P1P2P4P5", magic_word)) {
		return 1;
	}
	return 0;
}


int is_com(char *p)
{
	if (p[0] == '#')
		return 1;
	return 0;
}

void read_plain(image p, FILE *f)
{
	//function that reads matrices from a P1, P2 or P3 file
	for (int i = 0; i < p.height; i++)
		{
			for (int j = 0; j < p.width; j++) {
				for (int k = 0; k < p.pixel_no; k++) {
					char buffer[4];
				fscanf(f, "%s", buffer);
				p.matrix[i][j].val[k] = atoi(buffer);
				}
			}
		}
}

void read_binary(image *p, FILE *f)
{
	//read the matrix from a binary file
	for (int i = 0; i < p->height; i++)
		{
			for (int j = 0; j < p->width; j++) {
				for (int k = 0; k < p->pixel_no; k++) {
				unsigned char buffer;
				fread(&buffer, 1, 1, f);
				p->matrix[i][j].val[k] = (double)buffer;
				}
			}
		}
}

void skip_com(FILE **f, char **p)
{
	while (is_com(*p)) {
		//ignore the comments
		while (!strchr(*p, '\n'))	
			fscanf(*f, "%s", *p);
		fscanf(*f, "%s", *p);
	}	
}

image load_image(FILE **f, char *name)
{
	image result;
	int scale = 0;
	char *p = (char *)malloc(sizeof(char) * 1000);
	char c;
	fscanf(*f, "%s", p);
	//start reading from the file and check for comments
	skip_com(f, &p);
	result.type = image_type(p);
	result.pixel_no = pixel_count(p);
	result.scale = -1;
	
	if (strstr("P2 P3 P5 P6", p)) {
		scale = 1;//checks whether the file has a number containing
		//the scale as well
	}
	fscanf(*f, "%s", p);
	skip_com(f, &p);
	//move the file pointer backwards in order to read the number as an int
	//type, and not as a string
	fseek(*f, strlen(p) * (-1), SEEK_CUR);	
	fscanf(*f, "%d %d\n", &result.width, &result.height);
	fscanf(*f, "%s", p);
	skip_com(f, &p);

	fseek(*f, strlen(p) * (-1), SEEK_CUR);	
	if (scale > 0) {
	fscanf(*f, "%d", &result.scale);
	fread(&c, 1, 1, *f);
	fseek(*f, -1, SEEK_CUR);
	if (c == '#') {
	fscanf(*f, "%s", p);
	skip_com(f, &p);
		fseek(*f, strlen(p) * (-1), SEEK_CUR);
	}
	}	
	
	select_all(&result);
	result = alloc_matrix(result);
	if (result.type == 1)
	{

		//continue reading
		if (!result.matrix) {
		printf("Failed to load %s\n", name);
		return result;
	}
		read_plain(result, *f);
		free(p);
		printf("Loaded %s\n", name);
		return result;
		
	} else if (result.type == 2)
	{
		//reload file as a binary 
		if (!result.matrix) {
		printf("Failed to load %s\n", name);
		return result;
	}
		int c2 = ftell(*f);
		fclose(*f);
		*f = fopen(name, "rb");
		fseek(*f, c2 + 1, SEEK_SET);
		/*moves the file cursor pointer back to where it stopped
		reading plain text*/
		read_binary(&result, *f);
		free(p);
		printf("Loaded %s\n", name);
		return result;
	}
	free(p);
	return result;
}

void write_ascii(FILE *f, image p)
{
	unsigned char buffer;
	for (int i = 0; i < p.height; i++) {
		for (int j = 0; j < p.width; j++) {
			for (int k = 0; k < p.pixel_no; k++) {
				buffer = (unsigned char)(round(p.matrix[i][j].val[k]));
				fprintf(f, "%d ", buffer);
			}
		}
		fprintf(f, "\n");
	}
}

void write_binary(FILE *f, image p)
{
	unsigned char buffer;
	for (int i = 0; i < p.height; i++) {
		for (int j = 0; j < p.width; j++) {
			for (int k = 0; k < p.pixel_no; k++) {
				buffer = (unsigned char)(round(p.matrix[i][j].val[k]));
				fwrite(&buffer, sizeof(unsigned char), 1, f);
			}
		}
	}
}

char *reverse_type(int type, int pixel_no, int scale)
{
	char *type_r = malloc(sizeof(char) * 4);
	if (pixel_no == 3) {
		if (type == 1) {
			strcpy(type_r, "P3");
			return type_r;
		}
		else {
			strcpy(type_r, "P6");
			return type_r;
		}
	}
	if (pixel_no == 1) {
		if (scale >= 0) {
			if (type == 1) {
			strcpy(type_r, "P2");
				return type_r;
			}
			else {
			strcpy(type_r, "P5");
				return type_r;
			}
				
		}
		if (scale < 0) {
			if (type == 1) {
			strcpy(type_r, "P1");
				return type_r;
			}
			
			else {
			strcpy(type_r, "P4");
				return type_r;
			}
				
		}
	}
	return NULL;
}


void save(image p, char *name)
{
	int type = 2;
	char ascii[10];
	fgets(ascii, 10, stdin);
	if (!p.matrix) {
		printf("No image loaded\n");
		return;
	}
	
	FILE *f = fopen(name, "w");
	if (!strcmp(ascii, " ascii\n")) {
		type = 1;
	}
	char *type_r = reverse_type(type, p.pixel_no, p.scale);
	fprintf(f, "%s\n", type_r);
	
	free(type_r);
	fprintf(f, "%d %d\n", p.width, p.height);
	if (p.scale >= 0)
		fprintf(f, "%d\n", p.scale);
	if (!strcmp(ascii, " ascii\n")) {
		//continue writing into the file
		write_ascii(f, p);
		fclose(f);
		printf("Saved %s\n", name);
		return;
	}
	
		//"ab" permission is given to continue the writing, without
		//losing the plain text already written
		fclose(f);
		f = fopen(name, "ab");
		write_binary(f, p);
		fclose(f);
		printf("Saved %s\n", name);
		return;
}

