#!/usr/bin/python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys

df = pd.read_csv(sys.argv[1],sep=',')

features = df.columns
#df[features[0]].values

plt.plot(df[features[0]].values,df[features[1]].values/1000,label="filter2d",marker="o")
plt.plot(df[features[0]].values,df[features[2]].values/1000,label="sepfilter2d",marker="x")
plt.plot(df[features[0]].values,df[features[3]].values/1000,label="FTfilter",marker="v")
plt.xlabel("k size filter")
plt.ylabel("time (ms)")
plt.title("Execution time of gaussian filter")
plt.legend()
plt.savefig('execution_time.png', bbox_inches='tight')
