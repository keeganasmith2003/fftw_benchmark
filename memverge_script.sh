#!/bin/bash
module purge
module load GCC/13.2.0 FFTW/3.3.10

cd /scratch/user/u.ks124812/wes_benchmarking/fft
make fft
export memverge="memverge"
for i in 32 64; do
  watch "cat /proc/meminfo >> ./meminfo_output_$memverge/meminfo_$i.log; date +"%Y-%m-%dT%H:%M:%S%z" >> ./meminfo_output_$memverge/meminfo_$i.log" &> /dev/null &
  watch "ps -p $(pgrep -f "runner") -o %cpu,%mem,cmd --no-headers >>./ps_output_$memverge/ps_output_$i.log; date +'%Y-%m-%dT%H:%M:%S%z' >>./ps_output_$memverge/ps_output_$i.log" &> /dev/null &
  watch "free -h >> ./free_output_$memverge/free_output_$i.log;  date +'%Y-%m-%dT%H:%M:%S%z' >>./free_output_$memverge/free_output_$i.log" &> /dev/null &
      echo num_threads: $i
      echo Start time:
      date
      ./runner -n $i
      echo End time:
      date
      killall -9 watch
      sleep 5
done
killall -9 watch

