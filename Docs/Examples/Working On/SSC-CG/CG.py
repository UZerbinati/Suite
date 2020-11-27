#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Nov  1 20:42:24 2020

@author: Umberto Zerbinati
"""

from scipy import io, sparse
import matplotlib.pyplot as plt
A = io.loadmat('A.mat')['A'];
plt.spy(A)
