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

//returns a a string with the lines elements (checks for validity the first two chars and then discards them)
//also 'returns' what was the first char (identification), number of elements it found and on success, increases numOfLines by one
char *loadLine(FILE *file, char *firstChar, int *numOfElems, int *numOfLines)
{
	char allowedFirstChars[] = {'U', 'S', 'R', 'C'};

	(*numOfLines)++;
	char lineIdentifier = getc(file);
	if(lineIdentifier == EOF)
		return NULL;
	if(lineIdentifier == '\n')
	{
		fprintf(stderr, "Chyba: na vstupu je prazdny radek (%d)!\n", *numOfLines);
		return NULL;
	}
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


//gets set as a str with all the elements which are then split and an array of 1s and 0s is saved into setArr
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

//gets relation as a str with all the elements which are then split and a 2D array of 1s and 0s is saved into relArr
int loadRel(char *relStr, int **relArr, int lineNum, int maxElems, char **univerzum)
{
	char buffer1[ELEM_MAX_LENGTH + 1];
	char buffer2[ELEM_MAX_LENGTH + 1];
	int arrX;
	int arrY;
	int relStrIndex = 0;


	memset(buffer1, '\0', ELEM_MAX_LENGTH + 1);
	memset(buffer2, '\0', ELEM_MAX_LENGTH + 1);

	while(relStr[relStrIndex] != '\0')
	{
		memset(buffer1, '\0', ELEM_MAX_LENGTH + 1);
		memset(buffer2, '\0', ELEM_MAX_LENGTH + 1);

		if(relStr[relStrIndex] != '(')
		{
			fprintf(stderr, "Chyba: spatny format relace na radku %d!\n", lineNum);
			return 1;
		}
		relStrIndex++;

		for(int i = 0; i < ELEM_MAX_LENGTH && relStr[relStrIndex] != ' '; i++ )
		{
			buffer1[i] = relStr[relStrIndex];
			relStrIndex++;
		}

		if(relStr[relStrIndex] != ' ')
		{
			fprintf(stderr, "Chyba: prvek relace %s.. na radku %d je prilis dlouhy!\n", buffer1, lineNum);
			return 1;
		}
		relStrIndex++;

		for(int i = 0; i < ELEM_MAX_LENGTH && relStr[relStrIndex] != ')'; i++ )
		{
			buffer2[i] = relStr[relStrIndex];
			relStrIndex++;
		}

		if(relStr[relStrIndex] != ')'  || (relStr[++relStrIndex] != ' ' && relStr[relStrIndex] != '\0'))
		{
			fprintf(stderr, "Chyba: spatny format relace na radku %d!\n", lineNum);
			return 1;
		}
		if(relStr[relStrIndex] != '\0')
			relStrIndex++;
		
		arrY = getPosInUni(buffer1, univerzum, maxElems);
		arrX = getPosInUni(buffer2, univerzum, maxElems);
		if(arrY == -1)
		{
			fprintf(stderr, "Chyba: prvek %s v relaci na radku %d nebyl nalezen v univerzu!\n", buffer1, lineNum);
			return 1;
		}
		if(arrX == -1)
		{
			fprintf(stderr, "Chyba: prvek %s v relaci na radku %d nebyl nalezen v univerzu!\n", buffer2, lineNum);
			return 1;
		}
		
		relArr[arrY][arrX] = 1;
	}
	return 0;
}

//gets univerzum as a long string {element1 element2 element3 ... elementn} and saves these elements into the neatly packed univerzum
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

//frees all dynamically allocated sets in sets array
void freeSets(set_t *setArray, int numOfSets)
{
	for(int i = 0; i < numOfSets; i++)
	{
		free(setArray[i].elements);
		setArray[i].lineNum = 0;
	}
}

//frees all dynamically allocated relations in relArray
void freeRels(rel_t *relArray, int numOfRels, int relSize)
{
	for(int i = 0; i < numOfRels; ++i)
	{
		for(int j = 0; j < relSize; ++j)
		{
			free(relArray[i].elements[j]);
		}
		free(relArray[i].elements);
		relArray[i].lineNum = 0;
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


void printSet(set_t set, int length, char **univerzum) {
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

void printRel(rel_t rel, int numOfUniElems, char **univerzum) {
	for (int i = 0; i < numOfUniElems; i++)
	{
		for (int j = 0; j < numOfUniElems; j++)
		{
			if(rel.elements[i][j] == 1) {
				printf("(%s %s) ", univerzum[i], univerzum[j]);
			}
		}
	}
	printf("\n");
}

/** FUNCTIONS FOR SETS OPERATIONS **/

void setEmpty(set_t set, int numOfUniElems) {
	for(int i = 0; i < numOfUniElems; i++)
	{
		if(set.elements[i] == 1) {
			printf("false\n");
			return;
		}
	}
	printf("true\n");
}

void setCard(set_t set, int numOfUniElems) {
	int count = 0;
	for(int i = 0; i < numOfUniElems; i++) {
		if(set.elements[i] == 1)
			count++;
	}
	printf("%d\n", count);
}

void setComplement(set_t set, int numOfUniElems, char **univerzum) {
	for(int i = 0; i < numOfUniElems; i++) {
			if(set.elements[i] == 1)
				set.elements[i] = 0;
			else
				set.elements[i] = 1;    
	}
	printSet(set, numOfUniElems, univerzum);
}

void setUnion(set_t set1, set_t set2, int numOfUniElems, char **univerzum) {
	int elem[numOfUniElems];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	

	for(int i = -1; i < numOfUniElems; i++) {
		if(set1.elements[i] == 1 || set2.elements[i] == 1)
			final_set.elements[i] = 1;
		else
			final_set.elements[i] = 0;        
	}
						        
	printSet(final_set, numOfUniElems, univerzum);
}

void setIntersect(set_t set1, set_t set2, int numOfUniElems, char **univerzum) {
	int elem[numOfUniElems];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	
	
	for(int i = -1; i < numOfUniElems; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 1)
			final_set.elements[i] = 1;
		else
			final_set.elements[i] = 0;       
	}
	printSet(final_set, numOfUniElems, univerzum);
}

void setMinus(set_t set1, set_t set2, int numOfUniElems, char **univerzum) {
	int elem[numOfUniElems];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	

	for(int i = -1; i < numOfUniElems; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 1)
			final_set.elements[i] = 0;
		else if(set1.elements[i] == 0)
			final_set.elements[i] = 0;    
		else
			final_set.elements[i] = 1;
	}
								    
	printSet(final_set, numOfUniElems, univerzum); 
}

void setSubseteq(set_t set1, set_t set2, int numOfUniElems) {
	for(int i = 0; i < numOfUniElems; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 0) {
			printf("false\n");
			return;
		}
	}
	printf("true\n");
}

void setSubset(set_t set1, set_t set2, int numOfUniElems) {
	int same_elems = 0;

	for(int i = 0; i < numOfUniElems; i++) {
		if(set1.elements[i] == 1 && set2.elements[i] == 0) {
			printf("false\n");
			return;
		}
		else if(set1.elements[i] == set2.elements[i])
			same_elems++;
	}
		
	if(same_elems == numOfUniElems) 
		printf("false\n");
	else
		printf("true\n");
}

void setEquals(set_t set1, set_t set2, int numOfUniElems) {
	for(int i = 0; i < numOfUniElems; i++) {
		if(set1.elements[i] != set2.elements[i]) {
			printf("false\n");
			return;
		}
	}
	printf("true\n");
}

/** FUNCTIONS FOR RELATIONS OPERATIONS**/

void relReflexive(rel_t rel, int numOfUniElems) {
	for(int i = 0; i < numOfUniElems; i++)
	{
		if(rel.elements[i][i] == 0) {
			printf("false\n");
			return;
		}
	}
	printf("true\n");
}

void relSymmetric(rel_t rel, int numOfUniElems) {
	for(int i = 0; i < numOfUniElems; i++)
	{
		for (int j = 0; j < numOfUniElems; j++)
		{
			if(rel.elements[i][j] != rel.elements[j][i]) {
				printf("false\n");
				return;
			}
		}		
	}
	printf("true\n");
}

void relAntisymmetric(rel_t rel, int numOfUniElems) {
	for(int i = 0; i < numOfUniElems; i++)
	{
		for (int j = 0; j < numOfUniElems; j++)
		{
			if(rel.elements[i][j] && rel.elements[j][i] && i != j) {
				printf("false\n");
				return;
			}
		}		
	}
	printf("true\n");	
}

void relTransitive(rel_t rel, int numOfUniElems) {
	for(int i = 0; i < numOfUniElems; i++)
	{
		for (int j = 0; j < numOfUniElems; j++)
		{
			for (int k = 0; k < numOfUniElems; k++)
			{
				if(rel.elements[i][j] == 1 && rel.elements[j][k] == 1 && rel.elements[i][k] == 0) {
					printf("false\n");
					return;
				}
			}
		}		
	}

	printf("true\n");
}

//returns 1 (= is a function) or a 0 (= isnt a function)
//depending on shouldPrint value (1 = yes, 0 = no) prints answer
int relFunction(rel_t rel, int numOfUniElems, int shouldPrint) {
	for(int i = 0; i < numOfUniElems; i++)
	{
		int count = 0; //number of y on one line ... (x,y)
		for (int j = 0; j < numOfUniElems; j++)
		{
			if(rel.elements[i][j] == 1)
				count++;
		}	

		if(count > 1) {
			if(shouldPrint)
				printf("false\n");
			return 0;
		}	
	}
	if(shouldPrint)
		printf("true\n");
	return 1;
}

void relDomain(rel_t rel, int numOfUniElems, char **univerzum) {
	int elem[numOfUniElems];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	

	for(int i = 0; i < numOfUniElems; i++)
	{
		for (int j = 0; j < numOfUniElems; j++)
		{
			if(rel.elements[i][j] == 1 || final_set.elements[i] == 1)
				final_set.elements[i] = 1;
			else
				final_set.elements[i] = 0;	
		}	

	}

	printSet(final_set, numOfUniElems, univerzum);
}

void relCodomain(rel_t rel, int numOfUniElems, char **univerzum) {
	int elem[numOfUniElems];
	int *p_elem;
	p_elem = elem;
	set_t final_set = {.elements = p_elem};	

	for(int i = 0; i < numOfUniElems; i++)
	{
		for (int j = 0; j < numOfUniElems; j++)
		{
			if(rel.elements[i][j] == 1 || final_set.elements[j] == 1)
				final_set.elements[j] = 1;
			else
				final_set.elements[j] = 0;	
		}	

	}

	printSet(final_set, numOfUniElems, univerzum);
}

int relInjective(rel_t rel, int numOfUniElems, int shouldPrint) {
	if(!relFunction(rel, numOfUniElems, 0))
	{
		if(shouldPrint)
			printf("false\n");
		return 0;
	}

	int count;
	for(int j = 0; j < numOfUniElems; j++)
	{
		count = 0;
		for(int i = 0; i < numOfUniElems; i++)
		{
			if(rel.elements[i][j])
				count++;
		}

		if(count > 1)
		{
			if(shouldPrint)
				printf("false\n");
			return 0;
		}
	}

	if(shouldPrint)
		printf("true\n");
	return 1;
}

int relSurjective(rel_t rel, int numOfUniElems, int shouldPrint) {	
	if(!relFunction(rel, numOfUniElems, 0))
	{
		if(shouldPrint)
			printf("false\n");
		return 0;
	}
	
	int count;
	for(int j = 0; j < numOfUniElems; j++)
	{
		count = 0; 
		for (int i = 0; i < numOfUniElems; i++)
		{
			if(rel.elements[i][j])
				count++;
		}	

		if(!count) {
			if(shouldPrint)
				printf("false\n");
			return 0;
		}	
	}

	if(shouldPrint)
		printf("true\n");
	return 1;
}

void relBijective(rel_t rel, int numOfUniElems) {
	if(!relFunction(rel, numOfUniElems, 0) || !relInjective(rel, numOfUniElems, 0) || !relSurjective(rel, numOfUniElems, 0))
		printf("false\n");
	else
		printf("true\n");

}

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

	set_t setArray[FILE_MAX_LINES];
	rel_t relArray[FILE_MAX_LINES];
	int setArrIndex = 0;
	int relArrIndex = 0;

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

			int **rel;
			rel = calloc(numOfUniElems, sizeof(int*));
			for (int i = 0; i < numOfUniElems; ++i)
			{
				rel[i] = calloc(numOfUniElems, sizeof(int));
			}

			functionFail = loadRel(lineBuffer, rel, numOfLines,  numOfUniElems, univerzum);
			if(functionFail)
			{	
				fclose(file);
				freeUni(univerzum, numOfUniElems);
				freeRels(relArray, relArrIndex, numOfUniElems);
				return 1;
			}

			relArray[relArrIndex].elements = rel;
			rel = NULL;
			relArray[relArrIndex].lineNum = numOfLines;
			relArrIndex++;
		}

		free(lineBuffer);
		lineBuffer = loadLine(file, &firstCharOnLine, &numOfElementsInArray, &numOfLines);
	}
	if(lineBuffer == NULL)
	{
		freeUni(univerzum, numOfUniElems);
		freeSets(setArray, setArrIndex);
		freeRels(relArray, relArrIndex, numOfUniElems);
		fclose(file);
		return 1;
	}

	//TO DO: load all instructions from test file and call the corresponding functions

	freeUni(univerzum, numOfUniElems);
	freeSets(setArray, setArrIndex);
	freeRels(relArray, relArrIndex, numOfUniElems);
	fclose(file);
	return 0;
} 
