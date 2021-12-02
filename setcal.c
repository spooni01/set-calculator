#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELEM_MAX_LENGTH 30
#define FILE_MAX_LINES 1000

//set data type
typedef struct{
	int *elements;
	int lineNum;		
} set_t;

//relation data type
typedef struct{
	int **elements;
	int lineNum;
} rel_t;

/** LOADING, FREEING AND HELPER FUNCTIONS **/

//returns a string containing all the univerzum elements loaded from file
char *loadLine(FILE *file, char *firstChar, int *numOfElems, int *numOfLines)
{
	char allowedFirstChars[] = {'U', 'S', 'R', 'C'};

	(*numOfLines)++;
	char lineIdentifier = getc(file);
	if(!strchr(allowedFirstChars, lineIdentifier) || getc(file) != ' ')
	{	
		fprintf(stderr,"Chyba: Spatny format na radku %d!\n", *numOfLines);
		return NULL;
	}

	*firstChar = lineIdentifier;

	char ch = EOF;
	char *line = NULL;
	char *temp = NULL;
	size_t size = 0;
	size_t index = 0;

	while(ch)
	{
		ch = getc(file);
		if(ch == ' ' || ch == '\n')
			(*numOfElems)++;
		if(ch == '\n' || ch == '\0' || ch == EOF)
			ch = 0;

		if(size <= index)
		{
			size += sizeof(char);
			temp = realloc(line, size);
			if(!temp)
			{
				fprintf(stderr,"Chyba: Alokace pamati pro radek %d selhala!\n", *numOfLines);
				(*numOfLines)--;
				free(line);
				line = NULL;
				return line;
			}
			line = temp;
		}
		line[index++] = ch;
	}
	return line;
}

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
			fprintf(stderr, "Chyba: Chybny format univerza u prvku %s!\n", element);
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

void print_set(set_t set, int length, char **univerzum) {
	int count = 0; // number of printed elements
	printf("{");
	for (int i = 0; i < length; i++)
	{
	        if(set.elements[i] == 1) {
			if(count==0)
	                	printf("%s", univerzum[i]);
	                else
	                	printf(", %s", univerzum[i]); 
			count++;         
		}
	          
	}
 	printf("}\n");
}

/** FUNCTIONS FOR SETS OPERATIONS **/

void set_empty(set_t set, int length) {
	for(int i = 0; i < length; i++)
	{
		if(set.elements[i] == 1) {
			printf("false\n");
			return;
		}
	}
	printf("true\n");
}

void set_card(set_t set, int length) {
	int count = 0;
	for(int i = 0; i < length; i++) {
		if(set.elements[i] == 1)
			count++;
	}
	printf("%d\n", count);
}

void set_complement(set_t set, int length, char **univerzum) {
	for(int i = 0; i < length; i++) {
		if(set.elements[i] == 1)
			set.elements[i] = 0;
		else
			set.elements[i] = 1;    
	}
	print_set(set, length, univerzum);

}

void set_union(set_t set1, set_t set2, int length, char **univerzum) {
	int elem[length];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	

	for(int i = -1; i < length; i++) {
		if(set1.elements[i] == 1 || set2.elements[i] == 1)
			final_set.elements[i] = 1;
		else
			final_set.elements[i] = 0;        
	}
			        
	print_set(final_set, length, univerzum);
}

void set_intersect(set_t set1, set_t set2, int length, char **univerzum) {
	int elem[length];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	

	for(int i = -1; i < length; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 1)
			final_set.elements[i] = 1;
		else
			final_set.elements[i] = 0;       
	}
	print_set(final_set, length, univerzum);
}

void set_minus(set_t set1, set_t set2, int length, char **univerzum) {
	int elem[length];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	

	for(int i = -1; i < length; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 1)
			final_set.elements[i] = 0;
		else if(set1.elements[i] == 0)
			final_set.elements[i] = 0;    
		else
			final_set.elements[i] = 1;
	}
			    
	print_set(final_set, length, univerzum); 
}

void set_subseteq(set_t set1, set_t set2, int length) {
	for(int i = 0; i < length; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 0) {
			printf("false\n");
			return;
		}
	}
	printf("true\n");
}

void set_subset(set_t set1, set_t set2, int length) {
	int same_elems = 0;

	for(int i = 0; i < length; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 0) {
			printf("false\n");
			return;
		}
		else if(set1.elements[i] == set2.elements[i])
			same_elems++;
	}
	
	if(same_elems == length) 
		printf("false\n");
	else
		printf("true\n");
}

void set_equals(set_t set1, set_t set2, int length) {
	for(int i = 0; i < length; i++) {
		if(set1.elements[i] != set2.elements[i]) {
			printf("false\n");
			return;
		}
	}
	printf("true\n");
}

/** FUNCTIONS FOR RELATIONS OPERATIONS**/
//TO DO: ALL

/** MAIN **/

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
	char uniIdentifier;
	int numOfUniElems = 0;
	int numOfLines = 0;
	char *univerzumLine = loadLine(file, &uniIdentifier, &numOfUniElems, &numOfLines);

	if(uniIdentifier != 'U')
	{
		fprintf(stderr, "Chyba: Spatny format univerza\n");
		fclose(file);
		return 1;
	}

	univerzum = malloc(numOfUniElems * sizeof(char*));
	loadUniElements(univerzumLine, univerzum);
	free(univerzumLine);

	printUniverzum(univerzum, numOfUniElems);

	//set_t setArray[FILE_MAX_LINES];
	//rel_t relArray[FILE_MAX_LINES];

	//TO DO: load all sets and relations into respective arrays

	//TO DO: load all instructions from test file and call the corresponding functions

	//TO DO: free all sets and arrays, since they will be dynamically allocated

	freeUni(univerzum, numOfUniElems);
	fclose(file);
	return 0;
} 
