import sys
sys.path.append('../Build')
from suite import *
import matplotlib.pyplot as plt
import numpy as np
def Draw(meshfun,mesh,order=0,mk="*-"):
    def zero(x,y):
        return 0.0*x+0.0*y;
    if (meshfun.getDim()[0]==1 and meshfun.getDim()[1]==1):
        if(mesh.getType()=="UNIFORM"):
            a = mesh.getLineElement(0).getPoint(0);
            X = [a+0.1*i*mesh.getSize(1) for i in range(0,10*mesh.getElNumber()+1)]
            Y = [meshfun.eval([x],order)[0] for x in X]
            plt.plot(X,Y,mk)
    if (meshfun.getDim()[0]==2 and meshfun.getDim()[1]==1):
        if(mesh.getType()=="SQUARE-UNIFORM"):
            h = mesh.getSize(0);
            Q = mesh.getContainer();
            x = np.arange(Q[0],Q[1]+1e-8,h)
            y = np.arange(Q[2],Q[3]+1e-8,h)
            X,Y = np.meshgrid(x, y) # grid of point
            Z = zero(X,Y);
            for i in range(len(x)):
                for j in range(len(y)):
                    Z[i,j] = meshfun.eval([x[i],y[j]],order)[0];
            plt.pcolor(Y,X,Z);
def Figure(meshfun,mesh,order,mk="*-"):
    if (meshfun.getDim()[0]==1 and meshfun.getDim()[1]==1):
        if(mesh.getType()=="UNIFORM"):
            a = mesh.getLineElement(0).getPoint(0);
            X = [a+0.1*i*mesh.getSize(1) for i in range(0,10*mesh.getElNumber()+1)]
            Y = [meshfun.eval([x],order)[0] for x in X]
            return plt.plot(X,Y,mk)
def GeoDraw(Geo,C,N):
    if N%2==0:
        N=N+1;
    X = np.linspace(C[0][0],C[0][1],N);
    Y = np.linspace(C[1][0],C[1][1],N);
    for k in range(len(X)):
        for n in range(len(Y)):
            if Geo.eval([X[k],Y[n]])<(-1.05/(N)):
                color = "red";
            elif (-1.05/(N))<Geo.eval([X[k],Y[n]])<(1.05/(N)):
                color = "blue";
            else:
                color = "green";
            plt.scatter(X[k],Y[n],color=color)
def DrawSquare(Q,c="black"):
    X = [Q.getVertex(i).GetX() for i in range(4)];
    Y = [Q.getVertex(i).GetY() for i in range(4)];
    #plt.scatter(X,Y,marker="*",color="black");
    for i in range(4):
        plt.plot([X[i-1],X[i]],[Y[i-1],Y[i]],"*--",color=c);
def DrawTriangle(T):
    X = [T.GetVertex(i).GetX() for i in range(3)];
    Y = [T.GetVertex(i).GetY() for i in range(3)];
    #plt.scatter(X,Y,marker="*",color="black");
    for i in range(3):
        plt.plot([X[i-1],X[i]],[Y[i-1],Y[i]],"--",color="black");
def DrawMesh(M):
    if M.getDim() == 2:
        n = M.getElNumber();
        for k in range(n):
            Q = M.getSqEl(k);
            DrawSquare(Q);
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