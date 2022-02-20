#include <stdio.h>

/**
 * Returns the determinant of a 2x2 square matrix:
 * [ a b ]
 * [ c d ]
 */
int determinant(int a, int b, int c, int d) {
    int first = a * b;
    int second = c * d;
    return first - second;
}

/**
 * Creates matrix:
 *
 * [5  4]
 * [3  5]
 *
 * and computes the determinant.
 */
int main() {
    int a = 5;
    int b = 4;
    int c = 3;
    int d = 5;

    printf("Matrix:\n%d %d\n%d %d", a, b, c, d);
    printf("\n\nComputed Determinant: %d", determinant(a, b, c, d));
    printf("\nActual Determinant:   13\n");

    return 0;
}

