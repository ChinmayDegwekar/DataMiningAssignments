#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure


# In[2]:


data = np.genfromtxt('data.csv',delimiter=',')
data = np.log(data)


# In[3]:


figure(num=None, figsize=(14, 9), dpi=120, facecolor='w', edgecolor='k')
N = 7
ind = np.arange(N)  # the x locations for the groups
width = 0.27       # the width of the bars

fig = figure(figsize=(13,9))
ax = fig.add_subplot(111)
ax.spines['top'].set_color('white') 
ax.spines['right'].set_color('white')

yvals = data[:,0]
rects1 = ax.bar(ind, yvals, width, color='r')
zvals = data[:,1]
rects2 = ax.bar(ind+width, zvals, width, color='y')
kvals = data[:,2]
rects3 = ax.bar(ind+width*2, kvals, width, color='c')

ax.set_ylabel('Distance (log scaled)')
ax.set_xlabel('d (No of dimensions)')
ax.set_xticks(ind+width)
ax.set_xticklabels( ('1', '2', '4', '8', '16', '32', '64') )
ax.legend( (rects1[0], rects2[0], rects3[0]), ('L1 distance', 'L2 distance', 'L∞ distance') )

def autolabel(rects):
    for rect in rects:
        h = rect.get_height()
        ax.text(rect.get_x()+rect.get_width()/2., h+0.35, '%f'%h,
                ha='center', va='bottom', rotation=90)

autolabel(rects1)
autolabel(rects2)
autolabel(rects3)

plt.show()
fig.savefig('plot.jpg', dpi=fig.dpi)

