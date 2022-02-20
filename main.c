#include <stdio.h>

/**
 * Returns the determinant of a 2x2 square matrix:
 * [ a b ]
 * [ c d ]
 */
double determinant(double a, double b, double c, double d) {
    return a * d - b * c;
}

int main() {
    /**
     * Create matrix:
     * [5  0.1]
     * [3  5]
     */
    double a = 5;
    double b = 0.1;
    double c = 3;
    double d = 5;


    printf("Matrix:\n%f %f\n%f %f", a, b, c, d);
    printf("\n\nDeterminant: %f", determinant(a, b, c, d));

    return 0;
}

