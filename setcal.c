#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELEM_MAX_LENGTH 30
#define FILE_MAX_LINES 1000

<<<<<<< HEAD
//set
=======
//set data type
>>>>>>> 2fb62d3cfcbc1f9c4b569b02c9de62e9ae2281e1
typedef struct{
	int *elements;
	int lineNum;		
} set_t;

<<<<<<< HEAD
//relation
=======
//relation data type
>>>>>>> 2fb62d3cfcbc1f9c4b569b02c9de62e9ae2281e1
typedef struct{
	int **elements;
	int lineNum;
} rel_t;

<<<<<<< HEAD
//load data from univerzum and save univerzum, sets and relations to data types
//loadData(FILE* file, char **univerzum, set_t[] setArray, rel_t[] relArray)

//return element from univerzum with particular index
//returnUniverzumElement(char **univerzum, int uniSize, int index)

//free all allocated memory for univerzum
//univerzumDestructor(char ** univerzum, int uniSize)

//free all allocated memory from set array and relation array
//setReldestructor(set_t[] setArray, rel_t[] relArray)

//gets univerzum as a long string {element1 element2 element3 ... elementn} and loads these elements into the neatly packed univerzum
=======
/** LOADING, FREEING AND HELPER FUNCTIONS **/

//returns a a string with the lines elements (checks for validity the first two chars and then discards them)
//also 'returns' what was the first char (identification), number of elements it found and on success, increases numOfLines by one
char *loadLine(FILE *file, char *firstChar, int *numOfElems, int *numOfLines)
{
	char allowedFirstChars[] = {'U', 'S', 'R', 'C'};

	(*numOfLines)++;
	char lineIdentifier = getc(file);
	if(lineIdentifier == EOF)
		return NULL;
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

int loadSet(char *setStr, int *setArr, int maxElems, char **univerzum)
{
	char buffer[ELEM_MAX_LENGTH + 1];
	int setStrIndex = 0;
	int posInUni;
	int numOfElems = 0;

	memset(buffer, '\0', ELEM_MAX_LENGTH + 1);

	while(setStr[setStrIndex] != '\0')
	{
		memset(buffer, '\0', ELEM_MAX_LENGTH + 1);
		//isolate an element from input string and save it into buffer
		for(int i = 0; i < ELEM_MAX_LENGTH && setStr[setStrIndex] != ' ' && setStr[setStrIndex] != '\0'; i++)
		{
			buffer[i] = setStr[setStrIndex];
			setStrIndex++;
		}

		//check if element isnt too long	
		if(setStr[setStrIndex] != ' ' && setStr[setStrIndex] != '\0')
		{
			fprintf(stderr, "Chyba: chybny format mnoziny u prvku %s!\n", buffer);
			return 1;
		}

		//find this element in univerzum and save 1 on corresponding setArr position
		posInUni = getPosInUni(buffer, univerzum, maxElems);

		if(posInUni == -1)
		{
			fprintf(stderr, "Chyba: prvek %s neni v univerzu!\n", buffer);
			return 1;
		}

		numOfElems++;
		if(numOfElems > maxElems)
		{
			fprintf(stderr, "Chyba: prilis mnoho prvku v mnozine {%s}!\n", setStr);
			return 1;
		}

		setArr[posInUni] = 1;

		if(setStr[setStrIndex] != '\0')
			setStrIndex++;
	}
	return 0;
}

//gets univerzum as a long string {element1 element2 element3 ... elementn} and saves these elements into the neatly packed univerzum
>>>>>>> 2fb62d3cfcbc1f9c4b569b02c9de62e9ae2281e1
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
<<<<<<< HEAD
			fprintf(stderr, "Prvek %s... je prilis dlouhy, maximilni delka prvku je %d znaku!\n", element, ELEM_MAX_LENGTH);
=======
			fprintf(stderr, "Chyba: Chybny format univerza u prvku %s!\n", element);
>>>>>>> 2fb62d3cfcbc1f9c4b569b02c9de62e9ae2281e1
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

<<<<<<< HEAD
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

/*******************************************************************/

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
void set_empty(set_t set, int length) {
    for(int i = 0; i < length; i++) {
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
/*******************************************************************/

int main() {	
	
	char **univerzum;
	univerzum = malloc(4 * sizeof(char*));

	char *str = "ahoj babo dedku pazure";

	//testing functions
	loadUniElements(str, univerzum);
	printUniverzum(univerzum, 4);
	printf("prvek: %s je v univerzu na %d. pozici\n", "pazure", getPosInUni("pazure", univerzum, 4) + 1);

    /*****************/
    int length = 4;

    int elem1[] = {1, 0, 1, 0};
	int *p_elem1;
	p_elem1 = elem1;
	set_t set1 = {.lineNum = 2, .elements = p_elem1};

    int elem2[] = {0, 1, 1, 1};
	int *p_elem2;
	p_elem2 = elem2;
	set_t set2 = {.lineNum = 3, .elements = p_elem2};

    set_intersect(set1, set2, length, univerzum);

    /******************/
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
=======
//frees all dynamically allocated sets in sets array
void freeSets(set_t *setArray, int numOfSets)
{
	for(int i = 0; i < numOfSets; i++)
	{
		if(setArray[i].lineNum)
			free(setArray[i].elements);
		setArray[i].lineNum = 0;
	}
}

//prints elements of the univerzum
void printUniverzum(char **univerzum, int numOfUniElems)
{
	for(int i = 0; i < numOfUniElems; i++)
	{
		printf("%d. element: %s\n", i + 1, univerzum[i]);
	}
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

	//printUniverzum(univerzum, numOfUniElems);

	set_t setArray[FILE_MAX_LINES];
	//rel_t relArray[FILE_MAX_LINES];
	int setArrIndex = 0;
	//relArrIndex = 0;

	char firstCharOnLine;
	int numOfElementsInArray = 0;
	char *lineBuffer = loadLine(file, &firstCharOnLine, &numOfElementsInArray, &numOfLines);
	int functionFail;
	while((firstCharOnLine == 'S' || firstCharOnLine == 'R') && lineBuffer != NULL)
	{
		if(firstCharOnLine == 'S')
		{
			int *set = calloc(numOfUniElems, sizeof(int));
			functionFail = loadSet(lineBuffer, set, numOfUniElems, univerzum);
			if(functionFail)
			{	
				fclose(file);
				freeUni(univerzum, numOfUniElems);
				freeSets(setArray, setArrIndex);
				return 1;
			}

			setArray[setArrIndex].elements = set;
			set = NULL;
			setArray[setArrIndex].lineNum = numOfLines;
			setArrIndex++;		
		}

		else
		{
			//implement loading rels
		}

		free(lineBuffer);
		lineBuffer = loadLine(file, &firstCharOnLine, &numOfElementsInArray, &numOfLines);
	}

	for(int i = 0; i < setArrIndex; i++)
		print_set(setArray[i], numOfUniElems, univerzum);

	//TO DO: load all sets and relations into respective arrays

	//TO DO: load all instructions from test file and call the corresponding functions

	//TO DO: free all sets and arrays, since they will be dynamically allocated

	freeUni(univerzum, numOfUniElems);
	freeSets(setArray, setArrIndex);
	fclose(file);
	return 0;
} 
>>>>>>> 2fb62d3cfcbc1f9c4b569b02c9de62e9ae2281e1
