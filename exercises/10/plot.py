import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np

# Load the data into a pandas DataFrame
postfix = 'local'
file_path = f'values_{postfix}.csv'  # Change this to your actual file path
output_dir = f'plots_{postfix}'
data = pd.read_csv(file_path)

# Create an output directory for the plots
os.makedirs(output_dir, exist_ok=True)

# Group the data by elem_size and num_elems
grouped_data = data.groupby(['elem_size', 'num_elems'])

# Create bar plots for each configuration of elem_size and num_elems
for (elem_size, num_elems), group in grouped_data:
    ins_mix_values = group['ins_mix'].unique()
    name_values = group['name'].unique()
    num_ins_mix = len(ins_mix_values)
    num_names = len(name_values) 

    fig, ax = plt.subplots(figsize=(15, 5))
    
    bar_width = 0.2
    index = np.arange(num_ins_mix)

    # Calculate the maximum number of repetitions for this group
    max_repetitions = group['repetitions'].max()
    
    for i, name in enumerate(name_values):
        subset = group[group['name'] == name]
        repetitions = subset.set_index('ins_mix').reindex(ins_mix_values)['repetitions'].values
        bar_positions = index + i * bar_width
        bars = ax.bar(bar_positions, repetitions, bar_width, label=f'name={name}')
        
        # Add the number of repetitions and percentage above each bar
        for bar in bars:
            height = bar.get_height()
            percentage = (height / max_repetitions) * 100
            ax.text(bar.get_x() + bar.get_width() / 2, height, f'{int(height)}\n({percentage:.1f}%)', ha='center', va='bottom', fontsize=10) 

    # Adding labels and title
    ax.set_xlabel('Instruction mix (% insert/delete)')
    ax.set_ylabel('Repetitions (log scale, in hundered)')
    ax.set_title(f'Repetitions for elem_size={elem_size}, num_elems={num_elems}', fontsize=16)
    ax.set_xticks(index + bar_width * (num_names - 1) / 2)
    ax.set_xticklabels(ins_mix_values, rotation=45)
    ax.set_ylim(bottom=1)
    ax.legend()
    ax.grid(axis='y') 
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    
    # Save the plot as a PNG file
    plot_filename = os.path.join(output_dir, f'repetitions_elem_size_{elem_size}_num_elems_{num_elems}.png')
    plt.savefig(plot_filename)
    
    # Show the plot
    plt.show()

