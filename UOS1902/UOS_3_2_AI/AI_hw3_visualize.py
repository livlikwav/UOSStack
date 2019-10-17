#!/usr/bin/env python
# coding: utf-8

# #	double learning_rate = 7;
# #	double toleration = 0.05;
# #	vector<int> nodeNumberByLayer = {2, 1};

# > # layer 파일 읽어오기

# In[30]:


import matplotlib.pyplot as plt
import numpy as np
import csv

layer1_w0 = []
layer1_w1 = []
layer1_bias0 = []
layer1_w2 = []
layer1_w3 = []
layer1_bias1 = []
    
f = open(./weights.csv', 'r', encoding='utf-8')
rdr = csv.reader(f)
for line in rdr:
    layer1_w0.append(line[0])
    layer1_w1.append(line[1])
    layer1_bias0.append(line[2])
    layer1_w2.append(line[3])
    layer1_w3.append(line[4])
    layer1_bias1.append(line[5])
f.close()

layer1_w0 = list(map(float, layer1_w0[1:]))
layer1_w1 = list(map(float, layer1_w1[1:]))
layer1_bias0 = list(map(float, layer1_bias0[1:]))
layer1_w2 = list(map(float, layer1_w2[1:]))
layer1_w3 = list(map(float, layer1_w3[1:]))
layer1_bias1 = list(map(float, layer1_bias1[1:]))

layer1_w0 = np.array(layer1_w0)
layer1_w1 = np.array(layer1_w1)
layer1_bias0 = np.array(layer1_bias0)
layer1_w2 = np.array(layer1_w2)
layer1_w3 = np.array(layer1_w3)
layer1_bias1 = np.array(layer1_bias1)


# # 배열 길이 확인

# In[31]:


print("len(layer1_w0) : ********************* " + str(len(layer1_w0)))


# # error graph 그리기!

# In[32]:


error = []
f = open('./error.csv', 'r', encoding='utf-8')
rdr = csv.reader(f)
for line in rdr:
    error = error + line
f.close()
error = list(map(float, error[1:]))

plt.figure(figsize=(10,10))
plt.title('error graph')
plt.xlabel('train #')
plt.ylabel('MSE')

plt.plot(error[1:], 'blue', label='error')

plt.show()


# # AND, OR, XOR 그래프

# In[33]:



x_vals = np.arange(-2,2,0.1)
for i in range(0, len(layer1_w0)):
    y1_vals = (-layer1_w0[i] / layer1_w1[i]) * x_vals + (-layer1_bias0[i] / layer1_w1[i])
    y2_vals = (-layer1_w2[i] / layer1_w3[i]) * x_vals + (-layer1_bias1[i] / layer1_w3[i])
    if( i % 200 == 0):
        print(i)
        plt.scatter(0, 0, c = 'b')
        plt.scatter(0, 1, c = 'g')
        plt.scatter(1, 0, c = 'r')
        plt.scatter(1, 1, c = 'c')
        plt.xlim(-3,3)
        plt.ylim(-3,3)
        plt.plot(x_vals, y1_vals, 'm')
        plt.plot(x_vals, y2_vals, 'y')
        plt.pause(0.1)
    elif( i == 1218):
        print(i)
        plt.scatter(0, 0, c = 'b')
        plt.scatter(0, 1, c = 'g')
        plt.scatter(1, 0, c = 'r')
        plt.scatter(1, 1, c = 'c')
        plt.xlim(-3,3)
        plt.ylim(-3,3)
        plt.plot(x_vals, y1_vals, 'm')
        plt.plot(x_vals, y2_vals, 'y')
        plt.pause(0.1)
    
plt.show()


# # DONUT 그래프

# In[9]:



x_vals = np.arange(-2,2,0.1)
for i in range(0, len(layer1_w0)):
    y1_vals = (-layer1_w0[i] / layer1_w1[i]) * x_vals + (-layer1_bias0[i] / layer1_w1[i])
    y2_vals = (-layer1_w2[i] / layer1_w3[i]) * x_vals + (-layer1_bias1[i] / layer1_w3[i])
    if( i % 500 == 0):
        print(i)
        plt.scatter(0, 0, c = 'r')
        plt.scatter(0, 1, c = 'r')
        plt.scatter(1, 0, c = 'r')
        plt.scatter(1, 1, c = 'r')
        plt.scatter(0.5, 1, c = 'r')
        plt.scatter(1, 0.5, c = 'r')
        plt.scatter(0, 0.5, c = 'r')
        plt.scatter(0.5, 0, c = 'r')
        plt.scatter(0.5, 0.5, c = 'b')
        plt.xlim(-3,3)
        plt.ylim(-3,3)
        plt.plot(x_vals, y1_vals, 'm')
        plt.plot(x_vals, y2_vals, 'y')
        plt.pause(0.1)
    elif( i == 3235):
        print(i)
        plt.scatter(0, 0, c = 'r')
        plt.scatter(0, 1, c = 'r')
        plt.scatter(1, 0, c = 'r')
        plt.scatter(1, 1, c = 'r')
        plt.scatter(0.5, 1, c = 'r')
        plt.scatter(1, 0.5, c = 'r')
        plt.scatter(0, 0.5, c = 'r')
        plt.scatter(0.5, 0, c = 'r')
        plt.scatter(0.5, 0.5, c = 'b')
        plt.xlim(-3,3)
        plt.ylim(-3,3)
        plt.plot(x_vals, y1_vals, 'm')
        plt.plot(x_vals, y2_vals, 'y')
        plt.pause(0.1)
    
plt.show()

