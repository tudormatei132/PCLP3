// checks if a given number is a power of 2
int is_power(int n)
{
	while (n % 2 == 0) {
		n = n / 2;
	}
	if (n == 1)
		return 1;
	return 0;
}

int get_command(char *command, int *x, int *y)
{
	// get the parameters
	// return 1 if exactly 2 parameters are given
	// and -1 if there are too many or less than needed
	fgets(command, 30, stdin);
	char *word = strtok(command, "\n ");
	if (is_number(word)) {
		*x = atoi(word);
		word = strtok(NULL, "\n ");
		if (is_number(word)) {
			*y = atoi(word);
			word = strtok(NULL, "\n ");
			if (word) {
				return -1;
			} else {
				return 1;
			}
		} else {
			return -1;
		}
	}

	return -1;

}

void print_histogram(image p)
{

	int x, y;
	char *buffer = (char *)malloc(sizeof(char) * 30);
	int res = get_command(buffer, &x, &y);
	free(buffer);
	 if (!p.matrix) {
		printf("No image loaded\n");
		return;
	}

	if (res == -1) { // check if the pattern is matched by the given command
		printf("Invalid command\n");
		return;
	}

	if (p.pixel_no == 3) { // check if the image uses colors
		printf("Black and white image needed\n");
		return;
	}
	if (y <= 256 && y > 1) {
		if (!is_power(y))
			printf("Invalid set of parameters\n");

	} else {
		printf("Invalid set of parameters\n");

	}
	int fr[256];
	for (int i = 0; i < 256; i++)
		fr[i] = 0;
	// get how many times each possible value appears in the image's matrix
	for (int i = 0; i < p.height; i++) {
		for (int j = 0; j < p.width; j++) {
			fr[(int)p.matrix[i][j].val[0]]++;
		}
	}

	int *bins = (int *)malloc(sizeof(int) * (y));
	if (!bins) {
		printf("malloc() failed!");
		return;
	}
	for (int i = 0; i < y; i++) {
		bins[i] = 0;
	}
	int max = -1;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < 256 / y; j++) {
			// we divide the frequency array into y bins with
			// 256 / y elements each
			bins[i] += fr[i * 256 / y + j];//get the sum for each bin
		}
		if (bins[i] > max) {
			max = bins[i];
		}
	}



	for (int i = 0; i < y; i++) {
		double ratio = (double)bins[i] / max * x;//get the number of stars needed
		int stars_no = (int)ratio;
		printf("%d  |   ",stars_no);
		//print the corresponding number of stars for each bin
		for (int j = 0; j < stars_no; j++)
			printf("*");
		printf("\n");
	}
	free(bins);

}
