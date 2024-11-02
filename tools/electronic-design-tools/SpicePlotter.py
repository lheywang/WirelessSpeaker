# ===============================================================================
# SpicePlotter.py
# Tool to analyse QSPICE simulated data easier than with the integrated tool,
# by providing multiples graphes where a single parameter change for them.
# Wrote by lheywang on october 2024.
# ===============================================================================

import os
if os.name != "nt":
    print("Due to QSPICE availability on Windows only, please run this script for a Windows device.")
    exit()
from PyQSPICE import clsQSPICE as pqs # type: ignore
from pick import pick # type: ignore
import os # type: ignore
import math # type: ignore
import pandas as pd # type: ignore
import matplotlib as mpl # type: ignore
import matplotlib.pyplot as plt # type: ignore

# Create an instance of PyQSPICE
run = pqs("top")

title = "What do you want to do ?"
options = ["Load a QRAW", "Simulate a netlist", "Simulate a qsch circuit"]

job, index = pick(options, title)

if (index == 2):
    run.qsch2cir()
    run.cir2qraw()
if (index == 1):
    run.cir2qraw()

data = run.LoadQRAW(["V(R+High)"])
print(data)
print(data.sem)

mpl.rcParams.update([['font.sans-serif', ["Arial Rounded MT Bold", 'Arial Unicode MS', 'Arial', 'sans-serif']], ["mathtext.default", "rm"], ["legend.labelspacing", 0.1], ["legend.columnspacing", 0.2], ["legend.handletextpad", 0.3], ['axes.formatter.useoffset', False], ['xtick.minor.visible', True], ['ytick.minor.visible', True], ['grid.linewidth', 1],["savefig.dpi", 300], ["axes.unicode_minus", False]])

plt.close('all')

#['Solarize_Light2', '_classic_test_patch', '_mpl-gallery', '_mpl-gallery-nogrid', 'bmh', 'classic', 'dark_background', 'fast', 'fivethirtyeight', 'ggplot', 'grayscale', 'seaborn-v0_8', 'seaborn-v0_8-bright', 'seaborn-v0_8-colorblind', 'seaborn-v0_8-dark', 'seaborn-v0_8-dark-palette', 'seaborn-v0_8-darkgrid', 'seaborn-v0_8-deep', 'seaborn-v0_8-muted', 'seaborn-v0_8-notebook', 'seaborn-v0_8-paper', 'seaborn-v0_8-pastel', 'seaborn-v0_8-poster', 'seaborn-v0_8-talk', 'seaborn-v0_8-ticks', 'seaborn-v0_8-white', 'seaborn-v0_8-whitegrid', 'tableau-colorblind10']

for stl in ['ggplot', 'Solarize_Light2', 'classic', 'dark_background', 'grayscale']:
    plt.style.use(stl)

    fig, ax = plt.subplots(tight_layout=True)

    for i in range(run.sim['Nstep']):
        data[data.Step == i].plot(ax=ax, x=run.sim['Xlbl'],  y="V(R+High)", label="Step-" + str(i))

    ax.set_xlim(run.sim['Xmin'],run.sim['Xmax'])
    ax.set_ylim(-80,20)
    ax.set_ylabel('Output amplitude (dB)', fontsize=14)
    ax.set_xlabel('$V_{DS}$ (Hz)', fontsize=14)
    ax.minorticks_on()

    ax.grid(which='major', linewidth="0.5")
    ax.grid(which='minor', linewidth="0.35")

    ax.text(0.1, 70, run.sim['StepInfo'])
    plt.legend(ncol=1, loc="center left",fancybox=True)

    plt.show()

    run.tstime(['png'])
    plt.savefig(run.path['png'], format='png', bbox_inches='tight')
    plt.close('all')





