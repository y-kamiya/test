import os
import time
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from pygame import mixer

FREQ = 261.626  # note#60 C4
SAMPLE_RATE = 44100
DATAROOT = "data"
T = 1

filepath = os.path.join(DATAROOT, "do.wav")

t = np.arange(SAMPLE_RATE * T) / SAMPLE_RATE
wave = np.sin(2 * np.pi * FREQ * t) * 32767.0

wavfile.write(filepath, SAMPLE_RATE, wave.astype(np.int16))

mixer.init()
mixer.music.load(filepath)
mixer.music.play(T)

plt.plot(wave[:500])
plt.show()

