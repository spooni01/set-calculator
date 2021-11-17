#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// todo: dynamicka alokacia
#define MAX_LENGTH 30
#define MAX_ROWS 1000


// todo: universum a set ako array? alebo vsetko ako jeden struct?
typedef struct universum
{
   char item[MAX_LENGTH];
} universum_t;

typedef struct set
{
   char item[MAX_LENGTH];
} set_t;

typedef struct relation
{
   char item_a[MAX_LENGTH];
   char item_b[MAX_LENGTH];
} relation_t;


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
   // Counts the number of items so the function knows when it is the 
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
   
      You can add there any tests of arguments in function, but the condition must
      always contain '*error = true;' and 'return false;'. It should also 'printf(stderr, "...");'.
   */

   //check number of arguments   
   if(argc != 2)
   {
      fprintf(stderr, "Wrong number of arguments");
      *error = true;
      return false;
   }

   // todo: add tests for argv (also add *argv[] to arguments of this function)

   return true;
}

void separate_universum(char line[MAX_LENGTH], universum_t *universum)
{
   /*
      Function will separate 'line' to words and store it in '*universum'.
   */
   int word = 0;     // Count number of words to know where to save it.
   int letter = 0;   // Count letters in word.

   for(int i=0;i<=(arr_length(line));i++)
   {
      if(line[i]==' '||line[i]=='\0')
      {
         universum[word].item[letter]='\0';
         word++;     // Next word.
         letter = 0; // Reset 'letter' to 0 because new word will start with 'letter = 0'.
      }
      else
      {
         universum[word].item[letter] = line[i];
         letter++; 
      } 
   }
}

bool read_file(char *filename, set_t *set, universum_t *universum)
{  
   /*
      Function open file 'filename' and save each line to '*set'.
   */
   //todo: error (problem with loading file,etc...)
   FILE *file;
   file = fopen(filename, "r");
   int row = 0;            // 'row' counts the number of rows and saves the row from the file to '*set'.
   char line[MAX_LENGTH];  // Temporary storage of a row from a file.
   
   // Go through file line by line and save lines to '*set'
   // and then in for() cycle go through line letter by letter
   // and save letters to 'set[row].item[i]'.
   // todo: change while cycle to for?
   while((fgets(line, MAX_LENGTH, file)) != NULL)
   {
      for(int i=0; i < arr_length(line); i++)
      {
         // Check if line start with "U", so it is universum.
         if(i == 0 && line[i] == 'U')
            separate_universum(line, universum);

         // Save letters to 'set[row].item[i]' line by line.
         set[row].item[i] = line[i];
      }           
      row++;
   }
   return true;
}

int main(int argc, char *argv[]) 
{
   bool error = false;                 // Variable that is true if in program is error.
   universum_t universum[MAX_LENGTH];  // There will be store universums from file. On the [0] will be "U", so the first universum is on [1].
   set_t set[MAX_ROWS];                // todo change set_t to array

   // This condition check if arguments from user are correct (check_arguments())
   // and whether an error occurs while loading the file '*file'.
   if(check_arguments(argc, &error) && read_file(argv[1], set, universum))
   {
      
      //Just example of printing things, can be deleted:
      //printf("First char: %c\n", set[0].item[0]);
      //printf("First line: %s", set[0].item);
      printf("Prve univerzum: %s", universum[1].item);
   }

   // If there is an error in the program, exit the program with a return code 1
   if(error)
      return 1;
   else
      return 0;
}