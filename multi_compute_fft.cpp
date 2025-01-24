#include <fftw3.h>
#include <bits/stdc++.h>
using namespace std;
using clock_type = chrono::high_resolution_clock;

double generate_random_number(){
  return static_cast<double>(std::rand()) / RAND_MAX;
}
void populate_input(int n, fftw_complex* in){
  srand(42); 
  for(int i = 0; i < n; i++){
    in[i][0] = generate_random_number();
    in[i][1] = generate_random_number();
  }
}  
void compute_fft(int n, int num_threads){
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
int main(){
  long long TOTAL_BYTES = (long long)400 * 1024 * 1024 * 1024;
  long long NUM_DOUBLES = TOTAL_BYTES / (sizeof(double));
  int num_threads = 64;
  compute_fft(NUM_DOUBLES / 2, num_threads);
}
