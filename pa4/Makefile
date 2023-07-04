#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 4
#
#       make                   makes FindPath
#       make GraphClient       makes GraphClient
#		clean				   removes .o files
#------------------------------------------------------------------------------

FindPath : FindPath.o Graph.o List.o
	gcc -o FindPath FindPath.o List.o Graph.o

FindPath.o : FindPath.c List.h Graph.h
	gcc -c -std=c99 -Wall FindPath.c

GraphClient: GraphClient.o List.o Graph.o
	gcc -o GraphClient GraphClient.o List.o Graph.o

GraphClient.o : GraphClient.c List.h Graph.h
	gcc -c -std=c99 -Wall GraphClient.c

List.o Graph.o : List.c Graph.c List.h Graph.h
	gcc -c -std=c99 -Wall List.c Graph.c

clean :
	rm -f FindPath GraphClient FindPath.o GraphClient.o List.o Graph.o