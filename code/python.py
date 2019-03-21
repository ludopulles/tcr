from sys import *
n,m = [ int(x) for x in stdin.readline().rstrip().split() ]
stdout.write( str(n*m)+"\n" )

from itertools import * 
for (x,y) in product(range(3),repeat=2):
	stdout.write( str(3*x+y)+" " )
stdout.write( "\n" )
for L in combinations(range(4),2):
	stdout.write( str(L)+" " )
stdout.write( "\n" )

from functools import *
y = reduce( lambda x,y: x+y, map( lambda x: x*x, range(4) ), -3 )
stdout.write( str(y)+"\n" )

from math import *
stdout.write( "{0:.2f}\n".format(pi) )