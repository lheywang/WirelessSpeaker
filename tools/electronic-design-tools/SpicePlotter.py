# ===============================================================================
# SpicePlotter.py
# Tool to analyse QSPICE simulated data easier than with the integrated tool,
# by providing multiples graphes where a single parameter change for them.
# Wrote by lheywang on october 2024.
# ===============================================================================

import os

# from PyQSPICE import clsQSPICE as pqs # type: ignore
from pick import pick  # type: ignore
import cudf
import numpy as np
import time
cuts = time.time()

# First, we need to replace every \t with a ,
# This will make the parsing of data easier
with open("data/Components.csv", "r") as f:
    data = f.read()
data = data.replace("\t", ",")
with open("temp/Components.csv", "w") as f:
    f.write("Frequency,V(outr+high),iV(outr+high),V(outr-high),iV(outr-high),V(outr+mediums),iV(outr+mediums),V(outr-mediums),iV(outr-mediums),V(outl+high),iV(outl+high),V(outl-high),iV(outl-high),V(outl+mediums),iV(outl+mediums),V(outl-mediums),iV(outl-mediums),V(out+bass),iV(out+bass),V(out-bass),iV(out-bass)\n")
    for line in data.splitlines(True)[1:]:
        f.write(line)

# Load the CSV file
# 21 columns !
# The order shall be defined by the user when exporting ...
df = cudf.read_csv("temp/Components.csv", sep=",")

# Convert all columns to their Amplititude and Phase
MagPhi = cudf.DataFrame()
col = ["outr+high","outr-high","outr+mediums","outr-mediums","outl+high","outl-high","outl+mediums","outl-mediums","out+bass","out-bass"]
for column in col:
    MagPhi[f"V({column})"] = 20 * np.log10(np.abs(np.sqrt(np.power(df[f"V({column})"], 2) + np.power(df[f"iV({column})"], 2))))
    MagPhi[f"P({column})"] =  np.arctan2(df[f"iV({column})"], df[f"V({column})"]) * 180 / np.pi

print(MagPhi)

cutf = time.time()
input("Press enter to exit...")
print(f"Time elapsed : {cutf - cuts}")

