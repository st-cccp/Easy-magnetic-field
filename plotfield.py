import numpy as np
import matplotlib.pyplot as plt
import csv

csv_reader=csv.reader(open('output.csv',encoding='utf-8'))

x = range(-100, 104, 4)
x = [i/1000000 for i in x]

for i,rows in enumerate(csv_reader):
        if i==0:
            row1=rows[:-1]
        if i==0:
            row2=rows[:-1]

row1 = list(map(lambda x: float(x.strip()), row1))
row1mean=np.mean(row1)
row1 = [i-row1mean for i in row1]
np.array(row1)
plt.plot(x, row1)
plt.show()

row2 = list(map(lambda x: float(x.strip()), row2))
row2mean=np.mean(row2)
row1 = [i-row2mean for i in row2]
np.array(row2)
plt.plot(x,row2)
plt.show()
