#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

//TODO: Adjust the frequency based on your machine.
#define MAX_FREQ 3.4
#define BASE_FREQ 2.4

//TODO: Change number of instructions to reflect your chains
#define NUM_INST 625.0
//TODO: Change to reflect number of independent chains
#define NUM_CHAINS 3

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

  for (int j = 0; j < runs; j++) {

    // Time the add
    st = rdtsc();
    
    //TODO: Put your chains here
    //You should be computing NUM_INST*NUM_CHAINS instructions
    et = rdtsc();

    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_ADD: %llu\n\r",sum);
  printf("TURBO Cycles Taken for SIMD_ADD: %lf\n\r",sum * ((double)MAX_FREQ)/BASE_FREQ);
  printf("Throughput : %lf (chains: )\n\r",((double)NUM_INST * runs * NUM_CHAINS) / (sum * MAX_FREQ/BASE_FREQ));

return 0;
}
