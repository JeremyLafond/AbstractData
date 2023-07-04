#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 5
#
#       make                   makes FindComponents
#       GraphTest     		   makes GraphTest
#		clean				   removes .o files
#------------------------------------------------------------------------------

FindComponents : FindComponents.o Graph.o List.o
	gcc -o FindComponents FindComponents.o List.o Graph.o

FindComponents.o : FindComponents.c List.h Graph.h
	gcc -c -std=c99 -Wall FindComponents.c

GraphTest: GraphTest.o List.o Graph.o
	gcc -o GraphTest GraphTest.o List.o Graph.o

GraphTest.o : GraphTest.c List.h Graph.h
	gcc -c -std=c99 -Wall GraphTest.c

List.o Graph.o : List.c Graph.c List.h Graph.h
	gcc -c -std=c99 -Wall List.c Graph.c

clean :
	rm -f FindComponents GraphTest FindComponents.o GraphTest.o List.o Graph.o