fft:
	g++ compute_fft.cpp -o compute_fft -lfftw3
fft_parallel:
	g++ multi_compute_fft.cpp -o multi_compute_fft -lfftw3_threads -lfftw3	
