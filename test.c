#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void rotate_left_selection(int **p, int x2, int x1, int y2, int y1)
{
    int n = x2 - x1;
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < i; j++) {
                swap(&p[i][j], &p[j][i]);
        }
    }
}


void flip_selection(int **p, int x2, int x1, int y2, int y1)
{
    int n = x2 - x1;   
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
                swap(&p[i + x1][j + y1], &p[n - i + x1 - 1][n - j + y1 - 1]);
        }
    }
}

int rotate_right_selection(int **p, int x2, int x1, int y2, int y1)
{
    int n = x2 - x1;
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n / 2; j++) {
                swap(&p[i + x1][j + y1], &p[i + x1][n - j - 1 + y1]);
        }
    }
}


int main()
{
    int m, n;
    scanf("%d %d", &n, &m);
    int x1, x2, y1, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    int **p = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        p[i] = malloc(sizeof(int) * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[i][j]);
        }
    }
    
    rotate_right_selection(p, x2, x1, y2, y1);
    rotate_right_selection(p, x2, x1, y2, y1);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
}