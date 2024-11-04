# ===============================================================================
# Filter.py
# Tool to do calculation for us when designing and tuning filters !
# Wrote by lheywang on october 2024.
# ===============================================================================

from pick import pick  # type: ignore (Vscode error here due to local packages...)
import math

if __name__ == "__main__":
    # First, job selection !
    title = "Select your mission !"
    options = ["Design a filter", "Identify a filter"]

    job, jindex = pick(options, title)

    match (jindex):
        # Design a filter
        case 0:
            # Selection of the type
            title = "Which type of filter you want to design ?"
            options = ["Low pass", "High pass", "Band pass"]
            ftype, findex = pick(options, title)

            # Selection of the topology
            title = "Which topology do you want to use ?"
            options = [
                "RC (1st order)",
                "Sallen-Key (2nd order)",
                "Multiple Feedback (2nd order)",
            ]
            ftopo, ftindex = pick(options, title)

            if (ftindex < 1) and (findex > 1):
                print(
                    "Unable to design band filter with a simple RC ! Please select a second order filter at least !"
                )
                exit(-1)

            while True:
                try:
                    CF = float(input("Please enter a reference capacitor (nF) : "))

                    if ftindex > 0:
                        F = float(
                            input(
                                "Please enter the cutoff frequency (or the central frequency) : "
                            )
                        )
                        K = float(input("Please enter the gain of the system : "))
                        Q = float(
                            input("Please enter the quality factor of the filter : ")
                        )

                    if ftindex == 1:
                        RF = float(input("Enter a reference resistor : "))

                    break
                except KeyboardInterrupt:
                    exit(-2)
                except:
                    print("Unable to parse values ! Please retry !")

            if ftindex == 0:
                R = 1 / (2 * math.pi * CF)
                print(f"You need a {R} Ohm resistor to match your criterias !")

            # Quality factor
            alpha = 1 / Q
            CF = CF * 0.000000001  # nF
            PrintFactor = 1000000000  # opposite operation

            match (findex):
                # Low pass
                case 0:
                    # Sallen Key
                    if ftindex == 1:
                        k = 2 * math.pi * F * CF
                        m = (alpha**2) / 4 + (K - 1)

                        R4 = RF / (K - 1)
                        C2 = m * CF
                        R1 = 2 / (alpha * k)
                        R2 = alpha / (2 * m * k)

                        print(
                            "The designed filter shall use theses values (SHiwed according MT222 from Analog Devices representation)"
                        )
                        print(f"R1 = {R1} Ohms")
                        print(f"R2 = {R2} Ohms")
                        print(f"R4 = {R4} Ohms")
                        print(f"C2 = {C2 * PrintFactor} nF")
                        print("And for reminder, you enterred theses values :")
                        print(f"R3 = {RF} Ohms")
                        print(f"C1 = {CF * PrintFactor} nF")

                    # MFB
                    if ftindex == 2:
                        k = 2 * math.pi * F * CF

                        C2 = (4 / (alpha**2)) * (K + 1) * CF
                        R1 = alpha / (2 * K * k)
                        R3 = alpha / (2 * (K + 1) * k)
                        R4 = alpha / (2 * k)

                        print(
                            "The designed filter shall use theses values (SHiwed according MT220 from Analog Devices representation)"
                        )
                        print(f"R1 = {R1} Ohms")
                        print(f"R3 = {R3} Ohms")
                        print(f"R4 = {R4} Ohms")
                        print(f"C2 = {C2 * PrintFactor} nF")
                        print("And for reminder, you enterred theses values :")
                        print(f"C5 = {CF * PrintFactor} nF")

                # High pass
                case 1:
                    # Sallen Key
                    if ftindex == 1:
                        k = 2 * math.pi * F * CF

                        C2 = CF
                        R1 = (alpha + math.sqrt(alpha**2 + (K - 1))) / (4 * k)
                        R2 = (4 / (alpha + math.sqrt(alpha**2 + (K - 1)))) + 1 / k
                        if K != 1:
                            R4 = RF / (K - 1)
                        else:
                            R4 = 0

                        print(
                            "The designed filter shall use theses values (SHiwed according MT222 from Analog Devices representation)"
                        )
                        print(f"R1 = {R1} Ohms")
                        print(f"R2 = {R2} Ohms")
                        print(f"R4 = {R4} Ohms")
                        if R4 == 0:
                            print(
                                f"Due to K = 1 requirement, please ensure also R3 = 0. Values are already computed with it."
                            )
                        print(f"C2 = {C2 * PrintFactor} nF")
                        print("And for reminder, you enterred theses values :")
                        print(f"R3 = {RF} Ohms")
                        print(f"C1 = {CF * PrintFactor} nF")

                    # MFB
                    if ftindex == 2:
                        k = 2 * math.pi * F * CF

                        C3 = CF
                        C4 = CF / K
                        R2 = alpha / (k * (2 + (1 / K)))
                        R5 = (K * (2 + (1 / K))) / (alpha * k)

                        print(
                            "The designed filter shall use theses values (SHiwed according MT220 from Analog Devices representation)"
                        )
                        print(f"R2 = {R2} Ohms")
                        print(f"R5 = {R5} Ohms")
                        print(f"C3 = {C3 * PrintFactor} nF")
                        print(f"C4 = {C4 * PrintFactor} nF")
                        print("And for reminder, you enterred theses values :")
                        print(f"C1 = {CF * PrintFactor} nF")

                # Band pass
                case 2:
                    # Sallen Key
                    if ftindex == 1:
                        k = 2 * math.pi * F * CF
                        C2 = CF
                        C2 = 0.5 * CF
                        R1 = 2 / k
                        R2 = 2 / (3 * k)
                        R3 = 4 / k
                        H = (1 / 3) * (6.5 - 1 / Q)

                        if K != 1:
                            R5 = RF / (K - 1)
                        else:
                            R5 = 0
                            R4 = 0

                        print(
                            "The designed filter shall use theses values (SHiwed according MT222 from Analog Devices representation)"
                        )
                        print(f"R1 = {R1} Ohms")
                        print(f"R2 = {R2} Ohms")
                        print(f"R3 = {R3} Ohms")
                        print(f"R5 = {R5} Ohms")
                        if R5 == 0:
                            print(
                                f"Due to K = 1 requirement, please ensure also R4 = 0. Values are already computed with it."
                            )
                        print(f"C2 = {C2 * PrintFactor} nF")
                        print(f"Adjusted gain value : {H}")
                        print("And for reminder, you enterred theses values :")
                        print(f"R4 = {RF} Ohms")
                        print(f"C1 = {CF * PrintFactor} nF")

                    # MFB
                    if ftindex == 2:
                        k = 2 * math.pi * F * CF

                        C4 = CF
                        H = K / Q
                        R1 = 1 / (H * k)
                        R2 = 1 / (k * (2 * Q - H))
                        R5 = (2 * Q) / k

                        print(
                            "The designed filter shall use theses values (SHiwed according MT220 from Analog Devices representation)"
                        )
                        print(f"R1 = {R1} Ohms")
                        print(f"R2 = {R2} Ohms")
                        print(f"R5 = {R5} Ohms")
                        print(f"C4 = {C4 * PrintFactor} nF")
                        print(f"Adjusted gain value at center frequency : {H}")
                        print("And for reminder, you enterred theses values :")
                        print(f"C3 = {CF * PrintFactor} nF")

        # Indentify a filter
        case 1:
            pass
