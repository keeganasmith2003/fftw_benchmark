# GENERAL INFO  
This repository is to benchmark fftw with a large amount of memory (400 GB). The benchmark performs a 1D, complex to complex DFT with 26843545600 points.  
This program uses double precision, and points are randomly generated from a uniform distribution between 0 and 1.
# RUNNING (single core)  
## on ACES
```
git clone git@github.com:keeganasmith2003/fftw_benchmark.git
cd fftw_benchmark
sbatch myjob  
```  
produces a file 'out' which contains information about how long it took to execute fft.  
## locally
You will need to install fftw, reference:  
https://www.fftw.org/fftw2_doc/fftw_6.html 
Then:  
```
git clone git@github.com:keeganasmith2003/fftw_benchmark.git
cd fftw_benchmark
make fft
./compute_fft
```
The program will print info about how long it took to stdout.  
