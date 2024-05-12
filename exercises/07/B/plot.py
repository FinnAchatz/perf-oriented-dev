import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import itertools
from scipy import stats

df_std = pd.read_csv("tmp/time_0.csv")
df_std["version"] = "default"
df_rp = pd.read_csv("tmp/time_1.csv")
df_rp["version"] = "RPMalloc"
df_mi = pd.read_csv("tmp/time_2.csv")
df_mi["version"] = "MiMalloc"
df = pd.concat([df_std, df_rp, df_mi])

df_2 = df[df.groupby(["version"])['real'].transform(stats.zscore).abs() < 3]
#
grouped = df_2.groupby(["version"]).mean().reset_index()
# grouped["text"] = ["$\mu=${0:.2f}\n$\sigma=${1:.2f}".format(mean,std) for mean,std in zip(grouped["mean"], grouped["std"])]

print(grouped)


for prop in ["real", "kernel", "user", "max", "avg"]:
    data = grouped[["version", prop]]
    print(data)
    ylim = (data[prop].min() * 0.9, data[prop].min() * 1.1)
    ax = data.plot.bar(x="version", rot=0, ylim=ylim, figsize=(10,8))
    plt.show()

