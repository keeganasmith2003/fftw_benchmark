#include "compute_fft.h"
using std::stoi;
using std::cout;
int main(int argc, char* argv[]){
	cout << "first arg was " << argv[1] << "\n";
  int gigs = stoi(argv[1]);
  int num_threads = 1;
  cout << "num gigs is " << (long long)gigs << "\n"; 
	long long TOTAL_BYTES = (long long)gigs * 1024 * 1024 * 1024;
	long long NUM_DOUBLES = TOTAL_BYTES / (sizeof(double));
  long long N = NUM_DOUBLES/2;
	cout << "Amount of memory: " << gigs << " GB\n";
  if(argc > 2 && argv[2] == "-n"){
    num_threads = stoi(argv[3]);
    compute_fft(N, num_threads);
  }
  else{
    cout << "did not specify number of threads\n";
  }
}
