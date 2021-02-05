import sys
sys.path.append('../Build')
from suite import *
import matplotlib.pyplot as plt
import numpy as np
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
        
def DrawCAState(Automata,axopt=False):
    
    if Automata.getNStates == 2:
        plt.rcParams['image.cmap'] = 'binary'
    
    fig, ax = plt.subplots(figsize=(16, 9))
    v = Automata.getState().vec_export();
    data = np.array([v.to_Array()]);
    #print(data)
    ax.matshow(data);
    ax.axis(axopt);
def DrawCAStates(Automata,N,axopt=False):
    
    if Automata.getNStates == 2:
        plt.rcParams['image.cmap'] = 'binary'
    
    fig, ax = plt.subplots(figsize=(16, 9))
    v = Automata.getState().vec_export();
    data = np.array([v.to_Array()]);
    for i in range(N):
        Automata.Run();
        v = Automata.getState().vec_export();
        data = np.append(data,[v.to_Array()],axis=0);
    print(data)
    ax.matshow(data);
    ax.axis(axopt);