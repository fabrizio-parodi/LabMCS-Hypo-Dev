from sys  import *
from ROOT import *
import time

rnd = TRandom3()
#rnd.SetSeed(int(time.time()))
rnd.SetSeed(123456789)

file = open("s1.dat","w")
for i in range(1,10000):
    a = rnd.Exp(0.1)
    if a > 0.5:
        continue 
    file.write(str(a)+"\n")

file = open("s2.dat","w")
for i in range(1,10000):
    b = rnd.Exp(0.106)
    if b > 0.5:
        continue
    file.write(str(b)+"\n")
    #file.write(str(rnd.Exp(0.11))+"\n")
