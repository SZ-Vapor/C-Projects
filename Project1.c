#include <stdio.h>
#include <stdlib.h>

/**
 * Steven Hogenson
 * COSC450 Project 1
 * 11/5/2018
 *
 * This program will read in integers from a text file (amount MUST be divisible by 10) and sort the integers into two
 * matrices. These matrices are then multiplied together. The original matrices and the product are written to an output
 * text file. The product matrix gets sorted and this sorted matrix is written to the output file also.
 */




/**
 * Finds the number of integers present in the input file
 * @param inputFile The file to count ints from
 * @return The number of individual integers in the file
 */
int getNumberOfInts(char *inputFile) {
    int array[100000];//placeholder number
    FILE *file = fopen(inputFile, "r");
    int count = 0;
    while (count < sizeof(array) / sizeof(array[0]) && fscanf(file, "%d", &array[count]) == 1)//increments count for every integer in the text file
        count++;
    fclose(file);
    return count;
}

/**
 * Makes a new matrix that is the product of two matrices
 * @param numInts Number of ints form input file divided by 5. Have this many rows and columns
 * @param matrix1 First matrix to multiply by
 * @param matrix2 Second matrix to multiply by
 * @return Matrix that is the product of matrix1 and matrix 2
 */
long **multiplyMatrices(int numInts, long **matrix1, long **matrix2) {
    long entrySum = 0;

    long **matrixProduct = malloc(5 * sizeof(*matrixProduct));
    for (int i = 0; i < 5; i++) {
        matrixProduct[i] = malloc(5 * sizeof(*matrixProduct[i]));
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < numInts; k++) {
                entrySum += matrix1[i][k] * matrix2[k][j];
            }
            matrixProduct[i][j] = entrySum;
            entrySum = 0;
        }
    }
    return matrixProduct;
}

/**
 * Creates the first matrix
 * @param inputFile The file to read in from
 * @param numInts The number of integers in the file divided by 5. Have this many columns
 * @return A 5*X matrix
 */
long **makeMatrix1(char *inputFile, int numInts) {
    FILE *inputF = fopen(inputFile, "r");
    long **matrix = malloc(5 * sizeof(*matrix));
    for (int i = 0; i < 5; i++) {
        matrix[i] = malloc(numInts * sizeof(*matrix[i]));
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < numInts; j++) {
            fscanf(inputF, "%ld", &matrix[i][j]);
        }
    }
    fclose(inputF);
    return matrix;
}

/**
 * Creates the second matrix
 * @param inputFile The file to read in from
 * @param numInts The number of integers in the file divided by 5. Have this many rows
 * @return An X*5 matrix
 */
long **makeMatrix2(char *inputFile, int numInts) {
    FILE *inputF = fopen(inputFile, "r");
    long **matrix = malloc(numInts * sizeof(*matrix));
    for (int i = 0; i < numInts; i++) {
        matrix[i] = malloc(5 * sizeof(*matrix[i]));
    }

    for (int i = 0; i < numInts; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(inputF, "%ld", &matrix[i][j]);
        }
    }
    fclose(inputF);
    return matrix;
}

/**
 * Writes or appends a mtrix to the designated output file
 * @param outputFile The file to write or append to
 * @param write_orAppend Check if need to write or append
 * @param rows Number of rows in the matrix
 * @param columns Number of columns in the matrix
 * @param matrix The matrix to write
 * @param title The Matrix's name (ie. 'Matrix 1')
 * @return None
 */
writeMatrix(const char *outputFile, char *write_orAppend, int rows, int columns, long **matrix, char *title) {

    FILE *myOutputF = fopen(outputFile, write_orAppend);
    fprintf(myOutputF, "\n%s%s\n", title, ":");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(myOutputF, "%ld ", matrix[i][j]);
        }
        fprintf(myOutputF, "\n");
    }
    fclose(myOutputF);
}

/**
 * Uses bubble sort to sort the product matrix
 * @param matrix Matrix that is to be sorted
 */
void sortMatrix(long **matrix) {
    long temp;
    int currentRow;
    int currentColumn;
    int currentRow_orNextRow;
    int nextColumn;

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < (25 - 1); j++) {
            currentRow = j / 5;
            currentColumn = j % 5;
            currentRow_orNextRow = (j + 1) / 5;
            nextColumn = (j + 1) % 5;

            if (matrix[currentRow][currentColumn] > matrix[currentRow_orNextRow][nextColumn]) {
                temp = matrix[currentRow][currentColumn];
                matrix[currentRow][currentColumn] = matrix[currentRow_orNextRow][nextColumn];
                matrix[currentRow_orNextRow][nextColumn] = temp;
            }
        }
    }
}

int main(int argc, char **argv) {

    const char *inputFile = "COSC450_P1_Input.txt";
    const char *outputFile = "COSC450_P1_Output.txt";
    int numInts = getNumberOfInts(inputFile) / 5;

    long **matrix1 = makeMatrix1(inputFile, numInts);
    long **matrix2 = makeMatrix2(inputFile, numInts);
    long **matrixProduct = multiplyMatrices(numInts, matrix1, matrix2);
    writeMatrix(outputFile, "w", 5, numInts, matrix1, "Matrix 1");
    writeMatrix(outputFile, "a", numInts, 5, matrix2, "Matrix 2");
    writeMatrix(outputFile, "a", 5, 5, matrixProduct, "Matrix Product");
    sortMatrix(matrixProduct);
    writeMatrix(outputFile, "a", 5, 5, matrixProduct, "Matrix Product Sorted");
    return 0;
}
