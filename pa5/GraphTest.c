/*
Jeremy Lafond
jalafond
pa5
*/
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{ 
	int j;
	List stuff = newList();
	Graph graph = newGraph(10);
	Graph graph2 = newGraph(5);
	Graph cGraph = NULL;
	Graph tGraph = NULL;
	for(j = 1; j <= 10; j++)
	{
		append(stuff, j);
	}
	printf("The order is: %d \n", getOrder(graph));
	printf("The size is: %d \n", getSize(graph));
	addArc(graph, 1, 2);
	addArc(graph, 1, 5);
	addArc(graph, 2, 5);
	addArc(graph, 2, 6);
	addArc(graph, 3, 2);
	addArc(graph, 3, 4);
	addArc(graph, 4, 6);
	addArc(graph, 4, 7);
	addArc(graph, 5, 8);
	addArc(graph, 6, 5);
	addArc(graph, 7, 7);
	addArc(graph, 8, 4);
	addArc(graph, 8, 7);
	addArc(graph, 9, 3);
	addArc(graph, 9, 6);
	addArc(graph, 10, 2);
	printGraph(stdout, graph);
	printf("Size: %d \n", getSize(graph));
	printf("Order: %d \n", getOrder(graph));
	DFS(graph, stuff);
	fprintf(stdout, "\n");
	fprintf(stdout, "x:  d  f  p\n");
	for(j = 1; j <= 10; j++)
	{
		fprintf(stdout, "%d: %2d %2d %2d\n", j,
		getDiscover(graph, j),
		getFinish(graph, j),
		getParent(graph, j));
	}
	fprintf(stdout, "\n");
	printList(stdout, stuff);
	fprintf(stdout, "\n");
	tGraph = transpose(graph);
	cGraph = copyGraph(graph);
	fprintf(stdout, "\n");
	printGraph(stdout, cGraph);
	fprintf(stdout, "\n");
	printGraph(stdout, tGraph);
	fprintf(stdout, "\n");
	printf("Transpose order: %d \n", getOrder(tGraph));
	printf("Transpose size: %d \n", getSize(tGraph));
	printf("Copy order: %d \n", getOrder(cGraph));
	printf("Copy size: %d \n", getSize(cGraph));
	DFS(tGraph, stuff);
	fprintf(stdout, "\n");
	fprintf(stdout, "x:  d  f  p\n");
	for(j = 1; j <= 10; j++)
	{
		fprintf(stdout, "%d: %2d %2d %2d\n", j,
		getDiscover(tGraph, j),
		getFinish(tGraph, j),
		getParent(tGraph, j));
	}
	printf("Transpose order: %d \n", getOrder(tGraph));
	printf("Transpose size: %d \n", getSize(tGraph));
	fprintf(stdout, "\n");
	printList(stdout, stuff);
	fprintf(stdout, "\n");
	addEdge(graph2, 1, 2);
	addEdge(graph2, 1, 5);
	addEdge(graph2, 2, 5);
	addEdge(graph2, 2, 3);
	addEdge(graph2, 3, 4);
	addEdge(graph2, 4, 1);
	addEdge(graph2, 5, 3);
	fprintf(stdout, "\n");
	printGraph(stdout, graph2);
	fprintf(stdout, "\n");
	printf("Order: %d \n", getOrder(graph2));
	printf("Size: %d \n", getSize(graph2));
	makeNull(graph2);
	fprintf(stdout, "\n");
	printGraph(stdout, graph2);
	fprintf(stdout, "\n");
	printf("Order: %d \n", getOrder(graph2));
	printf("Size: %d \n", getSize(graph2));
	freeGraph(&graph);
	freeGraph(&graph2);
	freeGraph(&tGraph);
	freeGraph(&cGraph);
	freeList(&stuff);
	return(0);
}