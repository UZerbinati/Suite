
Gaussian Elimination
====================

In this notebook we show the class implemented to solve dense linear
systems wrapped from C++ using PyBind11. In particular we will study six
examples, the first three are provided in Lecture 6 of the Numerical
Linear Algebra course at KAUST. The aim of the first three example would
be to show the difference between "naive" Gaussian elimination, Gaussian
elimination with partial pivoting and Gaussian elimination with complete
pivoting. Unfortunately those example where designed for a 3-decimal
floating point arithmetic while the matrix, vector and linear system
classes were implemented in a double precision arithmetic. For this
reason we introduce Example 4 and Example 5, which should show the
advantage respectively of partial and complete pivoting in a double
precision arithmetic. We will use two function of the linear system
class, the first is Gauss(int n) that perform the Gaussian elimination,
where the number n identify the type of pivoting we wont: - n = 0, we do
Naive Gaussian elimination; - n = 1, we do partial Gaussian elimination
searching for non zero pivot; - n = 2, we do partial Gaussian
elimination searching for pivot with greatest magnitude; - n = 3, we do
complete Gaussian elimination. The second is BackSub(), which perform
backward substitution swapping the unknown when needed.

.. code:: ipython3

    import sys
    sys.path.append('../../../Py/Build')
    from suite import *

Example 1
~~~~~~~~~

.. code:: ipython3

    A = mat(3,3);
    A.from_Array([3.0,1.0,6.0,   2.0,1.0,3.0,   1.0,1.0,1.0])
    b = vec(3);
    b[1] = 2.0; b[2] = 7.0; b[3]=4.0;
    L = LinSys(A,b);
    L




.. parsed-literal::

    [3.000000,1.000000,6.000000]
    [2.000000,1.000000,3.000000]
    [1.000000,1.000000,1.000000]
    
    (2.000000,7.000000,4.000000)



.. code:: ipython3

    L.Gauss(0)
    L




.. parsed-literal::

    [3.000000,1.000000,6.000000]
    [0.000000,0.333333,-1.000000]
    [0.000000,0.000000,1.000000]
    
    (2.000000,5.666667,-8.000000)



.. code:: ipython3

    L.BackSub()




.. parsed-literal::

    (19.000000,-7.000000,-8.000000)



Example 2
~~~~~~~~~

.. code:: ipython3

    A = mat(2,2);
    A.from_Array([10**(-4),1.0,   1.0,1.0])
    b = vec(2);
    b[1] = 1.0; b[2] = 1.0;
    L = LinSys(A,b);
    L




.. parsed-literal::

    [0.000100,1.000000]
    [1.000000,1.000000]
    
    (1.000000,1.000000)



.. code:: ipython3

    L.Gauss(0)
    L




.. parsed-literal::

    [0.000100,1.000000]
    [0.000000,-9999.000000]
    
    (1.000000,-9999.000000)



.. code:: ipython3

    L.BackSub()




.. parsed-literal::

    (0.000000,1.000000)



.. code:: ipython3

    A = mat(2,2);
    A.from_Array([10**(-4),1.0,   1.0,1.0])
    b = vec(2);
    b[1] = 1.0; b[2] = 1.0;
    L = LinSys(A,b);
    L.Gauss(2)
    L.BackSub()




.. parsed-literal::

    (0.000000,1.000000)



Example 3
~~~~~~~~~

.. code:: ipython3

    A = mat(2,2);
    A.from_Array([2.0,2.0*(10**4),   1.0,1.0])
    b = vec(2);
    b[1] = 2.0*(10**4); b[2] = 2.0;
    L = LinSys(A,b);
    L




.. parsed-literal::

    [2.000000,20000.000000]
    [1.000000,1.000000]
    
    (20000.000000,2.000000)



.. code:: ipython3

    L.Gauss(0)
    L




.. parsed-literal::

    [2.000000,20000.000000]
    [0.000000,-9999.000000]
    
    (20000.000000,-9998.000000)



.. code:: ipython3

    L.BackSub()




.. parsed-literal::

    (1.000100,0.999900)



.. code:: ipython3

    A = mat(2,2);
    A.from_Array([2.0,2.0*(10**4),   1.0,1.0])
    b = vec(2);
    b[1] = 2.0*(10**4); b[2] = 2.0;
    L = LinSys(A,b);
    L.Gauss(3)
    L




