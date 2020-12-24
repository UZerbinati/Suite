import sys
sys.path.append('../Build')
from suite import *
import matplotlib.pyplot as plt
def Draw(meshfun,mesh,order):
    a = mesh.getElement(0).getPoint(0);
    X = [a+0.1*i*mesh.getSize(1) for i in range(0,10*mesh.getElNumber()+1)]
    Y = [meshfun.eval([x],order)[0] for x in X]
    plt.plot(X,Y)
