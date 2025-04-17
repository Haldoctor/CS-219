#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    size_t N = 0;
    scanf("%zd", &N);
    float *a = malloc(N * sizeof(float));
    float *b = malloc(N * sizeof(float));
    float *c = malloc(N * sizeof(float));

    for (size_t i = 0; i < N; i++) {
        a[i] = (float)i;
        b[i] = (float)i;
    }
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t i = 0; i < N; i++) {
      c[i] = a[i] + b[i];
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);

      double duration = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\nC 代码耗时: %.9f s\n", duration);
    

    free(a);
    free(b);
    free(c);
    return 0;
}