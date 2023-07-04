/*
Jeremy Lafond
jalafond
pa4
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 300
#define INF -1
#define true 0

int main(int argc, char* argv[])
{
	int size;
	FILE *in, *out;
	char lines[MAX_LEN];
	char *temp;
	char* fill = "0 0\n";
	Graph nGraph;
	List gList = newList();
	int u = 0;
	int v = 0;
	if(argc != 3)
	{
		printf("Usage error: <infile> <outfile>\n");
		exit(1);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(out == NULL)
	{
		printf("Write error: cannot open %s to write into. \n", argv[2]);
		exit(1);
	}
	if(in == NULL)
	{
		printf("Read error: cannot open %s to read out of. \n", argv[1]);
		exit(1);
	}
	if(fgets(lines, MAX_LEN, in) == NULL)
	{
		fprintf(stderr, "File Input Error: Invalid File Input");
		exit(1);
	}
	else
	{
		temp = strtok(lines, " \n");
		size = atoi(temp);
		nGraph = newGraph(size);
		temp = strtok(NULL, "\n");
	}
	fgets(lines,MAX_LEN, in);
	while(strcmp(lines, fill) != true)
	{
		temp = strtok(lines, " \n");
		u = atoi(temp);
		temp = strtok(NULL, " \n");
		v = atoi(temp);
		temp = strtok(NULL, " \n");
		addEdge(nGraph, u, v);
		fgets(lines, MAX_LEN, in);
	}
	printGraph(out, nGraph);
	fgets(lines, MAX_LEN, in);
	while(strcmp(lines, fill) != true)
	{
		temp = strtok(lines, " \n");
		u = atoi(temp);
		temp = strtok(NULL, " \n");
		v = atoi(temp);
		temp = strtok(NULL, " \n");
		BFS(nGraph, u);
		getPath(gList, nGraph, v);
		fprintf(out, "\n");
		if(front(gList) == INF || front(gList) == NIL)
		{
			fprintf(out,"The distance from %d to %d is infinity\n",u,v);
			fprintf(out,"No %d-%d path exists\n",u,v);
		}
		else
		{
			fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(nGraph,v));
			fprintf(out, "A shortest %d-%d path is: ",u,v);
			printList(out, gList);
			fprintf(out, "\n");
		}
		clear(gList);
		fgets(lines, MAX_LEN, in);
	}
	freeList(&gList);
	freeGraph(&nGraph);
	fclose(in);
	fclose(out);
	return(0);
}