#include <stdio.h>

struct Matrix2 {
    double rows[2][2];
};

/**
 * Returns the determinant of a 2x2 square matrix
 * @param matrix : The matrix to compute with
 * @return : The determinant
 */
double determinant(struct Matrix2 matrix) {
    double first = matrix.rows[0][0] * matrix.rows[1][1];
    double second = matrix.rows[0][1] * matrix.rows[1][0];
    return first - second;
}

int main() {
    struct Matrix2 broken;
    double top[] = {5, 0.1};
    double bottom[] = {3, 5};

    printf("Hello, World!\n");
    return 0;
}

