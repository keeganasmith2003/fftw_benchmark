#include "compute_fft.h"
using namespace std;
using clock_type = chrono::high_resolution_clock;
  
void compute_fft(long long n){
	fftw_complex *in, *out;
	fftw_plan p;
	cout << "n was: " << n << "\n";
  in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
	populate_input(n, in);
  auto start = clock_type::now();
  cout << "segfault happened here2\n";
  p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	cout << "segfault happened before execute, after plan\n";
  if (!in || !out) {
    std::cerr << "Error: Memory allocation failed for FFT input/output arrays." << std::endl;
    exit(EXIT_FAILURE);
}
  if (!p) {
        std::cerr << "FFTW plan creation failed.\n";
        fftw_free(in);
        fftw_free(out);
        exit(EXIT_FAILURE);
    }
  fftw_execute(p);
  cout << "seg fault happend here3\n";
  fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
  auto end = clock_type::now();
  auto interval = end - start;
  auto duration = chrono::duration_cast<chrono::nanoseconds>(interval).count();
  cout << "Time taken to execute fft (excluding time taken to generate input): " << duration << "\n";
}
void compute_fft(long long n, int num_threads){
  fftw_init_threads();
  fftw_plan_with_nthreads(num_threads);
  fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
	populate_input(n, in);
  auto start = clock_type::now();
  p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  fftw_free(in); fftw_free(out);
  auto end = clock_type::now();
  auto interval = end - start;
  auto duration = chrono::duration_cast<chrono::nanoseconds>(interval).count();
  cout << "Time taken to execute fft (excluding time taken to generate input): " << duration << "\n";
}
