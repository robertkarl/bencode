from sys import argv
x = argv[1]

i = 0
s = ""
while i < len(argv[1]):
	s += '%'
	s += x[i]
	i += 1
	s +=  x[i]
	i += 1
print s
