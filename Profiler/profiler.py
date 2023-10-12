import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def read_and_pre_processing() -> pd.DataFrame:
    benchmark_df = pd.read_csv('Profiler/srcprof.csv', sep=";")
    benchmark_df['N_MEMB'] = np.array(benchmark_df['N_MEMB'], dtype=int)
    benchmark_df.set_index(['N_MEMB'], inplace=True)
    benchmark_df.dropna(axis=1, inplace=True)
    benchmark_df['Total'] = benchmark_df.sum(axis=1)
    benchmark_df.sort_index(inplace=True)
    return benchmark_df

def benchmark_plot(benchmark_df:pd.DataFrame, benchmark_label:str, title:str, color:str)->None:
    df = benchmark_df[benchmark_label]
    plt.plot(df.index, df.values, label=benchmark_label, marker='o', markersize=3, linewidth=1, color=color)
    plt.axhline(y=df.mean(), color='r', linestyle='--', label=f'Mean: {df.mean():.3}s', alpha=0.5, linewidth=1)
    plt.title(title)
    plt.xlabel('Number of members')
    plt.ylabel('Time (s)')
    plt.grid()
    plt.legend()
    plt.savefig(f'Profiler/Images/{benchmark_label}.png', dpi=300)
    plt.close()
    
def benchmark_full_plot(benchmark_df):
    df = benchmark_df
    plt.plot(df.index, df.values, label = df.columns, marker='o', markersize=3, linewidth=1)
    #plt.axhline(y=df.mean(), color='r', linestyle='--', label=f'Mean: {df.mean():.3}s', alpha=0.5, linewidth=1)
    plt.title('Full Benchmark')
    plt.xlabel('Number of members')
    plt.ylabel('Time (s)')
    plt.grid()
    plt.legend()
    plt.savefig(f'Profiler/Images/{"Full Benchmark"}.png', dpi=300)
    plt.close()

if __name__ == "__main__":
    benchmark_df = read_and_pre_processing()
    benchmark_plot(benchmark_df, 'READ_TSP', 'Read File Time', 'b')
    benchmark_plot(benchmark_df, 'BUILD_ALL_EDGES', 'Build all edges time', 'g')
    benchmark_plot(benchmark_df, 'SORT_EDGES', 'Sort edges time', '#FFA500')
    benchmark_plot(benchmark_df, 'BUILD_MST', 'Build MST time', '#FF00FF')
    benchmark_plot(benchmark_df, 'BUILD_TOUR', 'Build tour time', 'r')

    benchmark_full_plot(benchmark_df)
