import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import csv

csv_reader=csv.reader(open('output.txt',encoding='utf-8'))

posx = []
posy = []
Bz = []

points = 0
for i,rows in enumerate(csv_reader):
    if len(rows) == 0:
        break
    else:
        thestr = rows[0]
        leftright = thestr.split(":")
        left = leftright[0].strip('{').strip('}').split(' ')
        left = [x for x in left if x != '']
        posx.append(float(left[0]))
        posy.append(float(left[1]))
        right = leftright[1].strip(' ')
        Bz.append(float(right))
        points = points + 1

x = np.arange(-1e-4,1e-4,5e-6)
y = np.arange(-1e-4,1e-4,5e-6)
X, Y = np.meshgrid(x, y)
B = np.zeros((np.size(x), np.size(y)))

for i in range(points):
    xi = 0
    for xindex in range(np.size(x)):
        if np.abs(x[xindex] - posx[i]) < 1e-10:
            xi = xindex
            break
    yi = 0
    for yindex in range(np.size(y)):
        if np.abs(y[yindex] - posy[i]) < 1e-10:
            yi = yindex
            break
    B[xi][yi] = Bz[i]


ax = plt.axes(projection='3d')
ax.plot_surface(X,Y,B)
plt.show()
