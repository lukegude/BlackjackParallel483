import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


par = open("mc_p.txt", "r")
#seq = open("mc_s.txt", "r")


# Parse the data
par_data = par.readlines()
#seq_data = seq.readlines()



#def plot_data(par_data=par_data, seq_data=seq_data):
#    par_data = [x.split(' ') for x in par_data]
#    par_data = [[x[0],x[1]] for x in par_data]
#    seq_data = [x.split(' ') for x in seq_data]
#    seq_data = [[x[0],x[1]] for x in seq_data]
#    
#    df = pd.DataFrame(par_data, columns=['time', 'n'])
#    df['time'] = df['time'].astype(float)
#    df['n'] = df['n'].astype(float)
#    df = df.sort_values(by=['n'])
#    
#    print(df)
#    
#    df2 = pd.DataFrame(seq_data, columns=['time', 'n'])
#    df2['time'] = df2['time'].astype(float)
#    df2['n'] = df2['n'].astype(float)
#    df2 = df2.sort_values(by=['n'])
#    
#    plt.plot(df['n'], df['time'], label='Parallel')
#    plt.plot(df2['n'], df2['time'], label='Sequential')
#    plt.xlabel('n')
#    plt.ylabel('time (s)')
#    plt.title('Monte Carlo')
#    plt.legend()
#    plt.savefig('mc.png')
#    plt.show()

#plot_data()

par_data = [x.split(' ') for x in par_data]
par_data = [[x[2],x[3],x[4][:-1]] for x in par_data]

# Plot the data on a bar chart
df = pd.DataFrame(par_data, columns=['wins', 'draws', 'losses'])
df['wins'] = df['wins'].astype(float)
df['draws'] = df['draws'].astype(float)
df['losses'] = df['losses'].astype(float)

# Set the index to basic, aggressive, conservative
df = df.set_index([pd.Index(['basic', 'aggressive', 'conservative'])])
print(df)

# Make three dataframes for each of the three strategies
df1 = df.iloc[0]
df2 = df.iloc[1]
df3 = df.iloc[2]

# Plot the data and show the values on the bars
ax = df1.plot(kind='bar', title='Wins, Draws, and Losses for Basic Strategy')
for p in ax.patches:
    ax.annotate(str(p.get_height()), (p.get_x() * 1.005, p.get_height() * 1.005))
plt.savefig('basic.png')

plt.figure()
ax = df2.plot(kind='bar', title='Wins, Draws, and Losses for Aggressive Strategy')
for p in ax.patches:
    ax.annotate(str(p.get_height()), (p.get_x() * 1.005, p.get_height() * 1.005))
plt.savefig('aggressive.png')

plt.figure()
ax = df3.plot(kind='bar', title='Wins, Draws, and Losses for Conservative Strategy')
for p in ax.patches:
    ax.annotate(str(p.get_height()), (p.get_x() * 1.005, p.get_height() * 1.005))
plt.savefig('conservative.png')

