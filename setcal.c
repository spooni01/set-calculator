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
			fprintf(stderr, "Chyba: Prvek %s... je prilis dlouhy, maximilni delka prvku je %d znaku!\n", element, ELEM_MAX_LENGTH);
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

//returns a string containing all the univerzum elements loaded from file
char *loadUniverzum(FILE *file, int *numOfUniElems)
{
	if(getc(file) != 'U' || getc(file) != ' ')
		fprintf(stderr,"Chyba: Spatny format univerza!\n");

	char ch = EOF;
	char *line = NULL;
	char *temp = NULL;
	size_t size = 0;
	size_t index = 0;

	while(ch)
	{
		ch = getc(file);
		if(ch == ' ' || ch == '\n')
			(*numOfUniElems)++;
		if(ch == '\n' || ch == '\0' || ch == EOF)
			ch = 0;

		if(size <= index)
		{
			size += sizeof(char);
			temp = realloc(line, size);
			if(!temp)
			{
				free(line);
				line = NULL;
				break;
			}
			line = temp;
		}
		line[index++] = ch;
	}
	
	return line;
}

int main(int argc, char *argv[]) {	
	
	if(argc == 1)
	{
		fprintf(stderr, "Chyba: Nebyl dodan soubor s daty!\n");
		return 1;
	}
	
	FILE *file = fopen(argv[1], "r");
	if(!file)
	{
		fprintf(stderr, "Chyba: Nelze otevrit soubor s daty!\n");
		fclose(file);
		return 1;
	}

	char **univerzum;
	int numOfUniElems = 0;
	char *univerzumLine = loadUniverzum(file, &numOfUniElems);
	univerzum = malloc(numOfUniElems * sizeof(char*));
	loadUniElements(univerzumLine, univerzum);

	//all elements of univerzum are loaded

	printUniverzum(univerzum, numOfUniElems);

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

	freeUni(univerzum, numOfUniElems);
	fclose(file);
	return 0;
} 
