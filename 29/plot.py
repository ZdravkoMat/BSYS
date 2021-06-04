#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

sloppy = [1.341011, 0.866801, 0.735667, 0.628627, 0.573996, 0.550160, 0.535955, 0.533551, 0.526000, .517421, 00.520576]
a = np.arange(0, 11)
s = 2 ** a

plt.plot(a, sloppy, marker='x')
plt.margins(0)
plt.xticks(a, s)
plt.xlabel('Threshold (8 Threads)')
plt.ylabel('Time (seconds)')
plt.savefig('sloppy.png', dpi=300)
plt.show()