import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import math
import sys
import functools

plt.figure(figsize=(6,6))

WINDOW_SCALE = 0.4
COLOR_MAPS = ['viridis', 'plasma', 'inferno', 'magma', 'cividis','spring', 
              'summer', 'autumn', 'winter', 'cool', 'Wistia']

def evalLine(slope, intercept, x):
    return slope * x + intercept

def plotPoint(pair,color='blue'):
    x,y = pair
    plt.scatter([x],[y],color=color,marker="D")

def getTheta(x,y):
    """Gets the angle IN DEGREES between origin and (x,y)"""
    if x == 0:
        return 90 + 180*(y < 0)
    elif y == 0:
        return 180 * (x < 0)
    elif x>0 and y>0: #q1
        return np.degrees(np.arctan(y/x))
    elif x < 0 and y>0: #q2
        return np.degrees(np.arctan(y/x)) + 180
    elif x < 0 and y <0:
        return np.degrees(np.arctan(y/x)) + 180
    else: 
        return np.degrees(np.arctan(y/x)) % 360
    
def rotatePoint(x,y,phi):
    """Rotates the point x,y an angle of phi degrees around the origin"""
    if phi == 0:
        return (x,y)
    else:
        m = math.dist([0,0], [x,y])
        theta = getTheta(x,y)
        newAngle = np.deg2rad((theta + phi)%360)
        return (m*np.cos(newAngle), m*np.sin(newAngle))

def transpose(center_x, center_y, x,y):
    return x-center_x, y-center_y

points = []
toplines = []
inputstr = sys.stdin.readlines()
toplines = inputstr[0].split('|')
points = inputstr[1].split('|')
all_lines = inputstr[2:]
all_lines = list(map(eval, all_lines))

toplines = [eval(l.strip()) for l in toplines[:-1]]
points = [eval(p.strip()) for p in points[:-1]]

# Plot Points
x_s = [p[0] for p in points]
y_s = [p[1] for p in points]

# Center
center_x, center_y = (np.average(x_s), np.average(y_s))

plt.scatter([0], [0], marker='D', color='midnightblue')

# Use currying to create a transposition function
transposex = functools.partial(transpose, center_x)
transposePoints = functools.partial(transposex, center_y)

transposedPts = list(map(transposePoints, [x_s], [y_s]))

# Rotate!
colors = ['red', 'blue', 'cyan']

# x_s = [p[0] for p in transposedPts]
# y_s = [p[1] for p in transposedPts]
x_s,y_s = transposedPts[0]
for rotation in range(3): #60 deg
    for x,y in zip(x_s,y_s):
        plotPoint(rotatePoint(x,y,60*rotation),colors[rotation])

#Get window parameters and expand
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

for rotation in range(3):
    # print(rotation)
    for (slope, intercept) in all_lines:
        y1 = evalLine(slope, intercept, x_min)
        y2 = evalLine(slope, intercept, x_max)
        x1,y1 = transposePoints(x_min, y1)
        x2,y2 = transposePoints(x_max, y2)
        x1_r,y1_r = rotatePoint(x1,y1,rotation*60)
        x2_r,y2_r = rotatePoint(x2,y2,rotation*60)
        # print(f" Plotting from x {x1_r} to {x2_r}")
        plt.plot([x1_r,x2_r], [y1_r,y2_r],color = "black", linewidth=0.5)
    # print(all_lines)
plt.show()