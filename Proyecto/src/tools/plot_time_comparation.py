#!/usr/bin/python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys

df_lti = pd.read_csv("lti-perf.csv",sep=',')

df_dokladal = pd.read_csv("dokladal-perf.csv",sep=',')
df_vectorized = pd.read_csv("vectorized-perf.csv",sep=',')
df_opencv = pd.read_csv("opencv-perf.csv",sep=',')

features = df_lti.columns


trivial_pix = np.array(df_lti[features[0]][0::2])
trivial_avg = np.array(df_lti[features[1]][0::2])
trivial_std = np.array(df_lti[features[2]][0::2])

lti_pix = np.array(df_lti[features[0]][1::2])
lti_avg = np.array(df_lti[features[1]][1::2])
lti_std = np.array(df_lti[features[2]][1::2])

dokladal_pix = np.array(df_dokladal[features[0]])
dokladal_avg = np.array(df_dokladal[features[1]])
dokladal_std = np.array(df_dokladal[features[2]])

vectorized_pix = np.array(df_vectorized[features[0]])
vectorized_avg = np.array(df_vectorized[features[1]])
vectorized_std = np.array(df_vectorized[features[2]])

opencv_pix = np.array(df_opencv[features[0]])
opencv_avg = np.array(df_opencv[features[1]])
opencv_std = np.array(df_opencv[features[2]])



plt.semilogy(lti_pix,lti_avg,label="ltilib",marker='o',markersize=4)
plt.fill_between(lti_pix,lti_avg-lti_std,lti_avg+lti_std,alpha=0.2)
plt.semilogy(trivial_pix,trivial_avg,label="trivial",marker='o',markersize=4)
plt.fill_between(trivial_pix,trivial_avg-trivial_std,trivial_avg+trivial_std,alpha=0.2)
plt.semilogy(dokladal_pix,dokladal_avg,label="dokladal",marker='o',markersize=4)
plt.fill_between(dokladal_pix,dokladal_avg-dokladal_std,dokladal_avg+dokladal_std,alpha=0.2)
plt.semilogy(vectorized_pix,vectorized_avg,label="vectorized-avx2",marker='o',markersize=4)
plt.fill_between(vectorized_pix,vectorized_avg-vectorized_std,vectorized_avg+vectorized_std,alpha=0.2)
plt.semilogy(opencv_pix,opencv_avg,label="opencv",marker='o',markersize=4)
plt.fill_between(opencv_pix,opencv_avg-opencv_std,opencv_avg+opencv_std,alpha=0.2)

plt.legend()



plt.xlabel("NxM píxeles")
plt.ylabel("Tiempo (ms)")
plt.title("Tiempo de ejecución de filtros de máximos 5x5")
plt.savefig('execution_time.png', bbox_inches='tight')
