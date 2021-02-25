import sys
sys.path.append('../Py/Build');
tol = 1e-4
from suite import *;
from suiteGUI import *
from math import exp
import numpy as np
from numpy.linalg import solve

def test_PDE_Elliptic_1D_Test1():
    I = line(0.0,2.0)
    mesh = Mesh(1);
    mesh.UniformMesh(I,0.4)
    u0 = MeshFunction(mesh,1)
    u0.pushFunction(lambda P: [0]);
    u0_vec = u0.vec_export()
    v0 = vec(u0_vec.len())
    v0[1]=0.0;
    v0[v0.len()]=2.0;
    f = MeshFunction(mesh,1)
    f.pushFunction(lambda p: [0])
    f_vec = f.vec_export()
    u0.vec_import(v0);
    bc = BoundaryCondition("DIRICHLET",u0)
    fbc = bc.apply(f_vec);
    FD = FiniteDifference(mesh)
    M = FD.LaplaceOp(bc)+FD.BoundaryOp(bc);
    u_vec = GauBSeidel(M,fbc,v0,2000)
    ue = MeshFunction(mesh,1);
    ue.pushFunction(lambda p: [p[0]]);
    ue_vec = ue.vec_export();
    err = u_vec+(-1)*ue_vec;
    assert abs(err.norm(2))<tol; 
def test_PDE_Elliptic_1D_Test2():
    I = line(-1.0,1.0)
    mesh = Mesh(1);
    mesh.UniformMesh(I,0.025)
    u0 = MeshFunction(mesh,1)
    u0.pushFunction(lambda P: [0])
    u0_vec = u0.vec_export()
    v0 = vec(u0_vec.len())
    v0[1]=1.0;
    v0[v0.len()]=1.0;
    u0.vec_import(v0);
    f = MeshFunction(mesh,1)
    f.pushFunction(lambda p: [0])
    f_vec = f.vec_export()
    bc = BoundaryCondition("DIRICHLET",u0)
    fbc = bc.apply(f_vec);
    FD = FiniteDifference(mesh)
    q = MeshFunction(mesh,1);
    q.pushFunction(lambda p: [1])
    K1 = FD.ReactionOp(bc,q);
    K2 = FD.LaplaceOp(bc);
    K = K1+(-1.00)*K2+FD.BoundaryOp(bc);
    u = MeshFunction(mesh,1)
    u.pushFunction(lambda p: [0])
    u_vec = u.vec_export()
    u_vec = GauBSeidel(K,fbc,fbc,6000)
    u.vec_import(u_vec)
    ue = MeshFunction(mesh,1);
    ue.pushFunction(lambda p: [(1/(1+exp(2)))*(exp(1-p[0])+exp(p[0]+1))]);
    u_vec = u.vec_export()
    ue_vec = ue.vec_export()
    err = u_vec+(-1)*ue_vec;
    assert abs(err.norm(2))<tol; 
def test_PDE_Elliptic_1D_Test3():
    I = line(0.0,1.0)
    mesh = Mesh(1);
    mesh.UniformMesh(I,0.05)
    u0 = MeshFunction(mesh,1)
    u0.pushFunction(lambda P: [0])
    u0_vec = u0.vec_export()
    v0 = vec(u0_vec.len())
    v0[1]=0.0;
    v0[v0.len()]=1.0;
    u0.vec_import(v0);
    f = MeshFunction(mesh,1)
    f.pushFunction(lambda p: [0])
    f_vec = f.vec_export()
    bc = BoundaryCondition("DIRICHLET",u0)
    fbc = bc.apply(f_vec);
    FD = FiniteDifference(mesh)
    p = MeshFunction(mesh,1);
    p.pushFunction(lambda p: [1])
    K1 = FD.LaplaceOp(bc);
    K2 = FD.TransportOp(bc,p);
    K = (-1.0)*K1+K2+FD.BoundaryOp(bc);
    u = MeshFunction(mesh,1)
    u.pushFunction(lambda p: [0])
    u_vec = u.vec_export()
    u_vec = GauBSeidel(K,fbc,fbc,10000)
    u.vec_import(u_vec)
    ue = MeshFunction(mesh,1);
    ue.pushFunction(lambda p: [(1/(exp(1)-1))*(exp(p[0])-1)]);
    u_vec = u.vec_export()
    ue_vec = ue.vec_export()
    err = u_vec+(-1)*ue_vec;
    assert abs(err.norm(2))<tol; 

