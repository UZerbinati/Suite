import sys
sys.path.append('../Py/Build');
tol = 1e-4;
from math import exp
from suite import *
import pytest
def test_ODE_basic():
    print("Testing for u'=u, u(0)=1"); 
    DiffEq = LinearODE(1);
    DiffEq.setDomain(0,2);
    DiffEq.setCoeff(0,lambda t : 0)
    DiffEq.setCoeff(1,lambda t : -1)
    DiffEq.setIC([1.0])
    [H,u] = DiffEq.Euler(1e-6);
    assert (abs(u[-1]-exp(2))< tol);
def test_ODE_nonlinear_1():
    """
        dy/dx = -y^2
        y(x) =  1/(x+1);
    """
    DiffEq = NonLinearODE(1);
    DiffEq.setDomain(0,2);
    DiffEq.setCoeff(lambda t : 1,lambda Dy,t: -Dy[0]**2)
    DiffEq.setIC([1.0]);
    [H,u] = DiffEq.Euler(1e-6);
    assert (abs(u[-1]-1/3)<tol);

