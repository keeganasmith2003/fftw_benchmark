#include "compute_fft.h"
using std::stoi;
using std::cout;
int main(int argc, char* argv[]){
  int num_threads = 1;
	long long NUM_DOUBLES = (long long)(INT32_MAX) * 2;
  long long N = NUM_DOUBLES/1024;
  cout << "num argc: " << argc << "\n";
  if(argc > 2){
    cout << argv[1] << "\n";
  }
  if(argc > 2 && (strcmp(argv[1], "-n") == 0)){
    num_threads = stoi(argv[2]);
    compute_fft(N, num_threads);
  }
  else{
    cout << "did not specify number of threads\n";
  }
}
