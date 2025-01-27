#include "compute_fft.h"
#include "omp.h"
using namespace std;
using clock_type = chrono::high_resolution_clock;
  
void compute_fft(long long n, int num_threads){
  omp_set_num_threads(num_threads);
  cout << "size of each fft is: " << n << "\n";
  cout << "executing with " << num_threads << " threads\n";
  vector<fftw_complex*> ins(num_threads);
  vector<fftw_complex*> outs(num_threads);
  vector<fftw_plan> plans(num_threads);
  //initialize all plans before execution
  //this is necessary because fftw plan cannot be
  //called within an openmp parallel region
  for(int i = 0; i < num_threads; i++){
    ins[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    outs[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    plans[i] = fftw_plan_dft_1d(n, ins[i], outs[i], FFTW_FORWARD, FFTW_ESTIMATE);
  }
  auto start = clock_type::now();
  cout << "starting parallel section\n";

  #pragma omp parallel 
  {
    int id = omp_get_thread_num();
    populate_input(n, ins[id]);
    fftw_execute(plans[id]);
  }
  
  auto end_time = clock_type::now();
  auto interval = end_time - start;
  auto duration = chrono::duration_cast<chrono::nanoseconds>(interval).count();
  cout << "Time taken to execute fft (excluding time taken to generate input): " << duration << "\n";
  for(int i = 0; i < num_threads; i++){
    fftw_destroy_plan(plans[i]);
    fftw_free(ins[i]); fftw_free(outs[i]);
  }
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
