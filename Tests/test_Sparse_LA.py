import sys
sys.path.append('../Py/Build');
tol = 1e-7;
from suite import *
def test_Sparse_LA_matrix_vector_mul():
    v = vec(4)
    v.from_Array([0.5,2,3,4])
    A = spmat(4,4)
    A[1,1] = 2
    s = vec(4);
    s.from_Array([1.0,2.0,3.0,4.0]);
    flag = True;
    for i in range(1,5):
        flag = flag and (abs((A*v)[i]-s[i])<tol);
    assert flag;
def test_Sparse_LA_Jacobi():
    A = spmat(3,3)
    A[1,1]=3;    A[1,2]=1;    A[1,3]=-1;
    A[2,1]=0;    A[2,2]=-2;    A[2,3]=1;
    A[3,1]=2;    A[3,2]=-2;    A[3,3]=5;
    b = vec(3);
    b.from_Array([2,0,10]);
    x0 = vec(3);
    x0.from_Array([0,0,0]);
    x = vec(3);
    x = Jacobi(A,b,x0,200);
    print(x);
    s = vec(3);
    s.from_Array([1.0,1.0,2.0]);
    print(s);
    flag = True;
    for i in range(1,4):
        print(abs(x[i]-s[i]));
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;
def test_Sparse_LA_Gauss_Seidel():
    A = spmat(3,3)
    A[1,1]=3;    A[1,2]=1;    A[1,3]=-1;
    A[2,1]=0;    A[2,2]=-2;    A[2,3]=1;
    A[3,1]=2;    A[3,2]=-2;    A[3,3]=5;
    b = vec(3);
    b.from_Array([2,0,10]);
    x0 = vec(3);
    x0.from_Array([0,0,0]);
    x = vec(3);
    x = GauBSeidel(A,b,x0,100);
    print(x);
    s = vec(3);
    s.from_Array([1.0,1.0,2.0]);
    print(s);
    flag = True;
    for i in range(1,4):
        print(abs(x[i]-s[i]));
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;
def test_Sparse_LA_SOR():
    A = spmat(3,3)
    A[1,1]=3;    A[1,2]=1;    A[1,3]=-1;
    A[2,1]=0;    A[2,2]=-2;    A[2,3]=1;
    A[3,1]=2;    A[3,2]=-2;    A[3,3]=5;
    b = vec(3);
    b.from_Array([2,0,10]);
    x0 = vec(3);
    x0.from_Array([0,0,0]);
    x = vec(3);
    x = SOR(A,b,x0,1.2,100);
    print(x);
    s = vec(3);
    s.from_Array([1.0,1.0,2.0]);
    print(s);
    flag = True;
    for i in range(1,4):
        print(abs(x[i]-s[i]));
        flag = flag and (abs(x[i]-s[i])<tol);
    assert flag;
