# -*- coding: utf-8 -*-

import numpy as np;

# class AHP:

#   Xid = []
#   Nid = []
#   N=[]
#   L = 0

#   def __init__(self,L):
#     self.L = L
#     N = np.zeros(L)
#     for i in N:
#       Nid.append(raw_input('Please input the name if Layer ' + str(i+1) + ':')) 
#       N[i] = input('Please input the number of var in Layer' + Nid[i])
#       for j in N

class Layer:

  N = 0
  Xid = []
  Val = []

  W = []
  string = ''
  
  def __init__(self,N):

    Xid = []

    #input name of vars
    print 'The name of vars should be no longer than 10 char.'
    for i in range(N):
      Xid.append(raw_input('Please input the name of var ' + str(i+1) + ':')[0:7])

    Val = np.mat(np.diag(np.ones(N)))
    #input Val Matrix
    for i in range(N):
      for j in range(i+1,N):
        Val[i,j] = input( Xid[i] + ' & ' + Xid[j] + ':')
        Val[j,i] = 1/Val[i,j]

    [n,W] = np.linalg.eig(Val.T) # count eig
    n = np.argmax(n)             # find the max eig value
    W = np.real(np.multiply(1.0/W.sum(axis=0),W))  # tranfrom to real type and normalized

    self.N = N
    self.Xid = Xid
    self.Val = Val
    self.W = W[:,n].T

  def __repr__(self):
    string = '\n==============================\n'
    string += 'Total ' + str(self.N) + ' var: '
    for xstr in self.Xid:
      string += xstr + ' '
    string += '\n===============================\nYour Value:\n\t'
    for xstr in self.Xid:
      string += xstr + '\t'
    for i in range(self.N):
      string += '\n' + self.Xid[i] 
      for j in range(self.N):
        string += '\t' + str(self.Val[i,j].round(5))
    string += '\n==============================\n'
    string += 'The Weight is:\n' + str(self.W)
    string += '\n==============================\n'

    return string

  def jug_help(self):
    print 'List of importance comparison:'
    print '1:Equal importance'
    print '2:Equal to moderate importance'
    print '3:Moderate importance'
    print '4:Moderate to strong importance'
    print '5:Strong importance'
    print '6:Strong to very strong importance'
    print '7:Very strong importance'
    print '8:Very to extremely strong importance'
    print '9:Extremely strong importance'
    print 'Please input the importance value between'



x = Layer(3)
print x