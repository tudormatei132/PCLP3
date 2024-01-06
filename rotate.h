
image rotate_right(image p)
{
    //rotates the given image once to the left
    //basically, transposes the matrix of the image
    image result;
    copy_size(p, &result);
    result.height = p.width;
    result.width = p.height;
    result = alloc_matrix(result);
    for (int i = 0; i < result.height; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < result.pixel_no; k++) {
                result.matrix[i][j].val[k] = p.matrix[p.width - j - 1][i].val[k];
            }
        }
    }
        
    select_all(&result);
    free_matrix(&p);
    return result;  
}

image flip(image p)
{
    //flips the given image
    image result;
    copy_size(p, &result);
    result = alloc_matrix(result);
    int n = result.height, m = result.width;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < result.pixel_no; k++) {
                result.matrix[i][j].val[k] = p.matrix[n - i - 1][m - j - 1].val[k];
            }
        }
    }
    
    select_all(&result);

    free_matrix(&p);
    return result;  
}

int get_angle(char *command, int *angle)
{
    fgets(command, 30, stdin);
    char *word = strtok(command, "\n ");
    if (is_number(word)) {
        *angle = atoi(word);
        word = strtok(NULL, "\n ");
        if (word) {
            return -1;
        } 
        return 1;
    } else {
        return -1;
    }
}

void rotate_left_selection(image p)
{
    int n = p.x2 - p.x1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < p.pixel_no; k++)
                swap_d(&p.matrix[i + p.y1][j + p.x1].val[k], &p.matrix[j + p.y1][i + p.x1].val[k]);
        }
    }
}

void rotate_right_selection(image p)
{
 
    int n = p.x2 - p.x1;
    rotate_left_selection(p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < p.pixel_no; k++)
                swap_d(&p.matrix[i + p.y1][j + p.x1].val[k], &p.matrix[j + p.y1][i + p.x1].val[k]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            for (int k = 0; k < p.pixel_no; k++)
                swap_d(&p.matrix[i + p.y1][j + p.x1].val[k], &p.matrix[i + p.y1][n - j - 1 + p.x1].val[k]);
        }
    }
}

void flip_selection(image p)
{
    int n = p.x2 - p.x1;   
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < p.pixel_no; k++)
                swap_d(&p.matrix[i + p.y1][j + p.x1].val[k], &p.matrix[n - i - 1 + p.y1][n - j - 1 + p.x1].val[k]);
        }
    }
    if (n % 2 == 1) {
        for (int i = 0; i < n / 2; i++) {
            for (int k = 0; k < p.pixel_no; k++)
                swap_d(&p.matrix[p.y1 + n / 2][i + p.x1].val[k], &p.matrix[p.y1 + n / 2][n - i - 1 + p.x1].val[k]);
        }
    }
}






void rotate(image *p)
{
    char *command = (char *)malloc(sizeof(char) * 30);
    int angle;
    int valid = get_angle(command, &angle);
    free(command);
    if (!p->matrix){
        printf("No image loaded\n");
        return;
    }
    if (!selected_all(*p)) {
        if (p->x2 - p->x1 != p->y2 - p->y1) {
            printf("The selection must be square\n");
            return;
        }
    }
    
    if (valid == -1) {
        printf("Invalid command\n");
        return;
    }

    if (abs(angle) > 360 || angle % 90 != 0) {
        printf("Unsupported rotation angle\n");
        return;
    }
    image aux;
    copy_image(*p, &aux);
    if (angle == 90 || angle == -270) {
        if (selected_all(*p)) {
        aux = rotate_right(aux);
        } else {
            rotate_right_selection(aux);
        }
    } else if (abs(angle) == 180) {
        if (selected_all(*p)) {
            aux = rotate_right(aux);
            aux = rotate_right(aux);
        }
        else {
            rotate_right_selection(aux);
            rotate_right_selection(aux);
        }
    } else if (angle == 270 || angle == -90){
        if (selected_all(*p)) {
            aux = rotate_right(aux);
            aux = rotate_right(aux);
            aux = rotate_right(aux);
            
        } else {
            rotate_right_selection(aux);
            rotate_right_selection(aux);
            rotate_right_selection(aux);
        }
    }
    
    printf("Rotated %d\n", angle);

    free_matrix(p);
    *p = aux;
}

