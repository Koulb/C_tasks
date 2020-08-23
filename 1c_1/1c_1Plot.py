#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import os.path
 
#checking existance of text files
if not os.path.exists('points.txt') or not os.path.exists('polygonPoints.txt'):
	print("Run 1c_1.c first")
	exit()

#reading data
PCinput = "points.txt"
data = np.loadtxt(PCinput)
x = data[:, 0]
y = data[:, 1]

PCinput = "polygonPoints.txt"
data_pol = np.loadtxt(PCinput)
x_pol = data_pol[:, 0]
y_pol = data_pol[:, 1]

#plotting data
plt.figure()
plt.scatter(x, y, s = 50, label = 'Points', color = 'b') 
plt.plot(x_pol,y_pol, label ='Polygon', color = 'r')
plt.xlabel('x')
plt.xticks(np.arange(-5, 6, 1)) ;
plt.ylabel('y')
plt.yticks(np.arange(-5, 6, 1)) ;
plt.grid()
plt.legend(loc = 'upper left')
plt.title('Shell of points')
plt.show()