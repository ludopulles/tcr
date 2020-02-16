# reading input:
from sys import *
n,m = [ int(x) for x in stdin.readline().rstrip().split() ]
stdout.write( str(n*m)+"\n" )
# set operations:
from itertools import *
for (x,y) in product(range(3),repeat=2):
	stdout.write( str(3*x+y)+" " )
print()
for L in combinations(range(4),2):
	stdout.write( str(L)+" " )
print()
# fancy lambdas:
from functools import *
y = reduce( lambda x,y: x+y, map( lambda x: x*x, range(4) ), -3 )
print(y)
# formatting:
from math import *
stdout.write( "{0:.2f}\n".format(pi) )
