#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_ROWS 1000

typedef struct set
{
   char item[MAX_LENGTH];
} set_t;

//todo struct relation

void print_set(set_t set[MAX_ROWS])
{
   int count = 0;

   printf("{");
   for(int i = 0; i < MAX_ROWS; i++)
   {
      //check if item is empty
      if(strlen(set[i].item) != 0)
      {
         //do not add ',' before first item
         count++;
         if(count == 1)
            printf("%s", set[i].item);
         else
            printf(", %s", set[i].item);

      }
   }
   printf("}");
}

int main() 
{
   set_t set[MAX_ROWS] = {{"Auto"}, {"pes"}, {"strom"}, {"les"}, {}, {}, {"DF"}};
   print_set(set);

   return 0;
}