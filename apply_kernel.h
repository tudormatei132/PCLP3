
double cal_sum(image p, double kernel[3][3], int i, int j, int k, double con)
{
    double sum = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
           sum = sum + p.matrix[i - 1 + x][j - 1 + y].val[k] * kernel[x][y]; 
        }
    }
    sum = sum * con;
    sum = clamp(sum);
    return sum;
}

void apply_kernel(image *p, double kernel[3][3], double con)
{
    image aux;
    int a1 = 0, a2 = 0, b1 = 0 ,b2 = 0;
    copy_image(*p, &aux);
    if (p->x1 == 0) {
        a1 = 1;
    }
    if (p->x2 == p->width) {
        a2 = 1;
    }
    if (p->y1 == 0) {
        b1 = 1;
    }
    if (p->y2 == p->height) {
        b2 = 1;
    }
    for (int i = p->y1 + b1; i < p->y2 - b2 ; i++) {
        for (int j = p->x1 + a1; j < p->x2 - a2; j++) {
            for (int k = 0; k < p->pixel_no; k++) {
                p->matrix[i][j].val[k] = cal_sum(aux, kernel, i, j, k, con);
                p->matrix[i][j].val[k] = round(p->matrix[i][j].val[k]);
            }
        }
    }
    free_matrix(&aux);
}


void apply(image *p)
{
    char *type = (char *)malloc(sizeof(char) * 20);
    if(!type) {
        printf("malloc() failed");
        return;
    }
    fgets(type, 20, stdin);
    if (!p->matrix) {
        printf("No image loaded\n");
        free(type);
        return;
    }
     if (!strcmp(type, "\n")) {
        printf("Invalid command\n");
        free(type);
        return;
    }
    if (p->pixel_no != 3) {
        printf("Easy, Charlie Chaplin\n");
        free(type);
        return;
    }
   
    double con = 1.;
    r_trail_whites(type);
    if (!strcmp(type, " EDGE")) {
        double kernel[3][3] = {{-1, -1 ,-1}, {-1, 8, -1}, {-1, -1, -1}};
        apply_kernel(p, kernel, con);
        printf("APPLY%s done\n", type);
        free(type);
        return;
    }
    if (!strcmp(type, " SHARPEN")) {
        double kernel[3][3] = {{0, -1 ,0}, {-1, 5, -1}, {0, -1, 0}};
        apply_kernel(p, kernel, con);
        printf("APPLY%s done\n", type);
        free(type);
        return;
    }
    if (!strcmp(type, " BLUR")) {
        double kernel[3][3] = {{1, 1 , 1}, {1, 1, 1}, {1, 1, 1}};
        con = 1./9;
        apply_kernel(p, kernel, con);
        printf("APPLY%s done\n", type);
        free(type);
        return;
    }
    if (!strcmp(type, " GAUSSIAN_BLUR")) {
        double kernel[3][3] = {{1, 2 , 1}, {2, 4, 2}, {1, 2, 1}};
        con = 1./16;
        apply_kernel(p, kernel, con);
        printf("APPLY%s done\n", type);        
        free(type);
        return;
    }
    printf("APPLY parameter invalid\n");
    free(type);
    return;
}



