from __future__ import annotations

import numpy as np
import pyaudio
import matplotlib.pyplot as plt

SAMPLE_RATE = 44100


def note2wave(note_id: int, duration: float) -> np.array:
    freq = 440.0 * 2 ** ((note_id - 69) / 12)
    t = np.arange(SAMPLE_RATE * duration) / SAMPLE_RATE
    wave = np.sin(2 * np.pi * freq * t)

    fade_len = min(100, wave.size)
    slope = (np.arange(fade_len) - 1) / fade_len
    wave[:fade_len] = wave[:fade_len] * slope

    slope = ((fade_len - 1) - np.arange(fade_len)) / fade_len
    wave[-fade_len:] = wave[-fade_len:] * slope

    return wave


name2id = {}
id = 0
for octave_id in range(-1, 10):
    for name in ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]:
        name2id[f"{name}{octave_id}"] = id
        id += 1


def name2wave(name: str, duration: float) -> np.array:
    note_id: int = 0
    if name in name2id:
        note_id = name2id[name]

    return note2wave(note_id, duration)


def mix(tracks: list[np.array]) -> np.array:
    if len(tracks) == 0:
        return None
    if len(tracks) == 1:
        return tracks[0]

    max_len = max(*[len(t) for t in tracks])
    for i, t in enumerate(tracks):
        if len(t) < max_len:
            tracks[i] = np.pad(t, (0, max_len - len(t)))

    return np.vstack(tracks).mean(axis=0)


p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paFloat32, channels=1, rate=SAMPLE_RATE, frames_per_buffer=1024, output=True)

track1 = np.concatenate([
    name2wave("C4", 0.3),
    name2wave("D4", 0.3),
    name2wave("E4", 0.3),
    name2wave("F4", 0.3),
    name2wave("G4", 0.3),
])
track2 = np.concatenate([
    name2wave("dummy", 0.3),
    name2wave("F4", 0.3),
    name2wave("G4", 0.3),
    name2wave("A4", 0.3),
    name2wave("B4", 0.3),
])
track3 = np.concatenate([
    name2wave("dummy", 0.3),
    name2wave("dummy", 0.3),
    name2wave("B4", 0.3),
    name2wave("C5", 0.3),
    name2wave("D5", 0.3),
])
track = mix([track1, track2,  track3])

stream.write(track.astype(np.float32).tostring())

# t = track.size // 3
# plt.plot(track[t-500:t+500])
# plt.show()

stream.close()
p.terminate()
