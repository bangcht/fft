import random
import numpy
from scipy import fftpack

SIZE = 8
RANGE = 1

temp = raw_input("Enter SIZE: ") 
SIZE = int(temp)

f = open('input.txt', 'w')

input_data = numpy.random.uniform(-RANGE, RANGE, size = SIZE)

f.write(str(SIZE) + '\n')
for i in range(0, input_data.size):
	f.write(str(input_data[i]) + '\n')

f.close()

f = open('output.txt', 'w')


output_data = fftpack.fft(input_data)

for i in range(0, output_data.size):
	c = output_data[i]
	f.write(str(c.real) + " " + str(c.imag) + '\n')

f.close()
