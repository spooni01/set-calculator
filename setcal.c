#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// todo: dynamicka alokacia a zmena dlzok v celom programe
#define MAX_LENGTH 30
#define MAX_ROWS 1000

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

void print_set(char set[MAX_LENGTH][MAX_LENGTH], int length)
{
   /*
      Function will print universum in format:
      '{item1, item2, item3}'.
   */
   int count = 0; // Must be counting because if condition may not allow to continue.

   printf("{");
   for (int i = 1; i < length; i++) 
   {
      if(set[i][0] != '\0')
      {
         count++;
         if(count == 1) 
            printf("%s", set[i]);
         else  
         {
            strtok(set[i], "\n");
            printf(", %s", set[i]);
         }
      }
   }
   printf("}\n");
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

   return true;
}

void separate_universum(char line[MAX_LENGTH], char universum[MAX_LENGTH][MAX_LENGTH], int *number_of_universums)
{
   /*
      Function will separate 'line' to words and store it in '*universum'.
   */
   int word = 0;     // Count number of words to know where to save it.
   int letter = 0;   // Count letters in word.

   for(int i = 0; i <= arr_length(line); i++)
   {
      if(line[i]==' '||line[i]=='\0')
      {
         universum[word][letter]='\0';
         word++;     // Next word.
         letter = 0; // Reset 'letter' to 0 because new word will start with 'letter = 0'.
      }
      else
      {
         universum[word][letter] = line[i];
         letter++; 
      } 
   }

   *number_of_universums = word - 1; // Minus 1 because first letter "U" is also counted.
}

void sort_file(char *filename, char lines_from_file[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH], char universum[MAX_LENGTH][MAX_LENGTH], int *number_of_universums)
{  
   /*
      Function open file 'filename' and save each line to '*set'.
   */
   FILE *file;
   file = fopen(filename, "r");
   char line[MAX_LENGTH];  // Temporary storage of a row from a file.
   
   // Go through file line by line and save lines to '*set' and then in for() cycle go through 
   // line letter by letter and save letters to 'set[row].item[i]'.
   for(int row = 0; fgets(line, MAX_LENGTH, file) != NULL; row++)
   {
      int word = 0;     // Count number of words to know where to save it.
      int letter = 0;   // Count letters in word.

      for(int i = 0; i <= arr_length(line); i++)
      {
         if(i == 0 && line[i] == 'U')
            separate_universum(line, universum, number_of_universums);

         if(line[i]==' '||line[i]=='\0')
         {
            lines_from_file[row][word][letter]='\0';
            word++;     // Next word.
            letter = 0; // Reset 'letter' to 0 because new word will start with 'letter = 0'.
         }
         else
         {
            if(line[i] != '\n')
               lines_from_file[row][word][letter] = line[i];
            
            letter++; 
         } 
      }

      // Print actual line to terminal.      
      if(line[0] != 'C')
         printf("%s", line);
   }
}

bool arr_equal(char arr1[], char arr2[])
{
   // check if two arrays are equal
   bool same_arrays = true;
   if(arr_length(arr1) == arr_length(arr2))
   {
      for (int i=0; i < arr_length(arr1); i++)
      if(arr1[i] != arr2[i])
         same_arrays = false;
   }
   else
      same_arrays = false;

   return same_arrays;        
}

void operation_set_empty(char set[5], char lines_from_file[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH])
{
   /*
      Check if set is empty.
   */
   int item;    
   for (item = 0; lines_from_file[atoi(set)][item][0] != '\0'; item++) {}

   item = item - 1; // Minus one becauce for cycle count also first letter ('U').

   if(item == 0)
      printf("true\n");
   else   
      printf("false\n");        
}

void operation_set_card(char set[5], char lines_from_file[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH])
{
   /*
      Count number of items in set.
   */
   int item;    
   for (item = 0; lines_from_file[atoi(set)][item][0] != '\0'; item++) {}
   printf("%d\n", item - 1);      
}

