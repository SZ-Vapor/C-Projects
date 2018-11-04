#include <stdio.h>
#include <stdlib.h>

/**
 *
 * @param inputFile The file to count ints from
 * @return The number of individual integers in the file
 */
int getNumberOfInts(char *inputFile) {
    int array[100000];
    FILE *file = fopen(inputFile, "r");
    int count = 0;
    while (count < sizeof(array) / sizeof(array[0]) && fscanf(file, "%d", &array[count]) == 1)
        count++;
    fclose(file);
    return count;
}

/**
 *
 * @param inner
 * @param matrix1
 * @param matrix2
 * @param matrix_Prod
 */
void multiplyMatrices(int inner, long **matrix1, long **matrix2, long **matrixProduct) {
    long entrySum = 0;

    /*long **matrix_Prod = malloc(5 * sizeof(*matrix_Prod));
    for (int i = 0; i < 5; i++) {
        matrix_Prod[i] = malloc(5 * sizeof(*matrix_Prod[i]));
    }*/
    
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < inner; k++) {
                entrySum += matrix1[i][k] * matrix2[k][j];
            }
            matrixProduct[i][j] = entrySum;
            entrySum = 0;
        }
    }
}

void createMatrix(const char *inputFile, int inner, long **matrix1, long **matrix2, long **matrixProduct) {

    //used to index arrays
    int i;
    int j;

    FILE *myInputF = fopen(inputFile, "r");
    FILE *myInputF2 = fopen(inputFile, "r");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < inner; j++) {
            fscanf(myInputF, "%ld", &matrix1[i][j]);
        }
    }
    for (i = 0; i < inner; i++) {
        for (j = 0; j < 5; j++) {
            fscanf(myInputF2, "%ld", &matrix2[i][j]);
        }
    }
    fclose(myInputF);

    multiplyMatrices(inner, matrix1, matrix2, matrixProduct);


}

/**
 *
 * @param outputFile The file to write the matrix output to
 * @param mode Check if Write or Append the matrix
 * @param rows
 * @param cols
 * @param matrix Which matrix to write to output
 * @param title Matrix's name
 * @return none
 */
writeMatrix(const char *outputFile, char *mode, int rows, int cols, long **matrix, char *title) {

    FILE *myOutputF = fopen(outputFile, mode);

    int i, j;

    fprintf(myOutputF, "\n%s%s\n", title, ":");
    //printf("\n%s%s\n",title,":");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {

            fprintf(myOutputF, "%ld ", matrix[i][j]);
            //printf("%ld ", matrix[i][j]);
        }
        fprintf(myOutputF, "\n");
        //printf("\n");
    }

    fclose(myOutputF);
}


int main(int argc, char **argv) {

    // different modes for writing to file
    const char *write_to = "w";
    const char *append_to = "a";
    //files to read and write to
    const char *input_file = "test2.txt";
    //const char *input_file = "COSC450_P1_Data.txt";
    const char *output_file = "COSC450_P1_Output.txt";

    int numInts = getNumberOfInts(input_file) / 5;

    long **matrix1 = malloc(5 * sizeof(*matrix1));
    for (int i = 0; i < 5; i++) {
        matrix1[i] = malloc(numInts * sizeof(*matrix1[i]));
    }

    long **matrix2 = malloc(numInts * sizeof(*matrix2));
    for (int i = 0; i < numInts; i++) {
        matrix2[i] = malloc(5 * sizeof(*matrix2[i]));
    }

    long **matrix_Prod = malloc(5 * sizeof(*matrix_Prod));
    for (int i = 0; i < 5; i++) {
        matrix_Prod[i] = malloc(5 * sizeof(*matrix_Prod[i]));
    }


    createMatrix(input_file, numInts, matrix1, matrix2, matrix_Prod);

    //writes matrix to file
    writeMatrix(output_file, "w", 5, numInts, matrix1, "Matrix 1");
    writeMatrix(output_file, "a", numInts, 5, matrix2, "Matrix 2");
    writeMatrix(output_file, "a", 5, 5, matrix_Prod, "Matrix Product");


    return 0;
}





