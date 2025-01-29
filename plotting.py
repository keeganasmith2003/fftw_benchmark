#!/usr/bin/python3
NUM_SAMPLES = 0
FILE = open('./meminfo_64.log')
OUT = open('meminfo_64_reformatted.csv', 'w')
meminfo = {}
dates = []
lines = 0
for line in FILE:
    lines += 1
    if line.split()[0].strip(':') not in meminfo:
        if line[0:4] == '2025':
            dates.append(line)
        else:    
            meminfo[line.split()[0].strip(':')] = line.split()[1]
    elif type(meminfo[line.split()[0].strip(':')]) == list:
        meminfo[line.split()[0].strip(':')].append(line.split()[1])
    else:
        meminfo[line.split()[0].strip(':')] = [meminfo[line.split()[0].strip(':')], line.split()[1]]
print(meminfo)
OUT.write('Time'+',')
for each in meminfo:
    OUT.write(each + ',')
OUT.write('\n')
for i in range(0,int(len(dates))):
    OUT.write(dates[i].strip()+',')
    for each in meminfo:
        OUT.write(meminfo[each][i] + ',')
    OUT.write('\n')
