import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


par = open("mc_p.txt", "r")
seq = open("mc_s.txt", "r")


# Parse the data
par_data = par.readlines()
seq_data = seq.readlines()



def plot_data(par_data=par_data, seq_data=seq_data):
   par_data = [x.split(' ') for x in par_data]
   par_data = [[x[0],x[1]] for x in par_data]
   seq_data = [x.split(' ') for x in seq_data]
   seq_data = [[x[0],x[1]] for x in seq_data]
   
   df = pd.DataFrame(par_data, columns=['time', 'n'])
   df['time'] = df['time'].astype(float)
   df['n'] = df['n'].astype(float)
   df = df.sort_values(by=['n'])
   
   print(df)
   
   df2 = pd.DataFrame(seq_data, columns=['time', 'n'])
   df2['time'] = df2['time'].astype(float)
   df2['n'] = df2['n'].astype(float)
   df2 = df2.sort_values(by=['n'])
   print(df2)
   
   plt.plot(df['n'], df['time'],label='Parallel')
   plt.plot(df2['n'], df2['time'], label='Sequential')
   plt.xlabel('Number of simulations (n)')
   plt.ylabel('Time (s)')
   plt.title('Speedup of Monte Carlo Simulation')
   plt.legend()
   plt.savefig('mc.png')
   plt.show()

plot_data()


def plot_scale(par_data=par_data):
    par_data = [x.split(' ') for x in par_data]
    par_data = [[x[0],x[2][0]] for x in par_data]
    
    df = pd.DataFrame(par_data, columns=['time', 'p'])
    df['time'] = df['time'].astype(float)
    df['p'] = df['p'].astype(float)
    df = df.sort_values(by=['p'])
    print(df)
    
    plt.plot(df['p'], df['time'], '-o', color='red')
    # Show each point
    
    plt.xlabel('Number of processors (p)')
    plt.ylabel('Time (s)')
    plt.title('Scalability of Monte Carlo Simulation')
    plt.savefig('mc_scale.png')
    plt.show()
