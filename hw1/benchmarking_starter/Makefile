CC		= gcc
CC_FLAGS 	= -mavx -mfma -O2 -std=c99

default: all assemble

all: latency throughput

latency: latency_simd_add.x latency_simd_fma.x latency_int_mul.x
	./latency_simd_add.x 100
	./latency_simd_fma.x 100
	./latency_int_mul.x 100

throughput: throughput_simd_add.x throughput_simd_fma.x
	./throughput_simd_add.x
	./throughput_simd_fma.x


latency_simd_add.x:
	$(CC) $(CC_FLAGS) -o latency_simd_add.x latency/latency_simd_add.c
latency_simd_fma.x:	
	$(CC) $(CC_FLAGS) -o latency_simd_fma.x latency/latency_simd_fma.c
latency_int_mul.x:	
	$(CC) $(CC_FLAGS) -o latency_int_mul.x latency/latency_int_mul.c
	
throughput_simd_add.x:	
	$(CC) $(CC_FLAGS) -o throughput_simd_add.x throughput/throughput_simd_add.c
throughput_simd_fma.x:		
	$(CC) $(CC_FLAGS) -o throughput_simd_fma.x throughput/throughput_simd_fma.c
	

assemble:
	objdump -d --source ./latency_simd_add.x > latency_simd_add.S
	objdump -d --source ./latency_simd_fma.x > latency_simd_fma.S
	objdump -d --source ./throughput_simd_add.x > throughput_simd_add.S
	objdump -d --source ./throughput_simd_fma.x > throughput_simd_fma.S

clean:
	rm -rf *.x *.S
