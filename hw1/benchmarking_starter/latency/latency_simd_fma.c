#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

//TODO: Adjust the frequency based on your machine.
#define MAX_FREQ 3.4
#define BASE_FREQ 2.4

//TODO: Change this to reflect the number of instructions in your chain
#define NUM_INST 625.0 

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}


// TODO: Define your macros here
//Hint: You may want to write Macros that call Macro intrinsics

int main(int argc, char **argv) {

  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 100;
  

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;

  for (int j = 0; j < runs; j++) {
    st = rdtsc();
    //TODO: Put your latency testing code here
    et = rdtsc();
    // Chain of NUM_INST simd fma instructions
    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_ADD: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / (NUM_INST * runs));

  return 0;
}
