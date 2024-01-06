
void free_matrix(image *p)
{
   
    for (int i = 0; i < p->height; i++) {
        for (int j = 0; j < p->width; j++) {
            free(p->matrix[i][j].val);
            p->matrix[i][j].val = NULL;
        }
        free(p->matrix[i]);
        p->matrix[i] = NULL;
        
    }
    free(p->matrix);
    p->matrix = NULL;
}


image alloc_matrix(image p)
{
    image result;
    result.x1 = p.x1;
    result.x2 = p.x2;
    result.y1 = p.y1;
    result.y2 = p.y2;
    result.width = p.width;
    result.height = p.height;
    result.pixel_no = p.pixel_no;
    result.type = p.type;
    result.scale = p.scale;
    result.matrix = (pixel **)malloc(sizeof(pixel *) * p.height);
    if (!result.matrix) {
                    printf("malloc() failed in alloc_matrix");
            exit(-1);
    }
    for (int i = 0; i < p.height; i++) {
        result.matrix[i] = (pixel *)malloc(sizeof(pixel) * p.width);
        if (!result.matrix[i]) {
            printf("malloc() failed in alloc_matrix");
            exit(-1);
        }
        for (int j = 0; j < p.width; j++) {
            result.matrix[i][j].val = (double *)malloc(sizeof(double) * p.pixel_no);
            if (!result.matrix[i][j].val) {
                            printf("malloc() failed in alloc_matrix");
                            exit (-1);
            }
        }
    }
    return result;
}