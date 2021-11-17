#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// todo check numbers
#define MAX_LENGTH 30
#define MAX_ROWS 1000

typedef struct set
{
   char item[MAX_LENGTH];
} set_t;

//todo struct relation

int arr_length(char *str)
{
   /*
      Return length of array.
   */
   int length;
   for (length=0; str[length] != 0; length++) {}
   return length;
}

void print_set(set_t set[MAX_ROWS])
{
   /*
      Function will print set in format:
      '{item1, item2, item3}'.
   */
   // Counts the number of items so that the function knows when it is the 
   // first item (-> function do not print the comma before the first item)
   int count = 0;

   printf("{");
   for(int i = 0; i < MAX_ROWS; i++)
   {
      // Check if item is empty. If item is empty, skip it.
      if(strlen(set[i].item) != 0)
      {
         count++;
         if(count == 1)
            printf("%s", set[i].item);
         else
            printf(", %s", set[i].item);
      }
   }
   printf("}");
}

bool check_arguments(int argc, bool *error)
{
   /* 
      The function checks the arguments. 
      If there is an error in code, function prints standart error in terminal
      and set '*error' to true (-> this will end the program in function main()).
      When the return value of this boolean function is true, it means that
      the arguments are correct.
   */

   //check number of arguments   
   if(argc != 2)
   {
      fprintf(stderr, "Wrong number of arguments");
      *error = true;
      return false;
   }

   return true;
}

bool read_file(char *filename, set_t *set)
{  
   /*
      Function open file 'filename' and save each line to '*set'.
   */
   //todo: error (problem with loading file,etc...)
   FILE *file;
   file = fopen(filename, "r");
   
   int row = 0;            // 'row' counts the number of rows and saves the row from the file to '*set'
   char line[MAX_LENGTH];  // temporary storage of a row from a file
   
   // todo: change while to for?
   // go through file line by line and save lines to '*set'
   // and then in for() cycle go through line letter by letter
   // and save letters to 'set[row].item[i]'
   while((fgets(line, MAX_LENGTH, file)) != NULL)
   {
      for(int i=0; i < arr_length(line); i++)
         set[row].item[i] = line[i];
      
      row++;
   }

   return true;
}

int main(int argc, char *argv[]) 
{
   bool error = false; //variable that is true if in program is error
   set_t set[MAX_ROWS]; // todo change set_t to array

   // This condition check if arguments from user are correct (check_arguments())
   // and whether an error occurs while loading the file '*file'.
   if(check_arguments(argc, &error) && read_file(argv[1], set))
   {
      // just example of printing first letter and first line, this two lines can be deleted:
      printf("First char: %c\n", set[0].item[0]);
      printf("First line: %s", set[0].item);
   }

   // if there is an error in the program, exit the program with a return code 1
   if(error)
      return 1;
   else
      return 0;
}