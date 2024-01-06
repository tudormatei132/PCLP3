image equalize(image *p)
{
    if (!p->matrix) {
        printf("No image loaded\n");
        return *p;
    }
    if (p->pixel_no == 3) {
        printf("Black and white image needed\n");
        return *p;
    }
    image result;
    copy_size(*p, &result);
    result = alloc_matrix(result);
    if (!result.matrix) {
        printf("malloc failed()");
        return *p;
    }

    int *fr = (int *)malloc(sizeof(int) * 256);
    if (!fr) {
        printf("malloc failed()");
        return *p;
    }

    for (int i = 0; i < 256; i++)
        fr[i] = 0;

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
            result.matrix[i][j].val[0] = 255./(p->width * p->height) * sum;
        }
    }
    free(fr);
    free_matrix(p);
    printf("Equalize done\n");
    
    return result;
}
