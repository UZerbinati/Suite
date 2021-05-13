import sys
sys.path.append('../Py/Build');
tol = 1e-4
from suite import *
from math import exp
def test_PDE_Elliptic_1D_Test2():
    print("TEST 0");
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
    K2 = (-1.0)*FD.LaplaceOp(bc);
    K = K1+K2+FD.BoundaryOp(bc);
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
    print(err)
    assert abs(err.norm(2))<tol; 

test_PDE_Elliptic_1D_Test2();
