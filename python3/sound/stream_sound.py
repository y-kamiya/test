import numpy as np
import pyaudio

FREQ = 261.626  # note#60 C4
SAMPLE_RATE = 44100
DATAROOT = "data"
T = 1


def play(s: pyaudio.Stream, freq: float, duration: float):
    t = np.arange(SAMPLE_RATE * duration) / SAMPLE_RATE
    wave = np.sin(2 * np.pi * freq * t)
    s.write(wave.astype(np.float32).tostring())


p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paFloat32, channels=1, rate=SAMPLE_RATE, frames_per_buffer=1024, output=True)

play(stream, 261.626, 0.3)  # note#60 C4 ド
play(stream, 329.628, 0.3)  # note#64 E4 ミ
play(stream, 391.995, 0.3)  # note#67 G4 ソ
play(stream, 523.251, 0.6)  # note#72 C5 ド

stream.close()
p.terminate()
