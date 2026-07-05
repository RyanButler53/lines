import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np


WINDOW_SCALE = 0.4

COLOR_MAPS = ['viridis', 'plasma', 'inferno', 'magma', 'cividis','spring', 
              'summer', 'autumn', 'winter', 'cool', 'Wistia']

def plotTrails(toplines, all_lines, cmap, filename ):

    if cmap == "random":
        cmap = np.random.choice(COLOR_MAPS) # chooses to random color map
    elif cmap not in COLOR_MAPS:
        print(f"{cmap} is not a valid color map.\nPick one of {COLOR_MAPS} colormaps")
        print("Picking a random color map")
        cmap = np.random.choice(COLOR_MAPS) # chooses to random color map

    def evalLine(slope, intercept, x):
        return slope * x + intercept

    allToplines = []
    allPoints = []

    # Resize Figure
    plt.figure(figsize=(9,9))

    # Input string alternates between lines and points
    for topline in toplines:

        points = topline.points
        lines = topline.lines
        
        allToplines.append(lines)
        allPoints.append(points)

        x_s = [p.x.to_float() for p in points]
        y_s = [p.y.to_float() for p in points]
        # do all plotting

        plt.scatter(x_s, y_s, marker=".",color='black')

    # Get Colors
    color_x =np.linspace(0.0, 1.0, len(toplines))
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
    for l in all_lines:
        slope = l.slope.to_float()
        intercept = l.intercept.to_float()
        y1 = evalLine(slope, intercept, x_min)
        y2 = evalLine(slope, intercept, x_max)
        plt.plot([x_min,x_max], [y1,y2], color = "black", linewidth=0.5)

    # Plot Top Lines
    # Toplines and points are all as FRACTION TYPES
    for lines, points,c in zip(allToplines, allPoints, colors):
        for i in range(len(points)-1):
            cur = points[i]
            next = points[i+1]
            plt.plot([cur.x.to_float(),next.x.to_float()], [cur.y.to_float(),next.y.to_float()], linestyle ="dashed", color=c, linewidth=3)

        # Start and end segments. Run along the first topline from x_min to points[0]
        y_start = evalLine(lines[0].slope.to_float(), lines[0].intercept.to_float(), x_min) 
        plt.plot([x_min,points[0].x.to_float()],[y_start,points[0].y.to_float()],color = c, linewidth=3)

        y_end = evalLine(lines[-1].slope.to_float(), lines[-1].intercept.to_float(), x_max)
        plt.plot([points[-1].x.to_float(),x_max],[points[-1].y.to_float(),y_end],color = c, linewidth=3)

    # Clean up figure and save
    ax.set_axis_off()
    plt.tight_layout()
    plt.savefig(filename)
