#!/bin/bash
#SBATCH --job-name=fftw
#SBATCH --time=02:00:00 --mem=480G
#SBATCH --ntasks=1 --nodes=1 --cpus-per-task=9
#SBATCH --output=out.log --error=error.log

module purge
module load GCC/13.2.0 FFTW/3.3.10

cd /scratch/user/u.ks124812/wes_benchmarking/fft
make fft

for i in 1 2 4 8; do
  watch "cat /proc/meminfo >> ./meminfo/meminfo_$i.log; date
  +"%Y-%m-%dT%H:%M:%S%z" >> ./meminfo/meminfo_$i.log" &> /dev/null &
  watch "ps -p $(pgrep -f "runner") -o %cpu,%mem,cmd --no-headers >>
  ./ps_output/ps_output_$i.log; date +'%Y-%m-%dT%H:%M:%S%z' >> ./ps_output/ps_output_$i.log" &> /dev/null &
  watch "free -h >> ./free_output/free_output_$i.log;  date +'%Y-%m-%dT%H:%M:%S%z' >>
  ./free_output/free_outfree_output_$i.log" &> /dev/null &
      echo Dimension 1: $i Dimension2: $i
      echo Start time:
      date
      ./runner -n $i
      echo End time:
      date
      killall -9 watch
      sleep 5
done
killall -9 watch

