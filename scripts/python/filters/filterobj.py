# Define a standard filterobj class, which will be used to define the filters
import numpy as np
import scipy.signal as signal

class filterobj:

    def __init__(
        self,
        type: str = "none",
        central: float = 0.0,
        width: float = 0.0,
        fs: int = 0,
        Q: float = 0.0,
        G: float = 0.0,
        order: int = 4
    ) -> None:
        self.type = type
        self.central: float = float(central)
        self.width: float = float(width)
        self.sample_rate: int = int(fs)
        self.quality: float = float(Q)
        self.gain: float = float(G)
        self.order = order

        self.low = ((self.central * 2) - self.width) / 2
        self.high = (self.central * 2) - self.low

        self.filters = []

        return

    def define(
        self,
        type: str,
        low: float = 0.0,
        high: float = 0.0,
        fs: int = 0,
        Q: float = 0.0,
        G: float = 0.0,
        order: int = 4
    ) -> int:
        """
        Define the filter from other specs than the default constructor
        """

        if low > high:
            return -1

        if type not in ["lowpass", "highpass", "bandpass"," bandstop"]:
            return -2

        self.type = type
        self.quality = float(Q)
        self.gain = float(G)
        self.sample_rate = int(fs)
        self.central = (low + high) / 2
        self.width = high - low
        self.low = low
        self.high = high
        self.order = order

        return 0

    def compute(self) -> int:
        """
        Compute the filter coefficients.
        """

        if self.type == "lowpass":
            cutoff = self.low
        elif self.type == "highpass":
            cutoff = self.high
        elif self.type in ["bandpass", "bandstop"]:
            cutoff = [self.low, self.high]
        else:
            return -1

        sos = signal.butter(N=self.order, Wn=cutoff, btype=self.type, fs=self.sample_rate, output='sos')

        for section in sos:
            b0, b1, b2, a0, a1, a2 = section

            # To add here : normalize over the standard format !!

            filt_struct = {
                'b': [b0/a0, b1/a0, b2/a0],
                'a': [1.0,   a1/a0, a2/a0], # a0 is now 1.0
                'type': self.type,
                'fc': cutoff
            }
            self.filters.append(filt_struct)

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
        Coeffs =            {self.filters}
"""
        )
