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

//gets univerzum as a long string {element1 element2 element3 ... elementn} and loads these elements into the neatly packed univerzum
int loadUniElements(char *uniElems, char **univerzum)
{	
	char *element;
	int uniElemsIndex = 0;
	int uniIndex = 0;

	while(uniElems[uniElemsIndex] != '\0')
	{
		element = (char*) calloc((ELEM_MAX_LENGTH + 1), sizeof(char));
		if(element == NULL)
		{	
			fprintf(stderr, "Chyba pri alokaci pameti\n");
			free(element);
			return 1; 
		}

		for(int elemIndex = 0; elemIndex < ELEM_MAX_LENGTH && uniElems[uniElemsIndex] != ' ' && uniElems[uniElemsIndex] != '\0'; elemIndex++)
		{
			element[elemIndex] = uniElems[uniElemsIndex];
			uniElemsIndex++;
		}

		if(uniElems[uniElemsIndex] != ' ' && uniElems[uniElemsIndex] != '\0')
		{
			fprintf(stderr, "Prvek %s... je prilis dlouhy, maximilni delka prvku je %d znaku!\n", element, ELEM_MAX_LENGTH);
			free(element);
			return 1;
		}

		univerzum[uniIndex] = element;
		uniIndex++;
		//if next char isnt end of string, skip the next space-char
		if(uniElems[uniElemsIndex] != '\0') 
			uniElemsIndex++;
	}
	return 0;
}

//frees all memory taken up by the elemts of the univerzum and the univerzum itself
void freeUni(char **univerzum, int numOfUniElems)
{
	for(int i = 0; i < numOfUniElems; i++)
	{
		free(univerzum[i]);
	}
	
	free(univerzum);
}

//prints elements of the univerzum
void printUniverzum(char **univerzum, int numOfUniElems)
{
	for(int i = 0; i < numOfUniElems; i++)
	{
		printf("%d. element: %s\n", i + 1, univerzum[i]);
	}
}

//returns the indexed position of str element in univerzum or -1 if the element wasnt found
int getPosInUni(char *element, char **univerzum, int numOfUniElems)
{
	for(int i = 0; i < numOfUniElems; i++)
	{
		if(strcmp(element, univerzum[i]) == 0)
			return i;
	}
	return -1;
}

int main() {	
	
	char **univerzum;
	univerzum = malloc(4 * sizeof(char*));

	char *str = "ahoj babo dedku pazure";

	//testing functions
	loadUniElements(str, univerzum);
	printUniverzum(univerzum, 4);
	printf("prvek: %s je v univerzu na %d. pozici\n", "pazure", getPosInUni("pazure", univerzum, 4) + 1);
	freeUni(univerzum, 4);	

	/*	
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
	*/
	return 0;
} 
