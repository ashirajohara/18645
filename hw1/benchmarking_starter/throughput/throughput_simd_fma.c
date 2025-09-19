#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

#define MAX_FREQ 3.2
#define BASE_FREQ 2.1
#define NUM_INST 3000.0
#define NUM_CHAINS 16

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#define FMA(src1, src2, src3, src4, src5, src6, src7, src8) \
  __asm__ __volatile__( \
    "vfmadd231pd %[xsrc1], %[xsrc1], %[xsrc1]\n" \
    "vfmadd231pd %[xsrc2], %[xsrc2], %[xsrc2]\n" \
    "vfmadd231pd %[xsrc3], %[xsrc3], %[xsrc3]\n" \
    "vfmadd231pd %[xsrc4], %[xsrc4], %[xsrc4]\n" \
    "vfmadd231pd %[xsrc5], %[xsrc5], %[xsrc5]\n" \
    "vfmadd231pd %[xsrc6], %[xsrc6], %[xsrc6]\n" \
    "vfmadd231pd %[xsrc7], %[xsrc7], %[xsrc7]\n" \
    "vfmadd231pd %[xsrc8], %[xsrc8], %[xsrc8]\n" \
    : [xsrc1] "+x" (src1), \
      [xsrc2] "+x" (src2), \
      [xsrc4] "+x" (src4), \
      [xsrc3] "+x" (src3), \
      [xsrc5] "+x" (src5), \
      [xsrc7] "+x" (src7), \
      [xsrc6] "+x" (src6), \
      [xsrc8] "+x" (src8) \
  );

#define FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \
  FMA(ax, bx, cx, dx, ex, fx, gx, hx) \
  FMA(ix, jx, kx, lx, mx, nx, ox, px) \

#define FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA10(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px)

#define FMA1000(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px) \
  FMA100(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px)


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
  double p[4] = {1.0, 1.0, 1.0, 1.0};
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
  __m256d px = _mm256_load_pd(&a[0]);

  for (int j = 0; j < runs; j++) {

    // Time the add
    st = rdtsc();
    
    FMA1000(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px);
    FMA1000(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px);
    FMA1000(ax, bx, cx, dx, ex, fx, gx, hx, ix, jx, kx, lx, mx, nx, ox, px);
    //TODO:Put your chains here
    
    et = rdtsc();

    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_ADD: %llu\n\r",sum);
  printf("TURBO Cycles Taken for SIMD_ADD: %lf\n\r",sum * ((double)MAX_FREQ)/BASE_FREQ);
  printf("Throughput : %lf\n\r",(double)(NUM_INST * runs * NUM_CHAINS) / (sum * MAX_FREQ/BASE_FREQ));

return 0;
}
