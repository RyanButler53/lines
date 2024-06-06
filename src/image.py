# Visualize the intersecting lines

import matplotlib.pyplot as plt
import numpy as np
import sys

WINDOW_SCALE = 0.4

def evalLine(slope, intercept, x):
    return slope * x + intercept


points = []
toplines = []
inputstr = sys.stdin.readlines()
toplines = inputstr[0].split('|')
points = inputstr[1].split('|')
all_lines = inputstr[2:]
all_lines = map(eval, all_lines)

toplines = [eval(l.strip()) for l in toplines[:-1]]
points = [eval(p.strip()) for p in points[:-1]]

# Plot Points
x_s = [p[0] for p in points]
y_s = [p[1] for p in points]

plt.scatter(x_s, y_s, marker="o",color='black')

# Get window parameters and expand
ax = plt.gca()
y_lim = ax.get_ylim()
x_lim = ax.get_xlim()
((x_min, x_max), (y_min, y_max)) = (x_lim, y_lim)
lim_arr = np.array([x_min, x_max, y_min, y_max])
change =  np.average(abs(WINDOW_SCALE*lim_arr))

x_min = x_lim[0] - change
x_max = x_lim[1] + change
y_min = y_lim[0] - 10*change # 10-15 gets good images
y_max = y_lim[1] + 10*change

ax.set_xlim([x_min, x_max])
ax.set_ylim([y_min, y_max])

#Draw all lines

for (slope, intercept) in all_lines:
    y1 = evalLine(slope, intercept, x_min)
    y2 = evalLine(slope, intercept, x_max)

    plt.plot([x_min,x_max], [y1,y2],color = "black", linewidth=0.5)

for i in range(len(points)-1):
    x,y = points[i]
    next_x,next_y = points[i+1]
    plt.plot([x,next_x], [y,next_y], "r--", linewidth=2)

# Start and end segments. Run along the first topline from x_min to points[0]
y_start = evalLine(toplines[0][0], toplines[0][1], x_min) 
plt.plot([x_min,points[0][0]],[y_start,points[0][1]],color = "red", linewidth=2)

y_end = evalLine(toplines[-1][0], toplines[-1][1], x_max)
plt.plot([points[-1][0],x_max],[points[-1][1],y_end],color = "red", linewidth=2)

plt.tight_layout()
plt.savefig("images/figure1.png")
