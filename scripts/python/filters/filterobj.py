# Define a standard filterobj class, which will be used to define the filters
import numpy as np


class filterobj:

    def __init__(
        self,
        type: str = "none",
        central: float = 0.0,
        width: float = 0.0,
        fs: int = 0,
        Q: float = 0.0,
        G: float = 0.0,
    ) -> None:
        self.type = type
        self.central: float = float(central)
        self.width: float = float(width)
        self.sample_rate: int = int(fs)
        self.quality: float = float(Q)
        self.gain: float = float(G)

        self.coeff_a: list[float] = []
        self.coeff_b: list[float] = []

        return

    def define(
        self,
        type: str,
        low: float = 0.0,
        high: float = 0.0,
        fs: int = 0,
        Q: float = 0.0,
        G: float = 0.0,
    ) -> int:
        """
        Define the filter from other specs than the default constructor
        """

        if low > high:
            return -1

        if type not in ["lowpass", "highpass", "peaking"]:
            return -2

        self.type = type
        self.quality = float(Q)
        self.gain = float(G)
        self.sample_rate = int(fs)
        self.central = (low + high) / 2
        self.width = high - low

        return 0

    def compute(self) -> int:
        """
        Compute the filter coefficients.
        """

        A = 10 ** (self.gain / 40.0)
        w0 = 2 * np.pi * (self.central / self.sample_rate)

        cos_w0 = np.cos(w0)
        sin_w0 = np.sin(w0)

        alpha = sin_w0 / (2 * self.quality)

        match self.type:
            case "lowpass":
                a0 = 1 + alpha
                self.coeff_b = [
                    float(((1 - cos_w0) / 2) / a0),
                    float((1 - cos_w0) / a0),
                    float(((1 - cos_w0) / 2) / a0),
                ]
                self.coeff_a = [
                    float((a0) / a0),
                    float((-2 * cos_w0) / a0),
                    float((1 - alpha) / a0),
                ]

            case "highpass":
                a0 = 1 + alpha
                self.coeff_b = [
                    float(((1 + cos_w0) / 2) / a0),
                    float((1 + cos_w0) / a0),
                    float(((1 + cos_w0) / 2) / a0),
                ]
                self.coeff_a = [
                    float((a0) / a0),
                    float((-2 * cos_w0) / a0),
                    float((1 - alpha) / a0),
                ]

            case "peaking":
                a0 = 1 + alpha / A
                self.coeff_b = [
                    float((1 + alpha * A) / a0),
                    float((-2 * cos_w0) / a0),
                    float((1 - alpha * A) / a0),
                ]
                self.coeff_a = [
                    float((a0) / a0),
                    float((-2 * cos_w0) / a0),
                    float((1 - alpha / A) / a0),
                ]

            case _:
                self.coeff_b = [1.0, 0.0, 0.0]
                self.coeff_a = [1.0, 0.0, 0.0]

        return 0

    def show(self):
        print(
            f"""\
{__class__.__name__} (class) :
    Filter parameters : 
        Type =              {self.type}
        central frequency = {self.central:.3f}
        width =             {self.width:.3f}
        sample rate =       {self.sample_rate}
        filter quality =    {self.quality:.3f}
        filter gain =       {self.gain:.3f}

    Filter coefficients : 
        A =                 {self.coeff_a}
        B =                 {self.coeff_b}
"""
        )
