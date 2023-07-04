/*
Jeremy Lafond
balafond
pa
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
  FILE *in, *in2, *out;
  char line[MAX_LEN];
  // check number of args
  if(argc != 3)
  {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  // open files for reading and writing 
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
  //read each line of input file, then count and print tokens 
  while(fgets(line, MAX_LEN, in) != NULL)  
  {
    count++;
  }
  fclose(in);
  in2  = fopen(argv[1], "r");
  char *lines[count];
  while(fgets(line, MAX_LEN, in2) != NULL)  
  {
    lines[n] = malloc(sizeof(line)+1);
    strcpy(lines[n],line);
    n++;
  }  
  //sorting
  List L = newList();
 // append(L,0);
  for(int i=0;i<count;++i)
  {
    moveBack(L);
    char *temp = lines[i];
    int j;//index of insertion
    for(j=i-1; (j >= 0 && strcmp(temp, lines[get(L)]) < 0);j--)
    {
      movePrev(L);
    }
    //the index is defined so insert after
    if( index(L) != -1)
      {
        insertAfter(L,i);
      }
    else 
    {
      prepend(L,i);
    }
  }
  if(length(L) > 0)
  {
    for(moveFront(L);get(L) != back(L);moveNext(L))
    {
      fprintf(out,"%s", lines[get(L)]);
    }
    fprintf(out,"%s",lines[back(L)]);
  }
  freeList(&L);
  free(*lines); //wow im dumb. this was required to fix my errors . . .
  fclose(in2);
  fclose(out);
  //need to free array 1 by 1
  for(int a = 1; a <= count-1; a++) //tricky tricky... had to think about the starting at 1 ending at +1
  {
      free(lines[a]);
  }
  return(0);
}