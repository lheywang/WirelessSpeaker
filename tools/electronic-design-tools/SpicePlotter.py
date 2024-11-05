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
import matplotlib.pyplot as plt

try:
    import cudf
except:
    print(
        "Failed to import cudf...\nNow using pandas as replacement but with performance loss"
    )
    exit()


# Starting execution chronometer
cuts = time.time()

# =====================================================================================================================
#
# =====================================================================================================================

# First, we need to replace every \t with a ,
# This will make the parsing of data easier
# We do this for every file in the data folder.
obj = os.scandir(os.getcwd() + "/data")
files = []
for entry in obj:
    if entry.is_file():
        files.append(entry.name)

print("Preparing input files for future treatement...")
for file in tqdm(files):
    with open(f"data/{file}", "r") as f:
        data = f.read()
    data = data.replace("\t", ",")
    with open(f"temp/{file}", "w") as f:
        f.write("Frequency,V(outr+high),iV(outr+high),V(outr-high),iV(outr-high),V(outr+mediums),iV(outr+mediums),V(outr-mediums),iV(outr-mediums),V(outl+high),iV(outl+high),V(outl-high),iV(outl-high),V(outl+mediums),iV(outl+mediums),V(outl-mediums),iV(outl-mediums),V(out+bass),iV(out+bass),V(out-bass),iV(out-bass)\n")
        for line in data.splitlines(True)[1:]:
            f.write(line)
print("Done !")

# =====================================================================================================================
# CSV PARSING
# =====================================================================================================================
# Load the CSV file
# 21 columns !
# The order shall be defined by the user when exporting ...
print("Loading data into VRAM...")
df = cudf.read_csv(f"temp/{files[0]}", sep=",")
for file in tqdm(files[1:]):
    df = cudf.concat(
        [df, cudf.read_csv(f"temp/{file}", sep=",").astype("float32")], axis=0
    )
print("Done !")

# =====================================================================================================================
# MAGNITUDE AND PHASE COMPUTE
# =====================================================================================================================
# Conversion from complex to Magnitude and phase
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
print("Done !")

# =====================================================================================================================
# STATISTICS
# =====================================================================================================================
print("Computing statistics per frequencies...")
MagPhi = MagPhi.sort_values("Frequency")
RowNumber = MagPhi['Frequency'].value_counts().sort_index().max()

Mean = MagPhi.rolling(window=int(RowNumber), min_periods=1).mean()
Max = MagPhi.rolling(window=int(RowNumber), min_periods=1).max()
Min = MagPhi.rolling(window=int(RowNumber), min_periods=1).min()
STD = MagPhi.rolling(window=int(RowNumber), min_periods=1).std()
print("Done !")

# =====================================================================================================================
# REPRESENTATION
# =====================================================================================================================
print("Computing presentations data...")
GlobalData = cudf.DataFrame()
GlobalData["Frequency"] = MagPhi["Frequency"]
# Global Minimums for audio response
# Right 
GlobalData["MinRVP"] = Min["V(outr+high)"] + Min["V(outr+mediums)"] + Min["V(out+bass)"]
GlobalData["MinRPP"] = Min["P(outr+high)"] + Min["P(outr+mediums)"] + Min["P(out+bass)"]
GlobalData["MinRVN"] = Min["V(outr-high)"] + Min["V(outr-mediums)"] + Min["V(out-bass)"]
GlobalData["MinRPN"] = Min["P(outr-high)"] + Min["P(outr-mediums)"] + Min["P(out-bass)"]
# Left 
GlobalData["MinLVP"] = Min["V(outl+high)"] + Min["V(outl+mediums)"] + Min["V(out+bass)"]
GlobalData["MinLPP"] = Min["P(outl+high)"] + Min["P(outl+mediums)"] + Min["P(out+bass)"]
GlobalData["MinLVN"] = Min["V(outl-high)"] + Min["V(outl-mediums)"] + Min["V(out-bass)"]
GlobalData["MinLPN"] = Min["P(outl-high)"] + Min["P(outl-mediums)"] + Min["P(out-bass)"]

# Global Minimums for audio response
# Right 
GlobalData["MaxRVP"] = Max["V(outr+high)"] + Max["V(outr+mediums)"] + Max["V(out+bass)"]
GlobalData["MaxRPP"] = Max["P(outr+high)"] + Max["P(outr+mediums)"] + Max["P(out+bass)"]
GlobalData["MaxRVN"] = Max["V(outr-high)"] + Max["V(outr-mediums)"] + Max["V(out-bass)"]
GlobalData["MaxRPN"] = Max["P(outr-high)"] + Max["P(outr-mediums)"] + Max["P(out-bass)"]
# Left 
GlobalData["MaxLVP"] = Max["V(outl+high)"] + Max["V(outl+mediums)"] + Max["V(out+bass)"]
GlobalData["MaxLPP"] = Max["P(outl+high)"] + Max["P(outl+mediums)"] + Max["P(out+bass)"]
GlobalData["MaxLVN"] = Max["V(outl-high)"] + Max["V(outl-mediums)"] + Max["V(out-bass)"]
GlobalData["MaxLPN"] = Max["P(outl-high)"] + Max["P(outl-mediums)"] + Max["P(out-bass)"]

