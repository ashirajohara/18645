#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

//TODO: Adjust the frequency based on your machine.
#define MAX_FREQ 3.2
#define BASE_FREQ 2.1

//TODO: Change number of instructions to reflect your chains
#define NUM_INST 3000.0
//TODO: Change to reflect number of independent chains
#define NUM_CHAINS 10

#define ADD(src1, src2, src3, src4, src5, src6, src7, src8, src9, src10) \
  __asm__ __volatile__( \
    "vaddpd %[xsrc1], %[xsrc1], %[xsrc1]\n" \
    "vaddpd %[xsrc2], %[xsrc2], %[xsrc2]\n" \
    "vaddpd %[xsrc3], %[xsrc3], %[xsrc3]\n" \
    "vaddpd %[xsrc4], %[xsrc4], %[xsrc4]\n" \
    "vaddpd %[xsrc5], %[xsrc5], %[xsrc5]\n" \
    "vaddpd %[xsrc6], %[xsrc6], %[xsrc6]\n" \
    "vaddpd %[xsrc7], %[xsrc7], %[xsrc7]\n" \
    "vaddpd %[xsrc8], %[xsrc8], %[xsrc8]\n" \
    "vaddpd %[xsrc9], %[xsrc9], %[xsrc9]\n" \
    "vaddpd %[xsrc10], %[xsrc10], %[xsrc10]\n" \
    : [xsrc1] "+x" (src1), \
      [xsrc2] "+x" (src2), \
      [xsrc3] "+x" (src3), \
      [xsrc4] "+x" (src4), \
      [xsrc5] "+x" (src5), \
      [xsrc6] "+x" (src6), \
      [xsrc7] "+x" (src7), \
      [xsrc8] "+x" (src8), \
      [xsrc9] "+x" (src9),  \
      [xsrc10] "+x" (src10)  \
  );

#define ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx)

#define ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD10(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx)

#define ADD1000(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx) \
  ADD100(ax, bx, cd, dx, ex, fx, gx, hx, ix, jx)

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

//TODO: Define your Macros here

int main(int argc, char **argv) {

  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 100;

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;
  double a[4] = {1.0, 1.0, 1.0, 1.0};
  double b[4] = {1.0, 1.0, 1.0, 1.0};
  double c[4] = {1.0, 1.0, 1.0, 1.0};
  double d[4] = {1.0, 1.0, 1.0, 1.0};
  double e[4] = {1.0, 1.0, 1.0, 1.0};
  double f[4] = {1.0, 1.0, 1.0, 1.0};
  double g[4] = {1.0, 1.0, 1.0, 1.0};
  double h[4] = {1.0, 1.0, 1.0, 1.0};
  double i[4] = {1.0, 1.0, 1.0, 1.0};
  double j[4] = {1.0, 1.0, 1.0, 1.0};
  double k[4] = {1.0, 1.0, 1.0, 1.0};
  double l[4] = {1.0, 1.0, 1.0, 1.0};
  double m[4] = {1.0, 1.0, 1.0, 1.0};
  double n[4] = {1.0, 1.0, 1.0, 1.0};
  double o[4] = {1.0, 1.0, 1.0, 1.0};
  __m256d ax = _mm256_load_pd(&a[0]);
  __m256d bx = _mm256_load_pd(&a[0]);
  __m256d cx = _mm256_load_pd(&a[0]);
  __m256d dx = _mm256_load_pd(&a[0]);
  __m256d ex = _mm256_load_pd(&a[0]);
  __m256d fx = _mm256_load_pd(&a[0]);
  __m256d gx = _mm256_load_pd(&a[0]);
  __m256d hx = _mm256_load_pd(&a[0]);
  __m256d ix = _mm256_load_pd(&a[0]);
  __m256d jx = _mm256_load_pd(&a[0]);
  __m256d kx = _mm256_load_pd(&a[0]);
  __m256d lx = _mm256_load_pd(&a[0]);
  __m256d mx = _mm256_load_pd(&a[0]);
  __m256d nx = _mm256_load_pd(&a[0]);
  __m256d ox = _mm256_load_pd(&a[0]);

  for (int j = 0; j < runs; j++) {

    // Time the add
    st = rdtsc();
    ADD1000(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx);
    ADD1000(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx);
    ADD1000(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx);

    et = rdtsc();

    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_ADD: %llu\n\r", sum);
  printf("TURBO Cycles Taken for SIMD_ADD: %lf\n\r", sum * ((double)MAX_FREQ)/BASE_FREQ);
  printf("Throughput : %lf (Chains: %d)\n\r", (((double)NUM_INST * runs * NUM_CHAINS) / (sum * MAX_FREQ/BASE_FREQ)), NUM_CHAINS);

return 0;
}
