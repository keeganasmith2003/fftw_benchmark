import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime
from dateutil import parser
NUM_SAMPLES = 0
FILE = open('./meminfo_output_run_0/meminfo_48.log')
WATCH_SECONDS = 1 
def parse_meminfo():
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
    return meminfo, dates

def convert_to_datetime(dt_string):
    return parser.parse(dt_string).timestamp()

def plot(attribute, meminfo, dates):
    y_data = list(map(int, meminfo[attribute]))
    x_data = list(map(convert_to_datetime, dates))
    # Data for plotting
    t = np.arange(0.0, len(y_data) * WATCH_SECONDS, WATCH_SECONDS)
    fig, ax = plt.subplots()
    ax.plot(t, y_data)

    ax.set(xlabel='time (s)', ylabel=attribute,
        title=f'{attribute} vs. time')
    fig.savefig(f"./figures/{attribute}.png")


def main():
    meminfo, dates = parse_meminfo()
    plot("MemFree", meminfo, dates)
    # OUT.write('Time'+',')
    # for each in meminfo:
    #    OUT.write(each + ',')
    # OUT.write('\n')
    # for i in range(0,int(len(dates))):
    #     OUT.write(dates[i].strip()+',')
    #     for each in meminfo:
    #         OUT.write(meminfo[each][i] + ',')
    #     OUT.write('\n')
if __name__ == "__main__":
    main()
