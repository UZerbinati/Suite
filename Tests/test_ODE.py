import sys
sys.path.append('../Py/Build');
tol = 1e-6;
from math import exp
from suite import *
import pytest
def test_ODE_basic():
   print("Testing for u'=u, u(0)=1"); 
   DiffEq = LinearODE(1);
   DiffEq.setDomain(0,2);
   DiffEq.setCoeff(0,lambda t : 0)
   DiffEq.setCoeff(1,lambda t : -1)
   DiffEq.setIC(1.0)
   [H,u] = DiffEq.ScalarEuler(1e-8);
   assert (abs(u[-1]-exp(2))< tol);

