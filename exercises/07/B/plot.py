import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import itertools
from scipy import stats
import glob


df = pd.DataFrame(columns = ["name", "time"])
for file in glob.glob("*.time"):
    df_read = pd.read_csv(file, names=["time"])
    df_read["name"] = file[0:-5]
    print(df_read)
    df = pd.concat([df, df_read])

print(df)


df_2 = df[df.groupby(["name"])['time'].transform(stats.zscore).abs() < 3]
#
grouped = df_2.groupby(["name"]).mean().reset_index()
# grouped["text"] = ["$\mu=${0:.2f}\n$\sigma=${1:.2f}".format(mean,std) for mean,std in zip(grouped["mean"], grouped["std"])]

print(grouped)

grouped = grouped.sort_values(by="time")

# ylim = (data[prop].min() * 0.9, data[prop].min() * 1.1)
ax = grouped.plot.bar(x="name", rot=25, figsize=(10,8), log=True)
ax.bar_label(ax.containers[0])
plt.savefig("time_arenaalloc.png")
plt.show()