.. parsed-literal::

    [20000.000000,2.000000]
    [0.000000,0.999900]
    
    (20000.000000,1.000000)



.. code:: ipython3

    L.BackSub()




.. parsed-literal::

    (1.000100,0.999900)



Example 4
~~~~~~~~~

In this example we show the advantage of using partial pivoting compared
with naive Gaussian elimination. We consider the linear system
:math:`A\vec{x} = \vec{b}`, where:

.. math::

   A=\begin{pmatrix}
       0 & 1 \\
       1 & 1
   \end{pmatrix}\qquad\qquad \vec{b} = \begin{pmatrix}
   1
   \\
   0
   \end{pmatrix}

 we know the solution to the problem is given by the vector:

.. math::

   \vec{x} = \begin{pmatrix}
   -1 \\ 1
   \end{pmatrix}

 we now perturbate the matrix :math:`A` by a factor :math:`10^{-20}`
that is smaller then the machine epsilon, and try to solve the linear
system using "naive" Gaussian elimination.

.. code:: ipython3

    A = mat(2,2);
    A.from_Array([10**(-20),1.0,   1.0,1.0])
    b = vec(2);
    b[1] = 1.0; b[2] = 0.0;
    L = LinSys(A,b);
    L.Gauss(0)
    L.BackSub()




.. parsed-literal::

    (0.000000,1.000000)



We clearly find the wrong answer, this is because when subtracting the
first row the second row we yield :math:`1-10^{20}`, which can't be
represented exactly in double precision (IEEE754 has a 15–17 decimals
precision). To avoid this we simply perform Gaussian elimination with
partial pivoting. Since we swap the two rows of the matrix we end up
immediately with an upper triangular matrix.

.. code:: ipython3

    A = mat(2,2);
    A.from_Array([10**(-20),1.0,   1.0,1.0])
    b = vec(2);
    b[1] = 1.0; b[2] = 0.0;
    L = LinSys(A,b);
    L.Gauss(2)
    L.BackSub()




.. parsed-literal::

    (-1.000000,1.000000)



Example 5
~~~~~~~~~

Similar problem as the one above occurs when we work with the matrix:

.. math::

   A = \begin{pmatrix}
   2 & 2(10^{20})\\
   1 & 1
   \end{pmatrix} \qquad\qquad \vec{b}=\begin{pmatrix}
   2(10^{20})\\
   2
   \end{pmatrix}

 the exact result would be:

.. math::

   \vec{x} = \begin{pmatrix}
       1+10^{-20} \\
       1-10^{-20}
   \end{pmatrix}

 when we perform naive Gaussian elimination and Gaussian elimination the
same phenomena as in Example 4 occurs and therefore we obtain the wrong
solution:

.. math::

   \vec{x} = \begin{pmatrix}
   0\\
   1
   \end{pmatrix}

.. code:: ipython3

    A = mat(2,2);
    A.from_Array([2.0,2.0*(10**20),   1.0,1.0])
    b = vec(2);
    b[1] = 2.0*(10**20); b[2] = 2.0;
    L = LinSys(A,b);
    L.Gauss(0)
    L.BackSub()




.. parsed-literal::

    (0.000000,1.000000)



.. code:: ipython3

    A = mat(2,2);
    A.from_Array([2.0,2.0*(10**20),   1.0,1.0])
    b = vec(2);
    b[1] = 2.0*(10**20); b[2] = 2.0;
    L = LinSys(A,b);
    L.Gauss(2)
    L.BackSub()




.. parsed-literal::

    (0.000000,1.000000)



Instead with complete pivoting we obtain the solution
:math:`\vec{x} = (1,1)` that is the correct solution in floating points
arithmetic since the epsilon machine is around :math:`10^{-16}`.

.. code:: ipython3

    A = mat(2,2);
    A.from_Array([2.0,2.0*(10**20),   1.0,1.0])
    b = vec(2);
    b[1] = 2.0*(10**20); b[2] = 2.0;
    L = LinSys(A,b);
    L.Gauss(3)
    L.BackSub()




.. parsed-literal::

    (1.000000,1.000000)


