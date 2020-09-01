import numpy as np
import matplotlib.pyplot as plt
import csv

csv_reader=csv.reader(open('output.csv',encoding='utf-8'))

x = np.arange(0.12, 0.16, 0.0004)
x = x[:-1]

for i,rows in enumerate(csv_reader):
        if i==0:
            row1=rows[:-1]
        if i==2:
            row2=rows[:-1]


row1 = list(map(lambda x: float(x.strip()), row1))
row1 = [i for i in row1]
np.array(row1)
plt.plot(x,row1)
plt.show()
row2 = list(map(lambda x: float(x.strip()), row2))
row2 = [i for i in row2]
np.array(row2)
plt.plot(x,row2)
plt.show()
