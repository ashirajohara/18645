#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

//TODO: Adjust the frequency based on your machine.
#define MAX_FREQ 3.2
#define BASE_FREQ 2.1

//TODO: Change this to reflect the number of instructions in your chain
#define NUM_INST 9000.0 

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#define FMA(src1, src2, src3) \
  __asm__ __volatile__( \
    "vfmadd231pd %[xsrc1], %[xsrc2], %[xsrc3]\n" \
    "vfmadd231pd %[xsrc3], %[xsrc1], %[xsrc2]\n" \
    "vfmadd231pd %[xsrc2], %[xsrc3], %[xsrc1]\n" \
    : [xsrc1] "+x" (src1), \
      [xsrc2] "+x" (src2), \
      [xsrc3] "+x" (src3)  \
  );

#define FMA10(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) \
  FMA(x, y, z) 

#define FMA100(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z) \
  FMA10(x, y, z)

#define FMA1000(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z) \
  FMA100(x, y, z)

// TODO: Define your macros here
//Hint: You may want to write Macros that call Macro intrinsics

int main(int argc, char **argv) {

  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 100;


  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;
  double x[4] = {3.0, 2.0, 3.0, 1.0};
  double y[4] = {3.0, 2.0, 3.0, 1.0};
  double z[4] = {3.0, 2.0, 3.0, 1.0};
  __m256d xx = _mm256_load_pd(&x[0]);
  __m256d yx = _mm256_load_pd(&y[0]);
  __m256d zx = _mm256_load_pd(&z[0]);

  for (int j = 0; j < runs; j++) {
    st = rdtsc();
    FMA1000(xx, yx, zx);
    FMA1000(xx, yx, zx);
    FMA1000(xx, yx, zx);
    et = rdtsc();
    // Chain of NUM_INST simd fma instructions
    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_FMA: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / (NUM_INST * runs));

  return 0;
}
