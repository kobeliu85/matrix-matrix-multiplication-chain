#include <iostream>
#include <sys/time.h>


#define DIM 256
#define R 10
#define RHS 128
#include "mkl.h"

// Function to compare two values for qsort
int compare(const void *a, const void *b) {
    return (*(double*)a > *(double*)b) - (*(double*)a < *(double*)b);
}

// Function to calculate the median of an array
double calculateMedian(double arr[], int n) {
    // Sort the array
    qsort(arr, n, sizeof(double), compare);

    // Calculate the median
    if (n % 2 == 0) {
        // If the number of elements is even, average the middle two elements
        return (arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
    } else {
        // If the number of elements is odd, return the middle element
        return arr[n / 2];
    }
}


int main() {

    int m1 = DIM, n1= R;
    int m2 = R, n2 = R;
    int m3 = R, n3 = DIM;
    int m4 = DIM, n4 = RHS;

    double *U = new double[m1*n1];
    double *B = new double[m2*n2];
    double *V = new double[m3*n3];
    double *W = new double[m4*n4];

    double *tmp1 = new double[m2*n3];
    double *tmp2 = new double[m2*n4];

    double *res = new double[m1*n4];

    for (int i = 0; i < m1*n1; i++) {
        U[i] = 1.0;
    }
    for (int i = 0; i < m2*n2; i++) {
        B[i] = 1.0;
    }
    for (int i = 0; i < m3*n3; i++) {
        V[i] = 1.0;
    }
    for (int i = 0; i < m4*n4; i++) {
        W[i] = 1.0;
    }

    double time_array[1000];
    struct timeval start, end;


    for(int i=0; i < 1000; i++)
    {
        gettimeofday(&start, NULL);
        // B * V first
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m2, n3, n2, 1.0, B, n2, V, n3, 0.0, tmp1, n3);


        // tmp1 * W
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m2, n4, n3, 1.0, tmp1, n3, W, n4, 0.0, tmp2, n4);

        // U * tmp2

        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m1, n4, n1, 1.0, U, n1, tmp2, n4, 0.0, res, n4);

        gettimeofday(&end, NULL);

        double exe_time = (end.tv_sec - start.tv_sec) * (1e+6)  + (end.tv_usec - start.tv_usec) ;
        printf("Execution time: %.10f\n", exe_time);
        time_array[i] = exe_time;
    }

    //    std::cout << "Median time: " << calculateMedian(time_array, 1000) << std::endl;

    printf("Median time: %.10f\n", calculateMedian(time_array, 1000));






//    std::cout << "Hello, World!" << std::endl;

    delete[] U;
    delete[] B;
    delete[] V;
    delete[] W;

    delete[] tmp1;
    delete[] tmp2;
    delete[] res;

    return 0;
}
