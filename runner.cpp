#include "compute_fft.h"
using std::stoi;
using std::cout;
int main(int argc, char* argv[]){
  int num_threads = 1;
	long long NUM_DOUBLES = (long long)(INT32_MAX) * 2;
  int N = NUM_DOUBLES/32;
  if(argc > 2 && (strcmp(argv[1], "-n") == 0)){
    num_threads = stoi(argv[2]);
    compute_fft(N, num_threads);
  }
  else{
    cout << "did not specify number of threads\n";
  }
}
