#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

//TODO: Adjust the frequency based on your machine.
#define MAX_FREQ 3.2
#define BASE_FREQ 2.1
// these specs work and are for Intel(R) Xeon(R) Silver 4208 CPU @ 2.10GHz (ece machine 022)

//TODO: Change this to reflect the number of instructions in your chain
#define NUM_INST 3000.0 

#define MULTIPLY(dest, src) \
  __asm__ __volatile__( \
    "imul %[rsrc], %[rdest]\n" \
    : [rdest] "+r" (dest) \
    : [rsrc] "r" (src) \
  );

#define MULTIPLY10(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y) \
  MULTIPLY(x, y)

#define MULTIPLY100(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y) \
  MULTIPLY10(x, y)

#define MULTIPLY1000(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y) \
  MULTIPLY100(x, y)

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

//Hint: You may want to write Macros that call Macro intrinsics

int main(int argc, char **argv) {
  
  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 100;

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;
  int x = 3;
  int y = 2;

  for (int j = 0; j < runs; j++) {

    st = rdtsc();
    MULTIPLY1000(x, y);
    MULTIPLY1000(x, y);
    MULTIPLY1000(x, y);
    et = rdtsc();
    // Chain of NUM_INST simd add instructions
    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for INT_MUL: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / (NUM_INST * runs));

  return 0;
}
