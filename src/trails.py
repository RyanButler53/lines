import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import sys

WINDOW_SCALE = 0.4

COLOR_MAPS = ['viridis', 'plasma', 'inferno', 'magma', 'cividis','spring', 
              'summer', 'autumn', 'winter', 'cool', 'Wistia']

# Color Scheme, Retain script only compatibility
cmap = sys.argv[1]
if cmap == "random":
    cmap = np.random.choice(COLOR_MAPS) #chooses to random color map
elif cmap not in COLOR_MAPS:
    print(f"{cmap} is not a valid color map.\nPick one of {COLOR_MAPS} colormaps")
    print("Picking a random color map")
    cmap = np.random.choice(COLOR_MAPS) #chooses to random color map

filename = 'images/trails.png'
if len(sys.argv)== 3:
    filename = sys.argv[2]

def evalLine(slope, intercept, x):
    return slope * x + intercept

inputStr = sys.stdin.readlines()
numTrails = int(inputStr[0])
allToplines = []
allPoints = []

# Resize Figure
plt.figure(figsize=(9,9))

# Input string alternates between lines and points
for trail_i in range(1, numTrails * 2, 2):
    lines = inputStr[trail_i].split('|')
    pts = inputStr[trail_i+1].split('|')

    toplines = [eval(l.strip()) for l in lines[:-1]]
    points = [eval(p.strip()) for p in pts[:-1]]
    
    allToplines.append(toplines)
    allPoints.append(points)

    x_s = [p[0] for p in points]
    y_s = [p[1] for p in points]
    # do all plotting

    plt.scatter(x_s, y_s, marker=".",color='black')

# Get Colors
color_x =np.linspace(0.0, 1.0, numTrails)
colors = mpl.colormaps[cmap](color_x)

# Expand Axes
ax = plt.gca()
y_lim = ax.get_ylim()
x_lim = ax.get_xlim()
((x_min, x_max), (y_min, y_max)) = (x_lim, y_lim)
lim_arr = np.array([x_min, x_max, y_min, y_max])
change =  np.average(abs(WINDOW_SCALE*lim_arr))

x_min = x_lim[0] - change
x_max = x_lim[1] + change
y_min = y_lim[0] - 30*change
y_max = y_lim[1] + 30*change
    
ax.set_xlim([x_min, x_max])
ax.set_ylim([y_min, y_max])

# Plot All Lines
allLines = inputStr[(2*numTrails+1):]
allLines = map(eval, allLines)
for (slope, intercept) in allLines:
    y1 = evalLine(slope, intercept, x_min)
    y2 = evalLine(slope, intercept, x_max)
    plt.plot([x_min,x_max], [y1,y2],color = "black", linewidth=0.5)

# Plot Top Lines
for toplines, pts,c in zip(allToplines, allPoints, colors):
    for i in range(len(pts)-1):
        x,y = pts[i]
        next_x,next_y = pts[i+1]
        plt.plot([x,next_x], [y,next_y], linestyle = "dashed", color=c, linewidth=3)

    # Start and end lines
    y_start = evalLine(toplines[0][0], toplines[0][1], x_min) 
    plt.plot([x_min, pts[0][0]], [y_start, pts[0][1]], color=c, linewidth=3)

    y_end = evalLine(toplines[-1][0], toplines[-1][1], x_max)
    plt.plot([pts[-1][0], x_max], [pts[-1][1], y_end], color=c, linewidth=3)

# Clean up figure and save
ax.set_axis_off()
plt.tight_layout()
plt.savefig(filename)
