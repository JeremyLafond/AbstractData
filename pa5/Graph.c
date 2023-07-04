/*
Jeremy Lafond
jalafond
pa5
*/
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj
{
	List *neighbor;
	int *color;
	int *parent;
	int *discover;
	int *finish;
	int order;
	int size;
} GraphObj;

/*** Constructors-Destructors ***/

//returns a graph pointing to a new graphObj with n vertices and no edges
Graph newGraph(int n)
{
	Graph graph = malloc(sizeof(GraphObj));
	graph->order = n;
	graph->size = 0;
	graph->neighbor = calloc(n + 1, sizeof(List));
	graph->neighbor[0] = NULL; //skip first element for sake of graph design
	graph->color = calloc(n + 1, sizeof(int));
	graph->parent = calloc(n + 1, sizeof(int));
	graph->discover = calloc(n + 1, sizeof(int));
	graph->finish = calloc(n + 1, sizeof(int));
	for(int j = 0; j <= n; j++)
	{
		graph->neighbor[j] = newList();
		graph->parent[j] = NIL;
		graph->discover[j] = UNDEF;
		graph->color[j] = white;
		graph->finish[j] = UNDEF;
	}
	return graph;
}

//frees dynamic memory of pG and sets it to null
void freeGraph(Graph* pG)
{
	if(*pG == NULL)
	{
		return;
	}
	Graph fGraph = *pG;
	for(int j = 0; j < fGraph->order + 1; j++)
	{
		freeList(&fGraph->neighbor[j]);
	}
	free(fGraph->neighbor);
	free(fGraph->parent);
	free(fGraph->color);
	free(fGraph->discover);
	free(fGraph->finish);
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/

//returns number of vertices
int getOrder(Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getOrder on NULL graph");
		exit(1);
	}
	return G->order;
}

//returns number of edges
int getSize(Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getSize on NULL graph");
		exit(1);
	}
	return G->size;
}

//returns discover time of u in graph G
//pre: 1 <= u <= order
int getDiscover(Graph G, int u)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getDiscover on NULL graph");
		exit(1);
	}
	if(u > getOrder(G) || u < 1)
	{
		fprintf(stderr, "Graph error: called getDiscover on an out of range vertex");
	}
	return G->discover[u];
}

//returns parent of vertex u
//pre: 1 <= u <= order
int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getParent on NULL graph");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
	{
		fprintf(stderr, "Graph error: parent vertex is out of bounds");
	}
	return G->parent[u];
}
	
//returns finish time of u in graph G
//pre: 1 <= u <= order
int getFinish(Graph G, int u)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getFinish on NULL graph");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
	{
		fprintf(stderr, "Graph error: called getFinish on out of bounds vertex");
	}
	return G->finish[u];
}

/*** Manipulation procedures ***/

//deletes edges of G
void makeNull(Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called makeNull on NULL graph");
		exit(1);
	}
	for(int j = 0; j < G->order + 1; j++)
	{
		clear(G->neighbor[j]);
		G->size = 0;
		G->order = 0;
	}
}

//insert new edge between u and v
//pre: 1 <= u <= order
//pre: 1 <= v <= order
void addEdge(Graph G, int u, int v)
{
	if(u < 1 || u > G->order || v < 1 || v > G->order)
	{
		fprintf(stderr, "Graph error: out of bounds vertex");
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--; //accounting for extra size++ from add calls
}

//inserts new edge from u to v
//pre: 1 <= u <= order
//pre: 1 <= v <= order
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called addArc on NULL graph");
		exit(1);
	}
	if(u < 1 || u > G->order || v < 1 || v > G->order)
	{
		fprintf(stderr, "Graph error: out of bounds vertex");
	}
	List tempList = G->neighbor[u];
	if(length(tempList) == 0)
	{
		append(tempList, v);
		G->size++;
		return;
	}
	for(moveFront(tempList); index(tempList) != -1; moveNext(tempList))
	{
		if(v < get(tempList))
		{
			insertBefore(tempList, v);
			break;
		}
	}
	if(index(tempList) == -1)
	{
		append(tempList, v);
	}
	G->size++;
}

void visit(Graph G, List S, int u, int *time)
{
	G->color[u] = gray;
	G->discover[u] = ++*time;
	List tList = G->neighbor[u];
	moveFront(tList);
	while(index(tList) >= 0)
	{
		int g = get(tList);
		if(G->color[g] == white)
		{
			G->parent[g] = u;
			visit(G, S, g, time);
		}
		moveNext(tList);
	}
	G->color[u] = black;
	G->finish[u] = ++*time;
	prepend(S, u);
}

//runs depth first search on G with List S that defines vertex order.
//also stores finish times in decreasing order.
//Pre: length(S) == n == getOrder(G)
void DFS(Graph G, List S)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called DFS on NULL graph");
		exit(1);
	}
	if(length(S) != getOrder(G))
	{
		fprintf(stderr, "Graph error: called DFS when length != order");
		exit(1);
	}
	for(int j = 1; j <= getOrder(G); j++)
	{
		G->color[j] = white;
		G->parent[j] = NIL;
		G->discover[j] = UNDEF;
		G->finish[j] = UNDEF;
	}
	int time = 0;
	moveFront(S);
	while(index(S) >= 0)
	{
		int vert = get(S);
		if(G->color[vert] == white)
		{
			visit(G, S, vert, &time);
		}
		moveNext(S);
	}
	for(int j = 0; j < getOrder(G); j++)
	{
		deleteBack(S);
	}
}

//returns transpose of G
//transpose flips direction of edges
Graph transpose(Graph G)
{
	Graph tGraph = newGraph(G->order);
	for(int j = 0; j <= getOrder(G); j++)
	{
		List tList = G->neighbor[j];
		moveFront(tList);
		while(index(tList) >= 0)
		{
			addArc(tGraph, get(tList), j);
			moveNext(tList);
		}
	}
	return tGraph;
}

//returns copy of graph G
Graph copyGraph(Graph G)
{
	Graph cGraph = newGraph(G->order);
	for(int j = 0; j <= getOrder(G); j++)
	{
		List cList = G->neighbor[j];
		moveFront(cList);
		while(index(cList) >= 0)
		{
			addArc(cGraph, j, get(cList));
			moveNext(cList);
		}
	}
	return cGraph;
}

/*** Other operations ***/

//prints adjacency list representation of G to file "out"
void printGraph(FILE* out, Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called printGraphy on NULL graph");
		exit(1);
	}
	if(out == NULL)
	{
		fprintf(stderr, "Graph error: Nowhere to print");
	}
	for(int j = 1; j < G->order + 1; j++)
	{
		fprintf(out, "%d: ", j);
		printList(out, G->neighbor[j]);
		fprintf(out, "\n");
	}
}