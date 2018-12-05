#!/usr/bin/python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys

df = pd.read_csv(sys.argv[1],sep=',')

features = df.columns

plt.figure(num=None, figsize=(6, 10))

for ft in features:
    if(ft!="wsize "):
#        plt.plot(df[features[0]].values,df[ft].values,label=ft,marker='o',markersize=4)
        plt.semilogy(df[features[0]].values,df[ft].values,label=ft,marker='o',markersize=4)

plt.xlabel("k size filter")
plt.ylabel("time (ms)")
plt.title("Execution time of max/min filter")
plt.legend()
plt.savefig('execution_time.png', bbox_inches='tight')
