/*
Jeremy Lafond
jalafond
pa5
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage error: <infile> <outfile>\n");
        exit(1);
    }
    int size = 0;
    int count1 = 0;
    int count2 = 1;
    int vertex1;
    int vertex2;
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    List stuff = newList();
    if(out == NULL)
    {
        fprintf(stderr, "Write error: cannot open %s to write into. \n", argv[2]);
        exit(1);
    }
    if(in == NULL)
    {
        fprintf(stderr, "Read error: cannot open %s to read out of. \n", argv[1]);
        exit(1);
    }
    fscanf(in, "%d", &size);
    Graph comp = newGraph(size);
    while(fgetc(in) != EOF)
    {
        fscanf(in, "%d", &vertex1);
        fscanf(in, "%d", &vertex2);
        if(vertex1 == 0 && vertex2 == 0)
        {
            break;
        }
        addArc(comp, vertex1, vertex2);
    }
    for(int i = 1; i <= size; i++)
    {
        append(stuff, i);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, comp);
    fprintf(out, "\n");
    DFS(comp, stuff);
    Graph tGraph = transpose(comp);
    DFS(tGraph, stuff);
    for(int i = 1; i <= getOrder(tGraph); i++)
    {
        if(getParent(tGraph, i) == NIL)
        {
            count1++;
        }
    }
    fprintf(out, "G contains %d strongly connected components:\n", count1);
    List *strongStuff = calloc(count1 + 1, sizeof(List));
    for(int i = 1; i <= count1; i++)
    {
        strongStuff[i] = newList();
    }
    int stuffLength = length(stuff);
    int end = front(stuff);
    for(int j = 1; j <= stuffLength - 1; j++)
    {
        int v = back(stuff);
        deleteBack(stuff);
        prepend(strongStuff[count2], v);
        if (getParent(tGraph, v) == NIL)
        {
            count2++;
        }
    }
    prepend(strongStuff[count2], end);
    for(count2 = 1; count2 <= count1; count2++)
    {
        fprintf(out, "Component %d: ", count2);
        printList(out, strongStuff[count2]); fprintf(out, "\n");
    }
    freeGraph(&comp);
    freeGraph(&tGraph);
    for(count2 = 0; count2 <= count1; count2++)
    {
        freeList(&strongStuff[count2]);
    }
    freeList(&stuff);
    free(strongStuff);
    fclose(in);
    fclose(out);
    return(0);
}