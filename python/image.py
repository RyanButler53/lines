# Visualize the intersecting lines

import matplotlib.pyplot as plt
import numpy as np
import py_lines as pl
# import sys

WINDOW_SCALE = 0.4

def evalLine(slope, intercept, x):
    return slope * x + intercept

def plot(toplines:pl.toplines, all_lines):

    # Lines on top, points on top, All lines
    lines = toplines.lines
    points = toplines.points

    # Plot Top Points
    x_s = [p.x.to_float() for p in points]
    y_s = [p.y.to_float() for p in points]

    plt.scatter(x_s, y_s, marker="o", color='black')

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
    for l in all_lines:
        y1 = evalLine(l.slope.to_float(), l.intercept.to_float(), x_min)
        y2 = evalLine(l.slope.to_float(), l.intercept.to_float(), x_max)
        plt.plot([x_min,x_max], [y1,y2],color = "black", linewidth=0.5)

    # Draw Dotted red line over top lines
    for i in range(len(points)-1):
        cur = points[i]
        next = points[i+1]
        plt.plot([cur.x.to_float(),next.x.to_float()], [cur.y.to_float(),next.y.to_float()], "r--", linewidth=2)

    # Start and end segments. Run along the first topline from x_min to points[0]
    y_start = evalLine(lines[0].slope.to_float(), lines[0].intercept.to_float(), x_min) 
    plt.plot([x_min,points[0].x.to_float()],[y_start,points[0].y.to_float()],color = "red", linewidth=2)

    y_end = evalLine(lines[-1].slope.to_float(), lines[-1].intercept.to_float(), x_max)
    plt.plot([points[-1].x.to_float(),x_max],[points[-1].y.to_float(),y_end],color = "red", linewidth=2)

    plt.tight_layout()
    plt.savefig("./figure1.png")

# Plot the "trails" system
