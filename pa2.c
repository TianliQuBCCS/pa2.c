/* 
 * Author: Oliver Hazard and Tianli Qu
 * PA2 Central Limit Theorem
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SAMPLES 10000
#define RUNS 50000
#define BINS 64
#define HISTOGRAM_SPAN 0.05
#define SCALE 32

double get_mean_of_uniform_random_samples() {
    double sum = 0.0;
    for (int i =0; i< SAMPLES;i++) {
        sum += (((double) rand() / RAND_MAX) * 2.0 - 1.0);
    }
    return sum / SAMPLES;
}

double populate_values_and_get_mean(double * values) {
    double sum = 0.0;
    for (int i = 0; i < RUNS; i++) {
        values[i] = get_mean_of_uniform_random_samples();
        sum += values[i];
    }    
    return sum / RUNS;
}

double get_mean_squared_error(double * values, double mean) {
    double sum_squared_error = 0.0;
    for (int i = 0; i < RUNS; i++) {
        double diff = mean - values[i];
        sum_squared_error += diff*diff;
    }
    return sum_squared_error / RUNS;
}

void create_histogram(double *values, int *counts) {
    double bin_size = HISTOGRAM_SPAN / (double)BINS;
    for (int i = 0; i < RUNS; ++i) {
        double value = values[i];
        int bin_index = (int)((value + (HISTOGRAM_SPAN / 2.0)) / bin_size);
        if (bin_index >= 0 && bin_index < BINS) {
            counts[bin_index]++;
        }
    }
}

void print_histogram(int * counts) {
    double bin_size = HISTOGRAM_SPAN / (double)BINS;
    for (int i = 0; i < BINS; ++i) {
        double bin_start = -(HISTOGRAM_SPAN / 2.0) + (i + 0.5) * bin_size;
        printf("%.4f  ", bin_start);
        for (int j = 0; j < counts[i] / SCALE; ++j) {
            printf("X");
        }                                                                           
        printf("\n");
    }
}

int main(){
    srand(time(NULL));
    
    double *values = malloc(RUNS * sizeof(double));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
            
    double mean = populate_values_and_get_mean(values);
    double mean_squared_error = get_mean_squared_error(values, mean);
    int counts[BINS] = {0}; 
    create_histogram(values, counts);
    print_histogram(counts);
                             
    free(values);
                                    
    printf("Sample mean over %d means of %d samples each: %lf   ", RUNS, SAMPLES, mean);
    printf("Sample variance: %lf\n", mean_squared_error);

    return EXIT_SUCCESS;
}

