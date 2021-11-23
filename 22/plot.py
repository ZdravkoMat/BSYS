#! /usr/bin/env python3

import matplotlib.pyplot as plt

x = [1, 2, 3, 4]    
y = [51.04, 81.35, 91.53, 95.36] 
y2 = [51.04, 87.02, 93.33, 96.57]
y3 = [50.55, 50.80, 52.61, 52.75]
y4 = [51.04, 87.26, 95.21, 97.68]
y5 = [51.04, 81.51, 91.02, 95.08]
y6 = [51.04, 83.13, 92.15, 95.80]
plt.plot(x, y, 'b', label='FIFO', linestyle="dotted")
plt.plot(x, y2, 'r', label='LRU', linestyle="dashed")
plt.plot(x, y3, 'y', label='MRU', linestyle="dashdot")
plt.plot(x, y4, 'g', label='OPT', linestyle="solid")
plt.plot(x, y5, 'y', label='RAND', linestyle="dashdot")
plt.plot(x, y6, '', label='CLOCK', linestyle="solid")
plt.title('Swapping')    
fig = plt.figure()    
plt.ylabel('Hit Rate')    
plt.xlabel('Cache Size')    
  
plt.show()  