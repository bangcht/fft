# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -fopenmp 
LOOFFLAG = -lm -lrt
# the build target executable:
TARGET = fft

fft: fft.h fft.c
	@$(CC) $(CFLAGS) -o fft fft.c $(LOOFFLAG)

dft: dft.h dft.c
	@$(CC) $(CFLAGS) -o dft dft.c $(LOOFFLAG)

test: test.c
	@$(CC) $(CFLAGS) -o test test.c $(LOOFFLAG)

clean:
	@rm -rf *.o *~ $(TARGET) dft fft