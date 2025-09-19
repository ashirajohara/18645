#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

// These specs work and are for Intel(R) Xeon(R) Silver 4208 CPU @ 2.10GHz (ECE machine 022)
#define MAX_FREQ 3.2
#define BASE_FREQ 2.1
#define NUM_INST 3000.0 

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#define ADD(src1, src2, dest) \
  __asm__ __volatile__( \
    "vaddpd %[xsrc1], %[xsrc2], %[xdest]\n" \
    : [xdest] "+x" (dest) \
    : [xsrc1] "x" (src1), \
      [xsrc2] "x" (src2)  \
  );


#define ADD10(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) \
  ADD(x, y, z) 

#define ADD100(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z) \
  ADD10(x, y, z)

#define ADD1000(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z) \
  ADD100(x, y, z)

int main(int argc, char **argv) {

  int runs = 100;

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;
  double a[4] = {1.0, 1.0, 1.0, 1.0};
  __m256d ax = _mm256_load_pd(&a[0]);

  for (int j = 0; j < runs; j++) {

    st = rdtsc();
    ADD1000(ax, ax, ax);
    ADD1000(ax, ax, ax);
    ADD1000(ax, ax, ax);
    et = rdtsc();
    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_ADD: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / (NUM_INST * runs));

  return 0;
}
