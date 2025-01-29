import numpy as np
import matplotlib.pyplot as plt

NUM_SAMPLES = 0
FILE = open('./meminfo_output_run_0/meminfo_64.log')
WATCH_SECONDS = 2
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
    return meminfo

def plot(attribute, meminfo):
    y_data = meminfo[attribute]
    # Data for plotting
    t = np.arange(0.0, len(y_data) * WATCH_SECONDS, WATCH_SECONDS)

    fig, ax = plt.subplots()
    ax.plot(t, y_data)

    ax.set(xlabel='time (s)', ylabel=attribute,
        title=f'{attribute} vs. time')
    ax.grid()
    fig.savefig(f"./figures/{attribute}.png")


def main():
    meminfo = parse_meminfo()
    plot("MemFree", meminfo)
    # OUT.write('Time'+',')
    # for each in meminfo:
    #     OUT.write(each + ',')
    # OUT.write('\n')
    # for i in range(0,int(len(dates))):
    #     OUT.write(dates[i].strip()+',')
    #     for each in meminfo:
    #         OUT.write(meminfo[each][i] + ',')
    #     OUT.write('\n')
if __name__ == "__main__":
    main()
