import sys
sys.path.append('../../../Py/Build')
from suite import *
from random import sample

#We create a vector and we pass at us result.
def ex1():
    v = vec(10000);
    v.from_Array(sample(range(1,100001),10000));


def ex2():
    v = vec(10000);
    v.from_Array(sample(range(1,100001),10000));
    v.free()
    del v;


def ex3():
    v = vec(10000);
    v.from_Array(sample(range(1,100001),10000));
    del v;

def ex4():
    A = sample(range(1,100001),10000);
    del A;