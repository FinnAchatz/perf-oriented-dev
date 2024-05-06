import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import itertools

df = pd.read_csv("times.csv")


# grouped = df.groupby(["init","mult","size_x","size_y"])['time'].mean().reset_index()
grouped = df.groupby(["init","mult","size_x","size_y"]).time.agg({'median', 'mean', 'std'}).reset_index()
grouped["text"] = ["M$=${0:.2f}\n$\mu=${1:.2f}\n$\sigma=${2:.2f}".format(med,mean,std) for med,mean,std in zip(grouped["median"],grouped["mean"], grouped["std"])]

ref = df[df["name"]=="FalseFalseNoneNone"]['time'].mean()
std = df[df["name"]=="FalseFalseNoneNone"]['time'].std()


print("reference: mean =", ref, "; std =", std)
print(grouped.sort_values(by="mean"))
print(grouped.sort_values(by="median"))

for version, col in itertools.product(["mult", "init", "both"], ["mean", "median"]):
     
    # Filter the DataFrame
    match version:
        case "mult": filtered_df = grouped[(grouped['init'] != True) & (grouped['mult'] != False)]
        case "init": filtered_df = grouped[(grouped['init'] != False) & (grouped['mult'] != True)]
        case "both": filtered_df = grouped[(grouped['init'] != False) & (grouped['mult'] != False)]

    # Pivot the DataFrame to get the values for the heatmap
    pivot_df = filtered_df.pivot(index='size_x', columns='size_y', values=col)

    pivot_df_text = filtered_df.pivot(index='size_x', columns='size_y', values='text').to_numpy()
    
    # Create the heatmap
    plt.figure(figsize=(10, 8))
    sns.heatmap(pivot_df, cmap='YlGnBu', annot=pivot_df_text, fmt="", vmin=71, vmax=75)
    plt.title(f'Heatmap of {col} time (Tiling of {version})')
    plt.savefig(f"{version}_{col}.png")
    plt.show()



# ##### Init
#
# # Filter the DataFrame
# filtered_df = grouped[(grouped['init'] != False) & (grouped['mult'] != True)]
#
# # Pivot the DataFrame to get the values for the heatmap
# pivot_df = filtered_df.pivot(index='size_x', columns='size_y', values='time')
#
# # Create the heatmap
# plt.figure(figsize=(10, 8))
# sns.heatmap(pivot_df, cmap='YlGnBu', annot=True, fmt=".1f", vmin=71, vmax=75)
# plt.title('Heatmap of Mean Time (Tiling of Init)')
# plt.savefig("init.png")
# plt.show()
#
#
#
# ##### Both
#
# # Filter the DataFrame
# filtered_df = grouped[(grouped['init'] != False) & (grouped['mult'] != False)]
#
# # Pivot the DataFrame to get the values for the heatmap
# pivot_df = filtered_df.pivot(index='size_x', columns='size_y', values='time')
#
# # Create the heatmap
# plt.figure(figsize=(10, 8))
# sns.heatmap(pivot_df, cmap='YlGnBu', annot=True, fmt=".1f", vmin=71, vmax=75)
# plt.title('Heatmap of Mean Time (Tiling of Both)')
# plt.savefig("both.png")
# plt.show()
