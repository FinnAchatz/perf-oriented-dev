# import pandas as pd
# import seaborn as sns
# import matplotlib.pyplot as plt
# import itertools
# from scipy import stats
# import glob
#
#
# df = pd.read_csv("values.csv")
#
# print(df)
#
# df["name"] = [n + str(es) + str(im) + str(ne) for n, es, im, ne in zip(df["name"], df["elem_size"], df["ins_mix"], df["num_elems"])]
#
# df2 = df[["name", "repetitions"]]
#
#
#
# grouped = df2.groupby(["name"])
#
# print(grouped)
#
# # ylim = (data[prop].min() * 0.9, data[prop].min() * 1.1)
# ax = grouped.plot.bar(x="name", rot=25, figsize=(10,8), log=True)
# # ax.bar_label(ax.containers[0])
# plt.savefig("time_arenaalloc.png")
# plt.show()
#

import pandas as pd
import matplotlib.pyplot as plt
import os

# Load the data into a pandas DataFrame
file_path = 'values.csv'  # Change this to your actual file path
data = pd.read_csv(file_path)

# Create an output directory for the plots
output_dir = 'plots'
os.makedirs(output_dir, exist_ok=True)

# Group the data by elem_size and num_elems
grouped_data = data.groupby(['elem_size', 'num_elems'])

# Create bar plots for each configuration of elem_size and num_elems
for (elem_size, num_elems), group in grouped_data:
    ins_mix_values = group['ins_mix'].unique()
    num_ins_mix = len(ins_mix_values)
    
    fig, axes = plt.subplots(nrows=1, ncols=num_ins_mix, figsize=(15, 6), sharey=True)
    
    if num_ins_mix == 1:
        axes = [axes]
    
    for ax, ins_mix in zip(axes, ins_mix_values):
        subset = group[group['ins_mix'] == ins_mix]
        ax.bar(subset['name'], subset['repetitions'], color='skyblue')

        # Set the y-axis to log scale and start from a small positive number
        ax.set_yscale('log')
        ax.set_ylim(bottom=1)  # Start y-axis from 1 

        # Adding labels and title
        ax.set_xlabel('Data Structure')
        ax.set_title(f'ins_mix={ins_mix}')
        ax.set_xticklabels(subset['name'], rotation=45)
    
    # Set common ylabel and overall title
    fig.supylabel('Repetitions')
    fig.suptitle(f'Repetitions for elem_size={elem_size}, num_elems={num_elems}', fontsize=16)
    
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    
    # Save the plot as a PNG file
    plot_filename = os.path.join(output_dir, f'repetitions_elem_size_{elem_size}_num_elems_{num_elems}.png')
    plt.savefig(plot_filename)
    
    # Show the plot
    plt.show()

