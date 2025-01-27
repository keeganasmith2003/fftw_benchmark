fft:
	g++ runner.cpp compute_fft.cpp common.cpp -o runner -fopenmp -lfftw3_threads -lfftw3
