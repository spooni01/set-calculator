#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//set
typedef struct{
	int *elements;
	int lineNum;		
} set_t;

/*******************************************************************/

int set_length(set_t set) {
    int length;
    for (length = 0; set.elements[length] == 1 || set.elements[length] == 0;length++) {}
    return length;
}
void print_set(set_t set) {
    printf("{");
    for (int i = 0; i < set_length(set); i++)
    {
        if(i==0)
            printf("%d", set.elements[i]);
        else
            printf(", %d", set.elements[i]);    
    }
    printf("}\n");
}

/*****/

void set_empty(set_t set) {
    for(int i = 0; i < set_length(set); i++) {
        if(set.elements[i] == 1) {
            printf("false\n");
            return;
        }
    }
    printf("true\n");
}
void set_card(set_t set) {
    int count = 0;
    for(int i = 0; i < set_length(set); i++) {
        if(set.elements[i] == 1)
            count++;
    }
    printf("%d\n", count);
}
void set_complement(set_t set) {
    for(int i = 0; i < set_length(set); i++) {
        if(set.elements[i] == 1)
            set.elements[i] = 0;
        else
            set.elements[i] = 1;    
    }
    print_set(set);
}
void set_union(set_t set1, set_t set2) {
    int set_len = set_length(set1);

    int elem[set_len];
	int *p_elem;
    p_elem = elem;
	set_t final_set = {.elements = p_elem};	

    for(int i = -1; i < set_len; i++) {
        if(set1.elements[i] == 1 || set2.elements[i] == 1)
            final_set.elements[i] = 1;
        else
            final_set.elements[i] = 0;        
    }
    
    print_set(final_set);
}
void set_intersect(set_t set1, set_t set2) {
    int set_len = set_length(set1);

    int elem[set_len];
	int *p_elem;
    p_elem = elem;
	set_t final_set = {.elements = p_elem};	

    for(int i = -1; i < set_len; i++) {
        if(set1.elements[i] == 1 && set2.elements[i] == 1)
            final_set.elements[i] = 1;
        else
            final_set.elements[i] = 0;        
    }
    
    print_set(final_set);
}
void set_minus(set_t set1, set_t set2) {
    int set_len = set_length(set1);

    int elem[set_len];
	int *p_elem;
    p_elem = elem;
	set_t final_set = {.elements = p_elem};	

    for(int i = -1; i < set_len; i++) {
        if(set1.elements[i] == 1 && set2.elements[i] == 1)
            final_set.elements[i] = 0;
        else if(set1.elements[i] == 0)
            final_set.elements[i] = 0;    
        else
            final_set.elements[i] = 1;        
    }
    
    print_set(final_set); 
}
void set_subseteq(set_t set1, set_t set2) {
    for(int i = 0; i < set_length(set1); i++) {
        if(set1.elements[i] == 1 && set2.elements[i] == 0) {
            printf("false\n");
            return;
        }
    }
    printf("true\n");
}
void set_subset(set_t set1, set_t set2) {
    int set1_len = set_length(set1);
    int same_elems = 0;

    for(int i = 0; i < set1_len; i++) {
        if(set1.elements[i] == 1 && set2.elements[i] == 0) {
            printf("false\n");
            return;
        }
        else if(set1.elements[i] == set2.elements[i])
            same_elems++;
    }

    if(same_elems == set1_len) 
        printf("false\n");
    else
        printf("true\n");
}
void set_equals(set_t set1, set_t set2) {
    for(int i = 0; i < set_length(set1); i++) {
        if(set1.elements[i] != set2.elements[i]) {
            printf("false\n");
            return;
        }
    }
    printf("true\n");
}
/*******************************************************************/

int main() {
    //sample sets for setArray
	int elem1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int *p_elem1;
	p_elem1 = elem1;
	set_t set1 = {.lineNum = 2, .elements = p_elem1};	

	int elem2[] = {1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
	int *p_elem2;
	p_elem2 = elem2;
	set_t set2 = {.lineNum = 3, .elements = p_elem2};

    set_union(set1, set2);
    return 0;
}