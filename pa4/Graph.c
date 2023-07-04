/*
Jeremy Lafond
jalafond
pa4
*/
#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj
{
	List *neighbor;
	int *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
} GraphObj;

/*** Constructors-Destructors ***/

//returns a graph pointing to a new graphObj with n vertices and no edges
Graph newGraph(int n)
{
	Graph graph = malloc(sizeof(GraphObj));
	graph->order = n;
	graph->source = NIL;
	graph->size = 0;
	graph->neighbor = calloc(n + 1, sizeof(List));
	graph->neighbor[0] = NULL; //skip first element for sake of graph design
	graph->color = calloc(n + 1, sizeof(int));
	graph->parent = calloc(n + 1, sizeof(int));
	graph->distance = calloc(n + 1, sizeof(int));
	for(int j = 0; j <= n; j++)
	{
		graph->neighbor[j] = newList();
		graph->parent[j] = NIL;
		graph->distance[j] = INF;
		graph->color[j] = white;
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
	free(fGraph->distance);
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

//returns most recently used source vertex
int getSource(Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getSource on NULL graph");
		exit(1);
	}
	return G->source; // NIL if pre BFS
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
	
//returns distance from source to u
//pre: 1 <= u <= order
int getDist(Graph G, int u)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getDist on NULL graph");
		exit(1);
	}
	if(G->source == NIL) //pre BFS call
	{
		return INF;
	}
	if(u < 1 || u > G->order)
	{
		fprintf(stderr, "Graph error: out of bounds vertex");
	}
	return G->distance[u];
}

//appends vertices of shortest path in G from source to u to the List L
//pre: getSource(G)!=NIL
//pre: 1 <= u <= order
void getPath(List L, Graph G, int u)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called getPath on NULL graph");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
	{
		fprintf(stderr, "Graph error: out of bounds vertex");
	}
	int temp = G->source;
	if(u == temp)
	{
		append(L, temp);
	}
	else if(G->parent[u] == NIL)
	{
		append(L, NIL);
	}
	else
	{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
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
		G->source = NIL;
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

//runs Breadth first search on G with source s
void BFS(Graph G, int s)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: called BFS on NULL graph");
		exit(1);
	}
	for(int j = 0; j < getOrder(G) + 1; j++)
	{
		G->color[j] = white;
		G->distance[j] = INF;
		G->parent[j] = NIL;
	}
	G->source = s;
	G->color[s] = gray;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List q = newList();
	append(q, s);
	while(length(q) > 0)
	{
		int tempFront = front(q);
		deleteFront(q);
		List tempList = G->neighbor[tempFront];
		for(moveFront(tempList); index(tempList) != -1; moveNext(tempList))
		{
			int t = get(tempList);
			if(G->color[t] == white)
			{
				G->color[t] = gray;
				G->distance[t] = G->distance[tempFront] + 1;
				G->parent[t] = tempFront;
				append(q, t);
			}
		}
		G->color[tempFront] = black;
	}
	freeList(&q);
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