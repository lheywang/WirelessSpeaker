# ===============================================================================
# SpicePlotter.py
# Tool to analyse QSPICE simulated data easier than with the integrated tool,
# by providing multiples graphes where a single parameter change for them.
# Wrote by lheywang on october 2024.
#
# This tool use extensively Nvidia CUDF to speed up packages on such larges datasets !
#
# ===============================================================================

import os
import numpy as np
import time
from tqdm import tqdm

try:
    import cudf
except:
    print(
        "Failed to import cudf...\nNow using pandas as replacement but with performance loss"
    )
    exit()


# Starting execution chronometer
cuts = time.time()

# First, we need to replace every \t with a ,
# This will make the parsing of data easier
# We do this for every file in the data folder.
obj = os.scandir(os.getcwd() + "/data")
files = []
for entry in obj:
    if entry.is_file():
        files.append(entry.name)

# print("Preparing input files for future treatement...")
# for file in tqdm(files):
#     with open(f"data/{file}", "r") as f:
#         data = f.read()
#     data = data.replace("\t", ",")
#     with open(f"temp/{file}", "w") as f:
#         f.write("Frequency,V(outr+high),iV(outr+high),V(outr-high),iV(outr-high),V(outr+mediums),iV(outr+mediums),V(outr-mediums),iV(outr-mediums),V(outl+high),iV(outl+high),V(outl-high),iV(outl-high),V(outl+mediums),iV(outl+mediums),V(outl-mediums),iV(outl-mediums),V(out+bass),iV(out+bass),V(out-bass),iV(out-bass)\n")
#         for line in data.splitlines(True)[1:]:
#             f.write(line)

# Load the CSV file
# 21 columns !
# The order shall be defined by the user when exporting ...
print("Loading data into VRAM...")
df = cudf.read_csv(f"temp/{files[0]}", sep=",")
for file in tqdm(files[1:]):
    df = cudf.concat(
        [df, cudf.read_csv(f"temp/{file}", sep=",").astype("float32")], axis=0
    )

# Convert all columns to their Amplititude and Phase.
print("Preparing data for future treatement...")
MagPhi = cudf.DataFrame()
MagPhi["Frequency"] = df["Frequency"]
col = [
    "outr+high",
    "outr-high",
    "outr+mediums",
    "outr-mediums",
    "outl+high",
    "outl-high",
    "outl+mediums",
    "outl-mediums",
    "out+bass",
    "out-bass",
]
for column in tqdm(col):
    MagPhi[f"V({column})"] = 20 * np.log10(
        np.abs(
            np.sqrt(np.power(df[f"V({column})"], 2) + np.power(df[f"iV({column})"], 2))
        )
    )
    MagPhi[f"P({column})"] = (
        np.arctan2(df[f"iV({column})"], df[f"V({column})"]) * 180 / np.pi
    )

def ComputeStats(Frame):
    return Frame.mean(), Frame.min(), Frame.max(), Frame.std()


print("Computing statistics per frequencies...")
MagPhi = MagPhi.sort_values("Frequency")
RowNumber = MagPhi['Frequency'].value_counts().sort_index().max()

Means = MagPhi.rolling(window=int(RowNumber), min_periods=1).mean()
Max = MagPhi.rolling(window=int(RowNumber), min_periods=1).max()
Min = MagPhi.rolling(window=int(RowNumber), min_periods=1).min()
STD = MagPhi.rolling(window=int(RowNumber), min_periods=1).std()

print(Means)
print(Max)
print(Min)
print(STD)





# for freq in tqdm(Freqs):
#     Stats._concat([freq.mean(), freq.min(), freq.max(), freq.std()])
# print(Stats)


cutf = time.time()
input("Press enter to exit...")
print(f"Time elapsed : {cutf - cuts}")
