#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

int main() {
    int n;
    printf("Enter the dimension of the vectors\n");
    scanf("%d", &n);
    
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    
    // Read the data
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    // Begin the timer
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Calculation part
    long long result = 0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }

    // End of the timer
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    // Calculate the time consumption
    double duration = (end.tv_sec - start.tv_sec) 
                    + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Dot product result: %lld\n", result);
    printf("Computation time: %.9f seconds\n", duration);

    free(a);
    free(b);
    
    return 0;
}
