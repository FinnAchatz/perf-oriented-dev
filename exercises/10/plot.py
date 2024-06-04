import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib.ticker as mticker

# Read the CSV file
df = pd.read_csv('values_local.csv')

# # Get the unique combinations of elem_size and num_elems
# combinations = df[['random_access', 'elem_size', 'num_elems', 'fill_random']].drop_duplicates()
#
# # Set up the seaborn style
# sns.set(style="whitegrid")
#
# # Determine unique ins_mix values
# unique_ins_mix = sorted(df[['ins_mix', 'random_access', 'fill_random']].unique())
#
# # Convert 'ins_mix' to a categorical type with a specific order
# df['ins_mix'] = df['ins_mix'].astype(str)
#
# # Iterate through each combination
# for _, row in combinations.iterrows():
#     elem_size = row['elem_size']
#     num_elems = row['num_elems']
#     fill_random = row['fill_random']
#     random_access = row['random_access']
#     
#     # Filter the dataframe for the current combination
#     subset = df[(df['elem_size'] == elem_size) & (df['num_elems'] == num_elems) & (df['fill_random'] == fill_random) & (df['random_access'] == random_access)]
#     
#     plt.figure()
#     for name in subset['name'].unique():
#         subset_name = subset[subset['name'] == name]
#         plt.plot(subset_name['ins_mix'], subset_name['repetitions'], label=name, marker='o')
#      
#     # Set the title and labels
#     plt.title(f'Performance for elem_size={elem_size}, num_elems={num_elems}, random_access={random_access}, fill_random={fill_random}')
#     plt.xlabel('% insertions/deletions')
#     plt.ylabel('repetitions')
#     
#     # Show the legend
#     plt.legend(title='Name')
#
#     # Set y-axis to plain format (disable scientific notation)
#     plt.gca().yaxis.set_major_formatter(mticker.ScalarFormatter(useMathText=False))
#     plt.gca().yaxis.get_major_formatter().set_useOffset(False)
#     plt.gca().yaxis.get_major_formatter().set_scientific(False)
#
#     
#     plt.show()
#
#     # Save the plot to a file
#     # plt.savefig(f'plot_elem_size_{elem_size}_num_elems_{num_elems}.png')
#     # 
#     # # Close the plot
#     # plt.close()

# Get the unique combinations of elem_size and num_elems
combinations = df[['elem_size', 'num_elems']].drop_duplicates()

# Set up the seaborn style
sns.set(style="whitegrid")

# Determine unique ins_mix values
unique_ins_mix = sorted(df['ins_mix'].unique())

# Convert 'ins_mix' to a categorical type with a specific order
df['ins_mix'] = df['ins_mix'].astype(str)

# Iterate through each combination
for _, row in combinations.iterrows():
    elem_size = row['elem_size']
    num_elems = row['num_elems']
    
    # Filter the dataframe for the current combination
    subset = df[(df['elem_size'] == elem_size) & (df['num_elems'] == num_elems)]
    
    plt.figure()
    for _, name_row in subset[['name', 'random_access', 'fill_random']].drop_duplicates().iterrows():
        subset_name = subset[(subset['name'] == name_row['name']) & (subset['random_access'] == name_row['random_access']) & (subset['fill_random'] == name_row['fill_random'])]
        plt.plot(subset_name['ins_mix'], subset_name['repetitions'], label=name_row, marker='o')
     
    # Set the title and labels
    plt.title(f'Performance for elem_size={elem_size}, num_elems={num_elems}')
    plt.xlabel('% insertions/deletions')
    plt.ylabel('repetitions')
    
    # Show the legend
    plt.legend(title='Name')

    # Set y-axis to plain format (disable scientific notation)
    plt.gca().yaxis.set_major_formatter(mticker.ScalarFormatter(useMathText=False))
    plt.gca().yaxis.get_major_formatter().set_useOffset(False)
    plt.gca().yaxis.get_major_formatter().set_scientific(False)

    
    plt.show()

    # Save the plot to a file
    # plt.savefig(f'plot_elem_size_{elem_size}_num_elems_{num_elems}.png')
    # 
    # # Close the plot
    # plt.close()

