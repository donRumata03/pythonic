import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import colors as mclr
import json

IN_FILE_PATH = r"D:\pythonic\plotting\plot_data.json"


def my_key(a):
    return a[0]


file_data = open(IN_FILE_PATH, "rb").read().decode("utf-8")
# file_data = open(IN_FILE_PATH, "r").read()

open(r"D:\pythonic\plotting\temp.json", "wb").write(file_data.encode("utf-8"))

raw_data = json.loads(file_data)
data = raw_data["plots"]

# print(data)

fig, ax = plt.subplots()

someone_has_name = False
log_x: bool = raw_data["log_x"]
log_y: bool = raw_data["log_y"]
for plot in data:
    color = plot["color"]
    points = plot["data"]  # [(float(str.replace(x, ",", ".")), float(str.replace(y, ",", "."))) for (x, y) in plot["data"]]
    sorting = plot["sorting"]
    plot_type = plot["type"]
    plot_name = plot["name"] if "name" in plot else None

    kw_params = {}
    if color != "default":
        kw_params["color"] = color
    if plot_name is not None:
        someone_has_name = True
        kw_params["label"] = plot_name

    if sorting:
        points.sort(key=my_key)
    xs = []
    ys = []
    for point in points:
        xs.append(point[0])
        ys.append(point[1])

    if plot_type in { "scatter", "points" }:
        plt.scatter(xs, ys, **kw_params)
    else:
        plt.plot(xs, ys, **kw_params)

if someone_has_name:
    legend = ax.legend(shadow=True)

if log_x:
    ax.set_xscale("log")
if log_y:
    ax.set_yscale("log")

if "output_filename" in raw_data:
    # print(raw_data["output_filename"])
    fig = plt.gcf()
    fig.set_size_inches(16, 9)
    plt.savefig(raw_data["output_filename"])
else:
    plt.show()

