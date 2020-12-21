import sys
sys.path.append('../Py/Build');
tol = 1e-7;
from suite import *

def test_Parallel_Dense_Cholesky():
    print("Testing Cholesky decomposition runed in parallel ...");
    A = mat(3,3);
    A.parallel = True;
    A.from_Array([1.0,2.0,1.0,  2.0,8.0,4.0,  1.0,4.0,11.0])
    L = mat(3,3);
    L = Cholesky(A);
    exactL = mat(3,3);
    exactL.from_Array([1.0,0.0,0.0,     2.0,2.0,0.0,        1.0,1.0,3.0]);
    flag = True;
    for i in range(1,4):
        for j in range(1,4):
            flag = flag and (abs(L[i,j]-exactL[i,j])<tol);
    assert flag;
