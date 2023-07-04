/*
Jeremy Lafond
balafond
pa1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 256

int main(int argc, char * argv[]) 
{
	int n = 0;
	int count = 0;
	FILE *in, *out;
	char line[MAX_LEN];
	char* array[MAX_LEN];
	List list = NULL;
	// check number of args
	if(argc != 3)
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	// open files for read/write
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL)
	{
		printf("Unable to open file %s for reading\n", argv[1]);
   		exit(1);
   	}
	if(out == NULL)
	{
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	// read lines of file and keeps track of line count
	while(fgets(line, MAX_LEN, in) != NULL)
	{
		count++;
	}
	rewind(in);
	for(int a = 0; a <= count; a++) 
	{
		array[a] = calloc(1, sizeof(char* [MAX_LEN]));
	}
	while(fgets(line, MAX_LEN, in) != NULL) 
	{
		strcpy(array[n], line);
		n++;
	}
    list = newList();
    append(list, 0);
    for(int a = 1; a <= count; a++) 
    {
    	//If this string belongs at the back
    	if(strcmp(array[a], array[back(list)]) > 0) 
    	{
    		append(list, a);
    		continue;
    	}
		//If this string belongs in the front 
		else if (strcmp(array[a], array[front(list)]) < 0) 
    	{
			prepend(list, a);
			continue;
    	}
		moveFront(list);
		while(index(list) != -1) 
		{
			//if the value at array index a is less than the value at array index of cursor from list
			if(strcmp(array[a], array[get(list)]) < 0)
			{
				insertBefore(list, a);
				break;
			}
			else
			{
				moveNext(list);
			}
		}
	}
	for (moveFront(list); index(list) != -1; moveNext(list))
	{
		fprintf(out, "%s", array[get(list)]);
	}
	fclose(in);
	fclose(out);
	freeList(&list);
	for(int a = 0; a <= count; a++)
	{
    	free(array[a]);
	}
  return(0);
}