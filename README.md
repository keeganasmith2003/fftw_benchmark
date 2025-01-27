# GENERAL INFO  
This repository is to benchmark fftw with a large amount of memory (480 GB). The benchmark performs num_threads number of 1D, complex to complex DFT each with a variable number of points (usually on the order of $$$2^{26}$$$ or so).  
This program uses double precision, and points are randomly generated from a uniform distribution between 0 and 1.
# RUNNING  
## on ACES
```
git clone git@github.com:keeganasmith2003/fftw_benchmark.git
cd fftw_benchmark
mkdir free_output
mkdir meminfo_output
mkdir ps_output
sbatch myjob  
```  
Once finished, the output folders (free_output, meminfo_output, etc) 
## locally
You will need to install fftw, reference:  
https://www.fftw.org/fftw2_doc/fftw_6.html 
Then:  
```
git clone git@github.com:keeganasmith2003/fftw_benchmark.git
cd fftw_benchmark
make fft
./runner -n <num_threads you want>
```
The program will print info about how long it took to stdout.  
