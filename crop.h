void crop(image *p)
{
    if (!p->matrix) {
        printf("No image loaded\n");
        return;
    }

    if (selected_all(*p))
        return;

    image cropped;
    cropped.width = p->x2 - p->x1 + 1;
    cropped.height = p->y2 - p->y1 + 1;
    cropped.matrix = (pixel **)malloc(sizeof(pixel *) * cropped.height);
    if (!cropped.matrix) {
        printf("malloc() failed in crop");
    }
    for (int i = 0; i < cropped.height; i++) {
        cropped.matrix[i] = (pixel *)malloc(sizeof(pixel) * cropped.width);
        if (!cropped.matrix[i]) {
                    printf("malloc() failed in crop");
        }
        for (int j = 0; j < cropped.width; j++) {
            cropped.matrix[i][j].val = (double *)malloc(sizeof(double) * cropped.pixel_no);
            if (!cropped.matrix[i][j].val) {
                        printf("malloc() failed in crop");
            }
        }
    }
    copy_size(*p, &cropped);
    cropped.width = p->x2 - p->x1 + 1;
    cropped.height = p->y2 - p->y1 + 1;
    cropped.pixel_no = p->pixel_no;
    int x1 = p->x1, y1 = p->y1;
    for (int i = 0; i < cropped.height; i++) {
        for (int j = 0; j < cropped.width; j++) {
            for (int k = 0; k < cropped.pixel_no; k++) {
                cropped.matrix[i][j].val[k] = p->matrix[y1 + i][x1 + j].val[k];
            }
        }
    }
    select_all(&cropped);
    free_matrix(*p);
    *p = cropped;
    
    printf("Image cropped\n");
}