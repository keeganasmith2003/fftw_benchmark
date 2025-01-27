#include "compute_fft.h"
using std::stoi;
using std::cout;
int main(int argc, char* argv[]){
  int num_threads = 1;
	long long NUM_DOUBLES = (long long)(INT32_MAX - 1) * 2;
  long long N = NUM_DOUBLES/2;
	cout << "Amount of memory: " << gigs << " GB\n";
  if(argc > 2 && argv[1] == "-n"){
    num_threads = stoi(argv[2]);
    compute_fft(N, num_threads);
  }
  else{
    cout << "did not specify number of threads\n";
  }
}
