import matplotlib.pyplot as plt
import numpy as np
import csv

def abline(slope, intercept):
    axes = plt.gca()
    x_vals = np.array(axes.get_xlim())
    y_vals = intercept + slope * x_vals
    plt.plot(x_vals, y_vals, 'r')

grad = []
bias = []
f = open('result.csv', 'r', encoding='utf-8')
rdr = csv.reader(f)
for line in rdr:
    grad.append(line[3])
    bias.append(line[4])
f.close()

grad = list(map(float, grad[1:]))
print(grad)
bias = list(map(float, bias[1:]))
print(bias)
    
fig = plt.figure()
ax = fig.add_subplot(1,1,1)
ax.set(xlim=[-3., 3.], ylim = [-3., 3.])    

for i in range(len(grad)):
    abline(grad[i], bias[i])

plt.scatter(0,0, s = 100, c = 'b')
plt.scatter(1,0, s = 100, c = 'b')
plt.scatter(0,1, s = 100, c = 'b')
plt.scatter(1,1, s = 100, c = 'b')
plt.plot([-3,3],[0,0],'--', c = 'k')
plt.plot([0,0],[-3,3],'--', c = 'k')
plt.title('result')
plt.show()

"""
error = []
f = open('error.csv', 'r', encoding='utf-8')
rdr = csv.reader(f)
for line in rdr:
    error = error + line
f.close()
error = list(map(int, error[1:]))
print(error)

fig = plt.figure()
ax = fig.add_subplot(1,1,1)
ax.set(xlim=[0., 3.], ylim = [0., 3.])
plt.plot(error[1:])
plt.title('error')
plt.show()
"""
