import sys
sys.path.append('../Py/Build');
from suite import *
def test_LA_dot_product():
    v = vec(3);
    v.from_Array([1.0,1.0,4.0])
    w = vec(3);
    w.from_Array([0.5,0.5,0.25])
    assert (v*w) == 2;
