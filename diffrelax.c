#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PARAMS 5
#define true 1
#define false 0

typedef int boolean;

void load_data_to_array(double **, int, FILE *);

int main(int argc, char *argv[])
{
    /*
        Parameters:
        1. Name of file containing space-separated square array of doubles (char *)
        2. Array dimension (int)
        3. Number of threads (int)
        4. Precision (double), 1e-6 preferred
        5. DEBUG (char *), option to enable debugging statements

        Examples:
        $ ./diffrelax path/to/array.dat 6 16 1e-6 DEBUG
    */

    double **data_array;
    int dimension;
    int num_threads;
    double precision;
    FILE *data_file;
    int i, j;
    double **avg_array;

    /* Test and set debug mode */
    boolean debug = false;
    if (argc > NUM_PARAMS && strcmp(argv[NUM_PARAMS], "DEBUG") == 0) {
        debug = true;
    }

    if (debug) {
        printf("debug: data_file(char *)=%s\n", argv[1]);
        printf("debug: dimension(char *)=%s\n", argv[2]);
        printf("debug: num_threads(char *)=%s\n", argv[3]);
        printf("debug: precision(char *)=%s\n", argv[4]);
    }

    /* Convert arguments to appropriate types */
    dimension = atoi(argv[2]);
    num_threads = atoi(argv[3]);
    precision = atof(argv[4]);

    if (debug) {
        printf("debug: dimension(int)=%d\n", dimension);
        printf("debug: num_threads(int)=%d\n", num_threads);
        printf("debug: precision(double)=%f\n", precision);
    }

    /* Allocate memory for 2D array */
    data_array = (double **) malloc(dimension * sizeof(double *));
    if (data_array == NULL) {
        printf("error: could not allocate memory for 2D array, aborting ...\n");
        return 1;
    }
    for (i = 0; i < dimension; i++) {
        data_array[i] = (double *) malloc(dimension * sizeof(double));
        if (data_array[i] == NULL) {
            printf("error: could not allocate memory for row %d of 2D array, aborting ...\n", i);
            return 1;
        }
    }

    /* Open array file for reading */
    data_file = fopen(argv[1], "r");
    if (data_file == NULL) {
        printf("error: could not open data file, aborting ...\n");
        return 1;
    }

    /* Store data in 2D array */
    load_data_to_array(data_array, dimension, data_file);

    if (debug) {
        printf("debug(load_data_to_array):\n");
        for (i = 0; i < dimension; i++) {
            for (j = 0; j < dimension; j++) {
                printf("%f ", data_array[i][j]);
            }
            putchar('\n');
        }
    }

    /* Close file */
    fclose(data_file);

    /* Prepare 2D array for neighbour averages */
    avg_array = (double **) malloc((dimension - 2) * sizeof(double *));
    for (i = 0; i < dimension - 2; i++) {
        avg_array[i] = (double *) malloc((dimension - 2) * sizeof(double));
    }

    /* Average the four neighbours of non-boundary numbers */
    for (i = 1; i < dimension - 1; i++) {
        for (j = 1; j < dimension - 1; j++) {
            avg_array[i - 1][j - 1] = (data_array[i - 1][j] + data_array[i][j - 1]
                    + data_array[i][j + 1] + data_array[i + 1][j]) / 4.0f;
        }
    }

    if (debug) {
        printf("debug(avg_array):\n");
        for (i = 0; i < dimension - 2; i++) {
            for (j = 0; j < dimension - 2; j++) {
                printf("%f ", avg_array[i][j]);
            }
            putchar('\n');
        }
    }

    /* Deallocate memory for 2D array */
    for (i = 0; i < dimension - 2; i++) {
        free(avg_array[i]);
    }
    free(avg_array);
    for (i = 0; i < dimension; i++) {
        free(data_array[i]);
    }
    free(data_array);

    return 0;
}

void load_data_to_array(double **data_array, int dimension, FILE *data_file)
{
    int i, j;
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            fscanf(data_file, "%lf", &data_array[i][j]);
        }
        fgetc(data_file);
    }
}
