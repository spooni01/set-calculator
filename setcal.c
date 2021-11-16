#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 30
#define MAX_ROWS 1000

typedef struct set
{
   char item[MAX_LENGTH];
} set_t;

//todo struct relation

int arr_length(char *str)
{
   int length;
	for (length=0; str[length] != 0; length++) {}
	return length;
}

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

void check_arguments(int argc, bool *error)
{
   //check numbere of arguments   
   if(argc != 2)
   {
      fprintf(stderr, "Wrong number of arguments");
      *error = true;
   }

}

int main(int argc, char *argv[]) 
{
   bool error = false; //variable that is true if in program is error
   check_arguments(argc, &error);
   if(error)
      return 1;

   //load file and save each line to 'set'
   FILE *file;
   char line[MAX_LENGTH];
   file = fopen(argv[1], "r");

   set_t set[MAX_ROWS];
   int row = 0;
   
   while((fgets(line, MAX_LENGTH, file)) != NULL)
   {
      for(int i=0; i < arr_length(line); i++)
         set[row].item[i] = line[i];
      
      row++;
   }

   print_set(set);

   return 0;
}