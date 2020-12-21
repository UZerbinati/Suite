import sys
sys.path.append('../Build')
from suite import *
import matplotlib.pyplot as plt
def Draw(meshfun,mesh,order=1):
    a = mesh.getElement(0).getPoint(0);
    X = [a+0.5*i*mesh.getSize(1) for i in range(0,2*mesh.getElNumber()+1)]
    Y = [meshfun.eval([x],order)[0] for x in X]
    plt.plot(X,Y)
