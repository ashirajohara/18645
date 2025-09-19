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

#define FMA(src1) \
  __asm__ __volatile__( \
    "vfmadd231pd %[xsrc1], %[xsrc1], %[xsrc1]\n" \
    : [xsrc1] "+x" (src1) \
  );

#define FMA10(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) \
  FMA(x) 

#define FMA100(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x) \
  FMA10(x)

#define FMA1000(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x) \
  FMA100(x)

int main(int argc, char **argv) {

  int runs = 100;

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;
  double x[4] = {3.0, 2.0, 3.0, 1.0};
  __m256d xx = _mm256_load_pd(&x[0]);

  for (int j = 0; j < runs; j++) {

    st = rdtsc();
    FMA1000(xx);
    FMA1000(xx);
    FMA1000(xx);
    et = rdtsc();
    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_FMA: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / (NUM_INST * runs));

  return 0;
}
