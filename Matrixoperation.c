#include <stdio.h>

#define MAX 10

// Function to read a matrix from user input
void readMatrix(int mat[MAX][MAX], int rows, int cols, const char *name) {
    printf("Enter elements of matrix %s (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}

// Function to print a matrix
void printMatrix(int mat[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

// Function to add two matrices of the same size
void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

// Function to multiply two matrices (a: r1 x c1, b: r2 x c2, requires c1 == r2)
void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX],
                       int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Function to compute the transpose of a matrix
void transposeMatrix(int mat[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = mat[i][j];
        }
    }
}

int main() {
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];
    int r1, c1, r2, c2;
    int choice;

    printf("=== Matrix Operations ===\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter rows and columns for both matrices: ");
            scanf("%d %d", &r1, &c1);
            r2 = r1;
            c2 = c1;

            readMatrix(a, r1, c1, "A");
            readMatrix(b, r2, c2, "B");

            addMatrices(a, b, result, r1, c1);

            printf("\nMatrix A:\n");
            printMatrix(a, r1, c1);
            printf("\nMatrix B:\n");
            printMatrix(b, r2, c2);
            printf("\nSum (A + B):\n");
            printMatrix(result, r1, c1);
            break;

        case 2:
            printf("Enter rows and columns of matrix A: ");
            scanf("%d %d", &r1, &c1);
            printf("Enter rows and columns of matrix B: ");
            scanf("%d %d", &r2, &c2);

            if (c1 != r2) {
                printf("Error: Number of columns of A must equal number of rows of B.\n");
                break;
            }

            readMatrix(a, r1, c1, "A");
            readMatrix(b, r2, c2, "B");

            multiplyMatrices(a, b, result, r1, c1, c2);

            printf("\nMatrix A:\n");
            printMatrix(a, r1, c1);
            printf("\nMatrix B:\n");
            printMatrix(b, r2, c2);
            printf("\nProduct (A x B):\n");
            printMatrix(result, r1, c2);
            break;

        case 3:
            printf("Enter rows and columns of matrix A: ");
            scanf("%d %d", &r1, &c1);

            readMatrix(a, r1, c1, "A");
            transposeMatrix(a, result, r1, c1);

            printf("\nMatrix A:\n");
            printMatrix(a, r1, c1);
            printf("\nTranspose of A:\n");
            printMatrix(result, c1, r1);
            break;

        default:
            printf("Error: Invalid choice.\n");
    }

    return 0;
}