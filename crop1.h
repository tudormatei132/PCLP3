image crop(image *p)
{
    if (!p->matrix) {
        printf("No image loaded\n");
        return *p;
    }

    if(selected_all(*p)) {
        printf("Image cropped\n");
        return *p;
    }
    image result;
    copy_size(*p, &result);
    result.width = p->x2 - p->x1;
    result.height = p->y2 - p->y1;
    result.pixel_no = p->pixel_no;
    result = alloc_matrix(result);

    for (int i = 0; i < result.height; i++) {
        for (int j = 0; j < result.width; j++) {
            for (int k = 0; k < result.pixel_no; k++) {
                result.matrix[i][j].val[k] = p->matrix[p->y1 + i][p->x1 + j].val[k];
            }
        }
    }

    select_all(&result);
    free_matrix(p);
    printf("Image cropped\n");
    return result;
}