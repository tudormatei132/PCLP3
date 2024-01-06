typedef struct {
     double *val;
} pixel;



typedef struct {
    int type;
    int pixel_no; //3 IF color photo, 1 for the other types
    int width, height;
    int scale;
    int x1, x2, y1, y2;
    pixel **matrix;
} image;

