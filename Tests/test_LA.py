import sys
sys.path.append('../Py/Build');
tol = 1e-7;
from suite import *
def test_LA_dot_product():
    print("Testing dot product ...");
    v = vec(3);
    v.from_Array([1.0,1.0,4.0])
    w = vec(3);
    w.from_Array([0.5,0.5,0.25])
    assert abs((v*w)-2)<tol;
def test_LA_norm():
    print("Testing vector norm ...");
    v = vec(3);
    v.from_Array([2.0,2.0,1.0]);
    assert abs(v.norm(2)-3)<tol;
def test_LA_dense_matrix_mul():
    print("Testing dense matrix matrix multiplication ...");
    A = mat(3,3);
    A[1,1] = 1; A[2,2] = 2; A[3,3] = 3;
    A[1,2] = 1;
    B = mat(3,3);
    B[1,1] = 3; B[2,2] = 4; B[3,3] = 3;
    B[1,2] = 2;B[1,3] = 1;
    C = mat(3,3);
    C[1,1] = 3; C[1,2] = 6; C[1,3] = 1;
    C[2,2] = 8; C[3,3] = 9;
    print(A*B);
    print(C);
    flag = True;
    for i in range(1,4):
        for j in range(1,4):
            flag = flag and (abs((A*B)[i,j]-C[i,j])<tol);
    assert flag;
def test_LA_dense_backsub():
    print("Testing backward substitution for linear systems");
    A = mat(3,3);
    b = vec(3);
    A.from_Array([1.0,1.0,1.0,   0.0,1.0,1.0,   0.0,0.0,1.0])
    b.from_Array([1.0,2.0,3.0]);
    L = LinSys(A,b);
    L.setType("UPPER");
    x = vec(3);
    x = L.BackSub();
    s = vec(3);
    s.from_Array([-1.0,-1.0,3.0]);
    flag = True;
    for i in range(1,4):
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;
def test_LA_dense_forwardsub():
    print("Testing forward substitution for linear systems");
    A = mat(3,3);
    b = vec(3);
    A.from_Array([1.0,0.0,0.0,   1.0,1.0,0.0,   1.0,1.0,1.0])
    b.from_Array([1.0,2.0,3.0]);
    L = LinSys(A,b);
    L.setType("LOWER");
    x = vec(3);
    x = L.ForwardSub();
    s = vec(3);
    s.from_Array([1.0,1.0,1.0]);
    flag = True;
    for i in range(1,4):
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;
def test_LA_dense_GE_No_Pivot():
    print("Testing for Gaussian Elimination with out pivoting");
    A = mat(3,3);
    A.from_Array([3.0,1.0,6.0,   2.0,1.0,3.0,   1.0,1.0,1.0])
    b = vec(3);
    b.from_Array([2.0,7.0,4.0]);
    L = LinSys(A,b);
    L.Gauss(0);
    x = vec(3);
    x = L.BackSub();
    print("x: ",x)
    s = vec(3);
    s.from_Array([19.0,-7.0,-8.0]);
    flag = True;
    for i in range(1,4):
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;
def test_LA_dense_GE_Abs_Pivoting():
    print("Testing for Gaussian Elimination with absolute pivoting");
    A = mat(2,2);
    A.from_Array([10**(-4),1.0,   1.0,1.0])
    b = vec(2);
    b.from_Array([1.0,1.0]);
    L = LinSys(A,b);
    L.Gauss(2);
    x = vec(2);
    x = L.BackSub();
    print("x: ",x)
    s = vec(2);
    s.from_Array([0.0,1.0]);
    flag = True;
    for i in range(1,3):
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;
def test_LA_dense_GE_Complete_Pivoting():
    print("Testing for Gaussian Elimination with complete pivoting");
    A = mat(2,2);
    A.from_Array([2.0,2.0*(10**4),   1.0,1.0])
    b = vec(2);
    b[1] = 2.0*(10**4); b[2] = 2.0;
    L = LinSys(A,b);
    L.Gauss(3)
    print(L)
    x = vec(2);
    x = L.BackSub();
    print("x: ",x)
    s = vec(2);
    s.from_Array([1.000100,0.999900]);
    flag = True;
    for i in range(1,3):
        print(x[i],s[i]);
        print(abs(x[i]-s[i]))
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;

