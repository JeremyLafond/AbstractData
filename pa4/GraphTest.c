/*
Jeremy Lafond
jalafond
pa4
*/
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>

void print(FILE* out, Graph g, List list, int n)
{
	fprintf(out, "\n");
	fprintf(out, "The distance from %d to %d is ", getSource(g), n);
	if(front(list) == NIL)
	{
		fprintf(out, "infinite\n");
		fprintf(out, "The path from %d to %d does not exist", getSource(g), n);
	}
	else
	{
		fprintf(out, "%d\n", getDist(g, n));
		fprintf(out, "Shortest %d-%d path: ", getSource(g), n);
		printList(out, list);
	}
	fprintf(out, "\n");
}

int main(int argc, char *argv[])
{
	Graph Y = newGraph(5);
	List glist = newList();
	printf("ORIGINAL:\n");
	printf("parent: %d\n", getParent(Y, 1));
	printf("size: %d\n", getSize(Y));
	printf("order: %d\n", getOrder(Y));
	printf("source: %d\n", getSource(Y));
	printGraph(stdout, Y);
	printf("MODIFIED:\n");
	addArc(Y, 1, 5);
	addArc(Y, 1, 4);
	addArc(Y, 2, 3);
	addArc(Y, 5, 2);
	addArc(Y, 4, 3);
	addArc(Y, 3, 5);
	addArc(Y, 3, 2);
	addArc(Y, 4, 2);
	printGraph(stdout, Y);
	printf("parent: %d\n", getParent(Y, 7));
	printf("size: %d\n", getSize(Y));
	printf("order: %d\n", getOrder(Y));
	printf("source: %d\n", getSource(Y));
	BFS(Y, 4);
	getPath(glist, Y, 3);
	printGraph(stdout, Y);
	makeNull(Y);
	printf("MAKENULL:\n");
	printf("parent: %d\n", getParent(Y, 1));
	printf("size: %d\n", getSize(Y));
	printf("order: %d\n", getOrder(Y));
	printf("source: %d\n", getSource(Y));
	printGraph(stdout, Y);
	printf("SUPER EDGY:\n");
	addEdge(Y, 1, 5);
	addEdge(Y, 1, 4);
	addEdge(Y, 2, 3);
	addEdge(Y, 5, 2);
	addEdge(Y, 4, 3);
	addEdge(Y, 3, 5);
	addEdge(Y, 3, 2);
	addEdge(Y, 4, 2);
	printGraph(stdout, Y);
	printf("parent: %d\n", getParent(Y, 7));
	printf("size: %d\n", getSize(Y));
	printf("order: %d\n", getOrder(Y));
	printf("source: %d\n", getSource(Y));
	BFS(Y, 4);
	getPath(glist, Y, 3);
	printGraph(stdout, Y);
	return 0;
}