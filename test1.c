#include <stdio.h>

void rotateMatrix90Right(int rows, int cols, int matrix[rows][cols]) {
    int temp[cols][rows];

    // Rotate by 90 degrees
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp[j][rows - i - 1] = matrix[i][j];
        }
    }

    // Copy the rotated values back to the original matrix
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows = 3;
    int cols = 4;

    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printf("Original Matrix:\n");
    printMatrix(rows, cols, matrix);

    // Rotate by 90 degrees twice
    rotateMatrix90Right(rows, cols, matrix);
    rotateMatrix90Right(rows, cols, matrix);

    printf("\nMatrix after 180 degrees rotation to the right:\n");
    printMatrix(rows, cols, matrix);

    return 0;
}