# Global Medians for audio response
# Right 
GlobalData["MedianRVP"] = Mean["V(outr+high)"] + Mean["V(outr+mediums)"] + Mean["V(out+bass)"]
GlobalData["MedianRPP"] = Mean["P(outr+high)"] + Mean["P(outr+mediums)"] + Mean["P(out+bass)"]
GlobalData["MedianRVN"] = Mean["V(outr-high)"] + Mean["V(outr-mediums)"] + Mean["V(out-bass)"]
GlobalData["MedianRPN"] = Mean["P(outr-high)"] + Mean["P(outr-mediums)"] + Mean["P(out-bass)"]
# Left 
GlobalData["MedianLVP"] = Mean["V(outl+high)"] + Mean["V(outl+mediums)"] + Mean["V(out+bass)"]
GlobalData["MedianLPP"] = Mean["P(outl+high)"] + Mean["P(outl+mediums)"] + Mean["P(out+bass)"]
GlobalData["MedianLVN"] = Mean["V(outl-high)"] + Mean["V(outl-mediums)"] + Mean["V(out-bass)"]
GlobalData["MedianLPN"] = Mean["P(outl-high)"] + Mean["P(outl-mediums)"] + Mean["P(out-bass)"]

# Standard deviations
# Right 
GlobalData["STDRVP"] = STD["V(outr+high)"] + STD["V(outr+mediums)"] + STD["V(out+bass)"]
GlobalData["STDRVN"] = STD["P(outr+high)"] + STD["P(outr+mediums)"] + STD["P(out+bass)"]
GlobalData["STDRPP"] = STD["V(outr-high)"] + STD["V(outr-mediums)"] + STD["V(out-bass)"]
GlobalData["STDRPN"] = STD["P(outr-high)"] + STD["P(outr-mediums)"] + STD["P(out-bass)"]
# Left 
GlobalData["STDLVP"] = STD["V(outl+high)"] + STD["V(outl+mediums)"] + STD["V(out+bass)"]
GlobalData["STDLVN"] = STD["P(outl+high)"] + STD["P(outl+mediums)"] + STD["P(out+bass)"]
GlobalData["STDLPP"] = STD["V(outl-high)"] + STD["V(outl-mediums)"] + STD["V(out-bass)"]
GlobalData["STDLPN"] = STD["P(outl-high)"] + STD["P(outl-mediums)"] + STD["P(out-bass)"]

# Global STD
# Right 
GlobalData["STDVRP"] = GlobalData["MedianRVP"] + GlobalData["STDRVP"]
GlobalData["STDVRN"] = GlobalData["MedianRVN"] - GlobalData["STDRVN"]
GlobalData["STDPRP"] = GlobalData["MedianRPP"] + GlobalData["STDRPP"]
GlobalData["STDPRN"] = GlobalData["MedianRPN"] - GlobalData["STDRPN"]
# Left 
GlobalData["STDVLP"] = GlobalData["MedianLVP"] + GlobalData["STDLVP"]
GlobalData["STDVLN"] = GlobalData["MedianLVN"] - GlobalData["STDLVN"]
GlobalData["STDPLP"] = GlobalData["MedianLPP"] + GlobalData["STDLPP"]
GlobalData["STDPLN"] = GlobalData["MedianLPN"] - GlobalData["STDLPN"]
print("Done !")
cutf = time.time()

# =====================================================================================================================
# MATPLOTLIB
# =====================================================================================================================
DATA = GlobalData.to_pandas()

plt.plot(DATA['Frequency'], DATA['MinRVP'], color='#e72900', label='Absolute maximums')
plt.plot(DATA['Frequency'], DATA['MaxRVP'], color='#0031e7', label='Absolute minimums')
plt.plot(DATA['Frequency'], DATA['MedianRVP'], color='#e7a500', label='Median')
plt.xlabel("Frequency (Hz)")
plt.ylabel("Amplitude (dB)")
plt.title("Right positive output response")
plt.legend()
plt.show()


input("Press enter to exit...")
print(f"Time elapsed (computing only) : {cutf - cuts}")
