#include "common.h"
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
