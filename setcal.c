#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELEM_MAX_LENGTH 30
#define FILE_MAX_LINES 1000

//set
typedef struct{
	int *elements;
	int lineNum;		
} set_t;

//relation
typedef struct{
	int **elements;
	int lineNum;
} rel_t;

//load data from univerzum and save univerzum, sets and relations to data types
//loadData(FILE* file, char **univerzum, set_t[] setArray, rel_t[] relArray)

//return element from univerzum with particular index
//returnUniverzumElement(char **univerzum, int uniSize, int index)

//free all allocated memory for univerzum
//univerzumDestructor(char ** univerzum, int uniSize)

//free all allocated memory from set array and relation array
//setReldestructor(set_t[] setArray, rel_t[] relArray)

int main() {	
	
	char **univerzum;
	univerzum = malloc(2 * sizeof(char*));
	char *pointerToUniElement = "bruh";
	*univerzum = pointerToUniElement;
	
	set_t setArray[FILE_MAX_LINES];
	rel_t relArray[FILE_MAX_LINES];

	//sample sets for setArray
	int elem1[] = {0, 0, 1, 1, 0, 0};
	int *p_elem1;
	p_elem1 = elem1;
	set_t set1 = {.lineNum = 2, .elements = p_elem1};	
	int elem2[] = {0, 1, 1, 1, 1, 0};
	int *p_elem2;
	p_elem2 = elem2;
	set_t set2 = {.lineNum = 3, .elements = p_elem2};

	setArray[0] = set1;

	free(univerzum);

	return 0;
} 