void operation_set_complement(char set[5], char lines_from_file[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH], char universum[MAX_LENGTH][MAX_LENGTH], int number_of_universums)
{
   /*
      Find complement of set 'set'.
   */
   for (int i = 0; i <= number_of_universums; i++)
   {
      for (int j = 0; j < MAX_LENGTH;j++)
      {
         // Delete '\n' from a chars[]. With '\n' function can recognize, that 'x' and 'x\n' is the same item.
         strtok(lines_from_file[atoi(set)][i], "\n");
         strtok(universum[j], "\n");

         if(arr_equal(lines_from_file[atoi(set)][i], universum[j]))
            universum[j][0]='\0';
      }      
   }
   
   print_set(universum, number_of_universums+1); 
}   

void operation_set_intersect(char set_a[5], char set_b[5], char lines_from_file[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH], int number_of_universums)
{
   /*
      Return intersect of two sets.
   */
   int count = 0;
   char final_set[MAX_LENGTH][MAX_LENGTH];
   for (int i = 0; i <= number_of_universums; i++)
   {
      for (int j = 0; j < number_of_universums; j++)
      {
         if(arr_equal(lines_from_file[atoi(set_a)][i], lines_from_file[atoi(set_b)][j]))
         {
            // Write to final_set.
            for (int k = 0; k < MAX_LENGTH; k++)
            {
               final_set[count][k] = lines_from_file[atoi(set_a)][i][k];
            }
            
            count++;
         }   
      }    
   }
   print_set(final_set, count);
}

void operations(char lines_from_file[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH], int row, char universum[MAX_LENGTH][MAX_LENGTH], int number_of_universums)
{
   /*
      Find what type of operator is on line 'row' and go to that function.
   */
   //todo: check arguments on line after C
   if(arr_equal(lines_from_file[row][1], "empty"))
      operation_set_empty(lines_from_file[row][2], lines_from_file);
   else if(arr_equal(lines_from_file[row][1], "card"))
      operation_set_card(lines_from_file[row][2], lines_from_file);
   else if(arr_equal(lines_from_file[row][1], "complement"))
      operation_set_complement(lines_from_file[row][2], lines_from_file, universum, number_of_universums);
   else if(arr_equal(lines_from_file[row][1], "union"))
      return; //todo
   else if(arr_equal(lines_from_file[row][1], "intersect"))
      operation_set_intersect(lines_from_file[row][2], lines_from_file[row][3], lines_from_file, number_of_universums);
   else if(arr_equal(lines_from_file[row][1], "minus"))
      return; //todo
   else if(arr_equal(lines_from_file[row][1], "subseteq"))
      return; //todo 
   else if(arr_equal(lines_from_file[row][1], "subset"))
      return; //todo 
   else if(arr_equal(lines_from_file[row][1], "equals"))
      return; //todo   
}

int main(int argc, char *argv[]) 
{
   char lines_from_file[MAX_ROWS][MAX_LENGTH][MAX_LENGTH];  // Store all lines from file.
   char universum[MAX_LENGTH][MAX_LENGTH];                  // There will be store universums from file. On the [0] will be , so the first universum is on [1].
   int number_of_universums;                                // Number of universums on a line where is "U" on first place.
   bool error = false;                                      // Variable that is true if in program is error.   
   
   // This condition check if arguments from user are correct (check_arguments())
   // and whether an error occurs while loading the file '*file'.
   if(check_arguments(argc, &error))
   {
      sort_file(argv[1], lines_from_file, universum, &number_of_universums);
      // Now in lines_from_file are all lines from file, in universum are universums 
      // Find all operations by "C" on begin and for each row do operation.
      for (int row = 0; row < MAX_ROWS; row++)
      {
         if(lines_from_file[row][0][0]=='C')
            operations(lines_from_file, row, universum, number_of_universums);
      }
   }

   // If there is an error in the program, exit the program with a return code 1
   if(error)
      return 1;
   else
      return 0;
}