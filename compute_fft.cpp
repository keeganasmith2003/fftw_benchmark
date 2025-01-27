#include "compute_fft.h"
#include "omp.h"
using namespace std;
using clock_type = chrono::high_resolution_clock;
  
void compute_fft(long long n, int num_threads){
  omp_set_num_threads(num_threads);
  cout << "size of each fft is: " << n << "\n";
  cout << "executing with " << num_threads << " threads\n";
  
  auto start = clock_type::now();
  cout << "starting parallel section\n";
  #pragma omp parallel 
  {
    fftw_complex *in, *out;
    fftw_plan p; 
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    #pragma omp critical
    { 
      cout << "initialized in/out\n";
    }
    populate_input(n, in);
    #pragma omp critical
    {
      cout << "populated input\n";
    }
    p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    #pragma omp critical
    {
      cout << "created plan\n";
    }
    if (!in || !out) {
      cerr << "FAILURE IN DATA ALLOCATION\n";
      exit(EXIT_FAILURE);
    }
    if (!p) {
          cerr << "FFTW plan creation failed.\n";
          fftw_free(in);
          fftw_free(out);
          exit(EXIT_FAILURE);
      }
    cout << "executing fft\n";
    fftw_execute(p);
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
  }
  auto end_time = clock_type::now();
  auto interval = end_time - start;
  auto duration = chrono::duration_cast<chrono::nanoseconds>(interval).count();
  cout << "Time taken to execute fft (excluding time taken to generate input): " << duration << "\n";
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
