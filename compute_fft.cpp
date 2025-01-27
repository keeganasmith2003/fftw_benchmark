#include "compute_fft.h"
#include "omp.h"
using namespace std;
using clock_type = chrono::high_resolution_clock;
  
void compute_fft(const int n, const int num_threads){
  omp_set_num_threads(num_threads);
  cout << "size of each fft is: " << n << "\n";
  cout << "executing with " << num_threads << " threads\n";
  fftw_init_threads();
  fftw_plan_with_nthreads(num_threads);
  fftw_complex* in;
  fftw_complex* out;
  auto start = clock_type::now();
  in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n * num_threads);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n * num_threads);
  fftw_plan plan = fftw_plan_many_dft(1, &n, num_threads,
                             in, &n,
                             1, n,
                             out, &n,
                             1, n,
                             FFTW_FORWARD, FFTW_ESTIMATE);
  populate_input(n * num_threads, in);
  fftw_execute(plan);
  
  auto end_time = clock_type::now();
  auto interval = end_time - start;
  auto duration = chrono::duration_cast<chrono::nanoseconds>(interval).count();
  cout << "Time taken to execute fft (excluding time taken to generate input): " << duration << "\n";
  fftw_destroy_plan(plan);
  fftw_free(in); fftw_free(out);
  fftw_cleanup_threads()
}
// void compute_fft(long long n, int num_threads){
//   fftw_init_threads();
//   fftw_plan_with_nthreads(num_threads);
//   fftw_complex *in, *out;
// 	fftw_plan p;
// 	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
// 	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
// 	populate_input(n, in);
//   auto start = clock_type::now();
//   p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
//   fftw_execute(p);
//   fftw_destroy_plan(p);
//   fftw_free(in); fftw_free(out);
//   auto end = clock_type::now();
//   auto interval = end - start;
//   auto duration = chrono::duration_cast<chrono::nanoseconds>(interval).count();
//   cout << "Time taken to execute fft (excluding time taken to generate input): " << duration << "\n";
// }
