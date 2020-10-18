import matplotlib.pyplot as plt
import numpy as np
with open("img.txt") as fin:
    width, height = list(map(int, fin.readline().split()))
    l = []
    for i in range(height):
        l.append(list(map(int, fin.readline().split())))
    
    for i in range(len(l)):
        l[i] = [(l[i][j+0], l[i][j+1], l[i][j+2]) for j in range(0, len(l[i]), 3)]
    
print(len(l), len(l[i]))

a = np.array(l)
    
    #print(l)
    #l = [(l[i:i+3]) for i in range(0, len(l), 3)]
    #l = [for i in range(0, len(l), width)]
    #l = [(l[i:i+height]) for i in range(0, len(l), height)]
    
plt.imshow(a)
plt.show()
print(width, height)