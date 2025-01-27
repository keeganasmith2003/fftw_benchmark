fft:
	g++ runner.cpp compute_fft.cpp common.cpp -o runner -lfftw3_threads -lfftw3
