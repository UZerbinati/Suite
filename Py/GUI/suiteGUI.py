import sys
sys.path.append('../Build')
from suite import *
import matplotlib.pyplot as plt
def Draw(meshfun,mesh,order,mk="*-"):
    if (meshfun.getDim()[0]==1 and meshfun.getDim()[1]==1):
        if(mesh.getType()=="UNIFORM"):
            a = mesh.getLineElement(0).getPoint(0);
            X = [a+0.1*i*mesh.getSize(1) for i in range(0,10*mesh.getElNumber()+1)]
            Y = [meshfun.eval([x],order)[0] for x in X]
            plt.plot(X,Y,mk)

def Figure(meshfun,mesh,order,mk="*-"):
    if (meshfun.getDim()[0]==1 and meshfun.getDim()[1]==1):
        if(mesh.getType()=="UNIFORM"):
            a = mesh.getLineElement(0).getPoint(0);
            X = [a+0.1*i*mesh.getSize(1) for i in range(0,10*mesh.getElNumber()+1)]
            Y = [meshfun.eval([x],order)[0] for x in X]
            return plt.plot(X,Y,mk)

def DrawTriangle(T):
    X = [T.GetVertex(i).GetX() for i in range(3)];
    Y = [T.GetVertex(i).GetY() for i in range(3)];
    #plt.scatter(X,Y,marker="*",color="black");
    for i in range(3):
        plt.plot([X[i-1],X[i]],[Y[i-1],Y[i]],"--",color="black");