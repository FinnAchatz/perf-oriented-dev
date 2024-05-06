import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import itertools
from scipy import stats

df = pd.read_csv("times.csv")

# grouped = df.groupby(["init","mult","size_x","size_y"])['time'].mean().reset_index()
# grouped = df.groupby(["init","mult","size_x","size_y"]).time.nlargest(n=2, keep='last').nsmallest(n=2, keep='last').agg({'median', 'mean', 'std'}).reset_index()
df_2 = df[df.groupby(["init","mult","size_x","size_y"])['time'].transform(stats.zscore).abs() < 3]
#
grouped = df_2.groupby(["init","mult","size_x","size_y"]).time.agg({'median', 'mean', 'std', 'min', 'max'}).reset_index()
grouped["text"] = ["M$=${0:.2f}\n$\mu=${1:.2f}\n$\sigma=${2:.2f}".format(med,mean,std) for med,mean,std in zip(grouped["median"],grouped["mean"], grouped["std"])]

print(grouped.describe())

ref = df[df["name"]=="FalseFalseNoneNone"]['time'].mean()
std = df[df["name"]=="FalseFalseNoneNone"]['time'].std()


print("reference: mean =", ref, "; std =", std)
print(grouped.sort_values(by="mean"))
print(grouped.sort_values(by="median"))

###### PLOT HEATMAPS #######

for version, col in itertools.product(["mult", "init", "both"], ["mean", "median"]):
     
    # Filter the DataFrame
    match version:
        case "mult": filtered_df = grouped[(grouped['init'] != True) & (grouped['mult'] != False)]
        case "init": filtered_df = grouped[(grouped['init'] != False) & (grouped['mult'] != True)]
        case "both": filtered_df = grouped[(grouped['init'] != False) & (grouped['mult'] != False)]

    # Pivot the DataFrame to get the values for the heatmap
    pivot_df = filtered_df.pivot(index='size_x', columns='size_y', values=col)

    pivot_df_text = filtered_df.pivot(index='size_x', columns='size_y', values='text').to_numpy()

    cmap = 'rocket' if col == 'mean' else 'mako' 
    
    # Create the heatmap
    plt.figure(figsize=(10, 8))
    sns.heatmap(pivot_df, cmap=cmap, annot=pivot_df_text, fmt="", vmin=71.5, vmax=73)
    plt.title(f'Heatmap of {col} time (Tiling of {version})')
    plt.savefig(f"{version}_{col}.png")
    plt.show()


###### PLOT BARS OF TOP #######

for mode in ['mean', 'median', 'min', 'max']:
    top = grouped.sort_values(by=mode).head(10)
    top['name'] = [f"{'init ' if init else ''}{'mult ' if mult else ''}{int(x)}x{int(y)}" for init,mult,x,y in zip(top['init'], top['mult'], top['size_x'], top['size_y'])]
    ax = top.plot.bar(x='name', y=mode, rot=25, ylim=(top[mode].iloc[0]-0.1, top[mode].iloc[9]+0.1), figsize=(10,8))
    plt.savefig(f"top_{mode}s.png")
    plt.show()
