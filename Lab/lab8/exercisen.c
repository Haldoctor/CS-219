#include <arm_neon.h> 
#include <stdio.h>
#include <stdint.h> 
#include <time.h>
#include <stdlib.h>

int main(){
  int N = 0;
  scanf("%d", &N);
  float *a = malloc(N * sizeof(float));
  float *b = malloc(N * sizeof(float));
  float *c = malloc(N * sizeof(float));

  for (size_t i = 0; i < N; i++) {
    a[i] = (float)i;
    b[i] = (float)i;
  }

  struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

  for (size_t i = 0; i + 3 < N; i += 4) {
    float32x4_t vec_a = vld1q_f32(a + i); 
    float32x4_t vec_b = vld1q_f32(b + i);
    float32x4_t vec_c = vaddq_f32(vec_a, vec_b); 
    __builtin_neon_vst1q_v(c + i, (int8x16_t)vec_c, 41); 
  }

  clock_gettime(CLOCK_MONOTONIC, &end);
      double duration = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\n neon 代码耗时: %.9f s\n", duration);

    free(a);
    free(b);
    free(c);
    return 0;

}
