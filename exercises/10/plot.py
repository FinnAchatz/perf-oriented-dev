#!/usr/bin/env python
import matplotlib.pyplot as plt
import pandas as pd


def plot_for_name(df, name):
    grouped = df.groupby("ins_mix")
    for ins_mix, group in grouped:
        fig, axs = plt.subplots(
            1,
            len(group["elem_size"].unique()),  # Changed here
            figsize=(8 * len(group["elem_size"].unique()), 6),  # Changed here
        )
        fig.suptitle(f"{name} with {ins_mix}% I/D", fontsize=16)
        for i, elem_size in enumerate(sorted(group["elem_size"].unique())):
            group_subset = group[group["elem_size"] == elem_size]
            ax = axs[i] if len(group["elem_size"].unique()) > 1 else axs
            ax.set_title(f"Element Size: {elem_size}")
            for index, row in group_subset.iterrows():
                label = f"random_access={row['random_access']}"
                ax.plot(
                    row["num_elems"],
                    row["repetitions"],
                    marker="o",
                    label=None,
                    color="blue" if row["random_access"] else "orange",
                )
            group_sorted = group_subset.sort_values(by="num_elems")
            group_random = group_sorted[group_sorted["random_access"] == 1]
            ax.plot(
                group_random["num_elems"],
                group_random["repetitions"],
                linestyle="-",
                color="blue",
                label="random_access=1",
            )
            group_not_random = group_sorted[group_sorted["random_access"] == 0]
            ax.plot(
                group_not_random["num_elems"],
                group_not_random["repetitions"],
                linestyle="-",
                color="orange",
                label="random_access=0",
            )
            ax.set_xlabel("num_elems")
            ax.set_xscale("log")  # Set x-axis scale to logarithmic

            ax.set_ylabel("repetitions")
            ax.set_yscale("log")  # Set y-axis scale to logarithmic
            ax.legend()
            ax.grid(True)

        output_path = f"./images/{name}_ins_mix_{ins_mix}.png"
        plt.savefig(output_path)
        plt.close()


if __name__ == "__main__":
    df = pd.read_csv("./values_local.csv")
    df_array = df[(df["name"] == "array") & (df["fill_random"] == 0)]
    plot_for_name(df_array, "array")
    df_linked = df[(df["name"] == "linked list") & (df["fill_random"] == 0)]
    plot_for_name(df_linked, "linked_list")
    df_linked_random = df[(df["name"] == "linked list") & (df["fill_random"] == 1)]
    plot_for_name(df_linked_random, "linked_list_random_fill")
    df_tiered = df[(df["name"] == "tiered list") & (df["fill_random"] == 0)]
    plot_for_name(df_tiered, "tiered_list")
