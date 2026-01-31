import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt
import tomllib
import pprint

from filterobj import filterobj


def get_filters(data: dict) -> tuple[list, list, list, list]:

    # Create filters
    EQ = []
    CROSSOVER_BASS = []
    CROSSOVER_MEDIUM = []
    CROSSOVER_HIGH = []

    for index1, fs in enumerate(data["EQ"]["sample_rate"]):
        EQ.append([])

        for index2, band in enumerate(data["EQ"]["freqs"]):
            tmp = filterobj()
            tmp.define(
                "peaking", band[0], band[1], fs, 0.707, data["EQ"]["gain"][index2]
            )
            tmp.compute()
            EQ[index1].append(tmp)

    for index1, fs in enumerate(data["CROSSOVER"]["BASS"]["sample_rate"]):
        CROSSOVER_BASS.append([])
        tmp = filterobj()
        tmp.define(
            "highpass",
            data["CROSSOVER"]["BASS"]["freqs"][0],
            data["CROSSOVER"]["BASS"]["freqs"][0],
            fs,
            0.707,
            0.0,
        )
        tmp.compute()
        CROSSOVER_BASS[index1].append(tmp)

        tmp = filterobj()
        tmp.define(
            "lowpass",
            data["CROSSOVER"]["BASS"]["freqs"][1],
            data["CROSSOVER"]["BASS"]["freqs"][1],
            fs,
            0.707,
            0.0,
        )
        tmp.compute()
        CROSSOVER_BASS[index1].append(tmp)

    for index1, fs in enumerate(data["CROSSOVER"]["MEDIUM"]["sample_rate"]):
        CROSSOVER_MEDIUM.append([])
        tmp = filterobj()
        tmp.define(
            "highpass",
            data["CROSSOVER"]["MEDIUM"]["freqs"][0],
            data["CROSSOVER"]["MEDIUM"]["freqs"][0],
            fs,
            0.707,
            0.0,
        )
        tmp.compute()
        CROSSOVER_MEDIUM[index1].append(tmp)

        tmp = filterobj()
        tmp.define(
            "lowpass",
            data["CROSSOVER"]["MEDIUM"]["freqs"][1],
            data["CROSSOVER"]["MEDIUM"]["freqs"][1],
            fs,
            0.707,
            0.0,
        )
        tmp.compute()
        CROSSOVER_MEDIUM[index1].append(tmp)

    for index1, fs in enumerate(data["CROSSOVER"]["HIGH"]["sample_rate"]):
        CROSSOVER_HIGH.append([])
        tmp = filterobj()
        tmp.define(
            "highpass",
            data["CROSSOVER"]["HIGH"]["freqs"][0],
            data["CROSSOVER"]["HIGH"]["freqs"][0],
            fs,
            0.707,
            0.0,
        )
        tmp.compute()
        CROSSOVER_HIGH[index1].append(tmp)

        tmp = filterobj()
        tmp.define(
            "lowpass",
            data["CROSSOVER"]["HIGH"]["freqs"][1],
            data["CROSSOVER"]["HIGH"]["freqs"][1],
            fs,
            0.707,
            0.0,
        )
        tmp.compute()
        CROSSOVER_HIGH[index1].append(tmp)

    return EQ, CROSSOVER_BASS, CROSSOVER_MEDIUM, CROSSOVER_HIGH


# Function to convert Complex H -> Decibels
def to_db(h):
    return 20 * np.log10(np.abs(h) + 1e-12)


if __name__ == "__main__":
    data = None

    with open("params.toml", "rb") as f:
        data = tomllib.load(f)

    EQ, CROSSOVER_BASS, CROSSOVER_MEDIUM, CROSSOVER_HIGH = get_filters(data)

    # Creating frequency space
    freqs = np.logspace(1, np.log10(CROSSOVER_BASS[0][0].sample_rate / 2), 1000)
    w_rad = 2 * np.pi * freqs / CROSSOVER_BASS[0][0].sample_rate

    _, h = signal.freqz(
        CROSSOVER_BASS[0][0].coeff_b, CROSSOVER_BASS[0][0].coeff_a, worN=w_rad
    )
    _, h2 = signal.freqz(
        CROSSOVER_BASS[0][1].coeff_b, CROSSOVER_BASS[0][1].coeff_a, worN=w_rad
    )

    h_tot = h * h2

    plt.figure(figsize=(12, 8))

    plt.semilogx(freqs, to_db(h_tot), label="Woofer Total", color="blue", linewidth=2)

    # Styling
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Amplitude [dB]")
    plt.grid(which="both", linestyle="-", alpha=0.5)
    plt.legend()
    plt.xlim(20, 20000)

    plt.show()
