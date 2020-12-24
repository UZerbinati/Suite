import sys
sys.path.append('../Py/Build');
tol = 1e-8
from suite import *;
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
    M = FD.LaplaceOp(bc);
    u_vec = GauBSeidel(M,fbc,v0,2000)
    ue = MeshFunction(mesh,1);
    ue.pushFunction(lambda p: [p[0]]);
    ue_vec = ue.vec_export();
    err = u_vec+(-1)*ue_vec;
    assert abs(err.norm(2))<tol;
    
    
