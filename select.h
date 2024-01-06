void select_all(image *p)
{
	p->x1 = 0;
	p->y1 = 0;
	p->x2 = p->width;
	p->y2 = p->height;
}

void select_pix(image *p, int a1, int a2, int b1, int b2)
{
    if (!p->matrix) {
        printf("No image loaded\n");
        return;
    }
    int minx = a1, maxx = a2, miny = b1, maxy = b2;
    if (a1 > a2) {
        minx = a2;
        maxx = a1;
    }
    if (b1 > b2) {
        miny = b2;
        maxy = b1;
    }
    if (a1 == a2 || b1 == b2 || minx < 0 || miny < 0 || maxx > p->width || maxy > p->height) {
        printf("Invalid set of coordinates\n");
        return;
    }
    p->x1 = minx;
    p->x2 = maxx;
    p->y1 = miny;
    p->y2 = maxy;
    printf("Selected %d %d %d %d\n", minx, miny, maxx , maxy);
}




void select_f(image *p)
{
    int a1, a2, b1, b2;
    char *buffer = (char *)malloc(sizeof(buffer) * 40);
    fgets(buffer, 40, stdin);
    char *word = strtok(buffer, "\n ");
    if (word == NULL) {
        printf("Invalid command\n");
        return;
    }
    if (!strcmp(word, "ALL")) {
        if (!p->matrix) {
                printf("No image loaded\n");
                return;
            }
        select_all(p);
        printf("Selected ALL\n");
        return;
    } else {
        if (is_number(word)) {

            a1 = atoi(word);
            word = strtok(NULL, "\n ");
            if (is_number(word)) {
                b1 = atoi(word);
                word = strtok(NULL, "\n ");

                if (is_number(word)) {
                    a2 = atoi(word);
                    word = strtok(NULL, "\n ");
                    if (is_number(word)) {
                        b2 = atoi(word);
                        word = strtok(NULL, "\n ");
                        if (word)
                            printf("Invalid command\n");
                        else 
                            select_pix(p, a1, a2, b1, b2);
                    } else {
                        printf("Invalid command\n");
                    }
                } else {
                    printf("Invalid command\n");
                }
            } else {
                printf("Invalid command\n");
            }
        } else {
            printf("Invalid command\n");
        }
    }
    free(buffer);
}