def test_PDE_Parabolic_1D_Test1():
    I = line(-1.0,1.0)
    mesh = Mesh(1);
    mesh.UniformMesh(I,0.25)
    # we now define the initial data over the above constructed mesh, and draw it,
    # $$u_0(x) = (x^2-1)$$
    u0 = MeshFunction(mesh,1)
    u0.pushFunction(lambda P: [(-P[0]**2+1)])
    u0_vec = u0.vec_export()
    # We then create an spatial approximation of the Laplace operator with Dirichlet boundary conditions and use this to generate the stiffness matrix $K$, then we construct the mass matrix $M$.
    bc = BoundaryCondition("DIRICHLET",u0)
    FD = FiniteDifference(mesh)
    K = FD.LaplaceOp(bc)+FD.BoundaryOp(bc);
    M = spmat(K.Width(),K.Height())
    N = spmat(K.Width(),K.Height())
    N.empty();
    # Now we use the forward Euler method to solve the systems of ODEs represented by the following same discrete equations:
    # $$M\vec{U}'(t)-K\vec{U}(t) = 0$$
    DiffEq = LinearODEs(1);
    DiffEq.setDomain(0,6.0)
    DiffEq.setCoeff(0,lambda t : N)
    DiffEq.setCoeff(1,lambda t : (-1)*K)
    DiffEq.setCoeff(2,lambda t : M)
    DiffEq.setIC([u0_vec])
    DiffEq.setSolver("JACOBI",500);
    [H, u] = DiffEq.Euler(0.005)
    ut = MeshFunction(mesh,1)
    ut.pushFunction(lambda P: [0])
    ut.vec_import(u[0])
    assert(u[-1].norm(2)<tol);
def test_PDE_Elliptic_2D_Test_1():
    mesh = Mesh(2); #We initzialize a 2D mesh
    #We create a uniform mesh on the square [0,1]x[0,1] of N elements
    mesh.UniformSqMesh([0.0,1.0,0.0,1.0],23);
    #We now use a distance function to define the geometry of the domain
    #where we want to solve the BVP with a finite difference scheme
    Geo = Geometry(2);
    def distSquare(P):
        """
        y2 -> *----------*
               |          |
               |          |
               |          |
        y1 -> *----------*
               ^          ^
               |x1        |x2
        """
        x1 = 0; x2 = 1; y1 = 0; y2=1;
        return max([P[0]-x2,x1-P[0],P[1]-y2,y1-P[1]])
    Geo.add(distSquare) #We add the distance function to the geometry

    #We define a function for the B.C.
    def G(x,y):
        if x==0.0:
            return 0.0;
        elif x==1.0:
            return np.cos(np.pi*y);
        elif y==0.0:
            return x**2;
        elif y==1.0:
            return -(x**2);
        else:
            return 0.0;
    #We place the function G on the mesh creating the mesh function g
    g = MeshFunction(mesh,1)
    g.pushFunction(lambda p: [G(p[0],p[1])])
    #We define Dirichlet B.C on the above defined geometry
    bc = BoundaryCondition("DIRICHLET",g,Geo)
    FD = FiniteDifference(mesh)#We decalre we are using classic finite difference
    #Then we construct the matrix rappresenting the Laplace operator and boudary operator
    K = FD.LaplaceOp(bc)+FD.BoundaryOp(bc);
    #We define the known term f, as a mesh function
    f = MeshFunction(mesh,1)
    f.pushFunction(lambda p: [(2-(np.pi*p[0])**2)*np.cos(np.pi*p[1])])
    f_vec = f.vec_export();
    #We apply the B.C. modifying the vector F, of the system AU=F
    f_bc = bc.apply(f_vec);
    #Solve the linear system
    uhnp = solve(spmat2npmat(K),np.array(f_bc.to_Array()));
    #load the solution of the linear system in a mesh function
    uh = MeshFunction(mesh,1)
    uh.pushFunction(lambda p: [0*p[0]+0*p[1]])
    uh_vec = uh.vec_export()
    uh_vec.from_Array(uhnp);
    uh.vec_import(uh_vec);
    u = MeshFunction(mesh,1)
    u.pushFunction(lambda p: [(p[0]**2)*np.cos(np.pi*p[1])])
    u_vec = u.vec_export()
    err = MeshFunction(mesh,1)
    err.pushFunction(lambda p: [0*p[0]+0*p[1]])
    err_vec = u_vec+(-1)*uh_vec;
    err.vec_import(err_vec)
    assert abs(err.norm(2))<1e-4; 

