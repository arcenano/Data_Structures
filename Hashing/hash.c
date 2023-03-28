//---------------------------------------------------
// AUTHOR: Mariano Arce Jop
// FILENAME: hash
// SPECIFICATION: Eighth Lab Fall 2021
// FOR: CS2413 Data Structures
// Time Spent: 4 hours
//---------------------------------------------------

#include<stdio.h>
#include<stdlib.h>

typedef struct node_s
{
	int data; //Holds the character 
	struct node_s *p_next; // Holds the next node's address
} node_t;

void add_node_at_front(node_t **pp_head, int value);
void print_list(node_t *p_head);
int remove_node_with_value(node_t **pp_head, int value);
void insert(node_t *ptable[], int key);
void print(node_t *ptable[]);
void delete(node_t *ptable[],int key);
void search(node_t *ptable[], int key);
void test(node_t *ptable[]);

int main(){
    node_t *table[9]; // Hash Table
	int option; // User Selection
	int value; // Holds user value

	// Allocate structures in table
	for(int i=0;i<9;i++){
		table[i]=NULL;
	}

	test(table);

	printf("\n**************HASH IMPLEMENTATION**************\n");
	printf("===============================================");

    do{
        printf("\n\n*******************MAIN MENU*******************\n");
        printf("\n 1. Insert a new value");
        printf("\n 2. Delete a value");
        printf("\n 3. Search for a value");
        printf("\n 4. Print hash table");
        printf("\n 5. Exit");
	    printf("\n -- Enter your selection:");

		scanf("%d",&option);

		switch(option){
            case 1:
				printf("Enter a value to insert:");
				scanf("%d",&value);
				insert(table,value);
				printf("Value inserted.\n");
                break;

            case 2: 
				printf("Enter a value to delete:");
				scanf("%d",&value);
				delete(table,value);
                break;

            case 3:
				printf("Enter a value to search:");
				scanf("%d",&value);
				search(table,value);
                break;

            case 4:
				printf("Printing Values:\n");
				print(table);

                break;

            case 5:
                break;

            default:
                printf("Unknown command");
        }

    } while(option!=5);

    printf("\n -- Exiting...\n");
	getchar();
    getchar();
}

//Function Definitions

void add_node_at_front(node_t **pp_head, int value) {
//Name: add_node_at_front
//Purpose: Adds a node at front
//Inputs: Pointer to the list and character
//Outputs: No outputs

	node_t *p_node; // Pointer to a node
	
	/* Add one node */
	p_node = malloc(sizeof(node_t));
	if (p_node == NULL) {
		printf("Failed to allocate memory\n");
		return;
	}
	
	/* Initialize node */
	p_node->data = value;
	
	/* The new node points to whatever p_head was pointing to (could be NULL) */
	p_node->p_next = *pp_head;
	
	/* Make the head point to the new node */
	*pp_head = p_node;
}

void print_list(node_t *p_head){
//Name: print_list
//Purpose: Prints the list
//Inputs: Pointer to head
//Outputs: No outputs
	node_t *p_node; // Pointer to a node
	
	p_node = p_head;
	while (p_node != NULL){
		printf("%d ", p_node->data);
		p_node = p_node->p_next;
        if(p_node!=NULL){
            printf("-> ");
        }
    }
}

int remove_node_with_value(node_t **pp_head, int value) {
//Name: remove_node_with_value
//Purpose: Removes a node with a specific value
//Inputs: Pointer to the list and the value to be removed
//Outputs: 1 if successful or 0 if unsuccesful

	node_t *p_node; // Pointer to a node
	node_t *p_last; // Pointer to the last node
	
	/* Is the list empty? */
	if (*pp_head == NULL) {
		return (0);
	}
	
	/* Is the first node a match? */
	if ((*pp_head)->data == value) {
		/* Delete from front */
		p_node = *pp_head;
		
		/* Skip node in linked list */
		*pp_head = p_node->p_next;
		
		/* Free node */
		free(p_node);
		
		return(1);		
	}
	else {
		/* Find the first match.  Keep track of the last node */
		p_last = *pp_head;
		while((p_last->p_next != NULL) && (p_last->p_next->data != value)) {
			p_last = p_last->p_next;
		}

		/* Did we find it? */
		if (p_last->p_next == NULL) {
			/* Didn't find it */
			return(0);
		} else {
			/* Found it.  Remove it */
			p_node = p_last->p_next;
			p_last->p_next = p_node->p_next;
			
			/* Free node */
			free(p_node);
			return(1);
		}
	}
}

void insert(node_t *ptable[], int key){
// Name: insert
// Purpose: Inserts a value into the hash table
// Inputs: Hash table
// Outputs: None

    node_t *p_node;

	int hash = key%9;

    if(ptable[hash]==NULL){
		ptable[hash]=malloc(sizeof(node_t));
        ptable[hash]->data=key;
		ptable[hash]->p_next=NULL;
    } else {
        add_node_at_front(&ptable[hash],key);
    }
}

void print(node_t *ptable[]){
// Name: print
// Purpose: Prints the entire hash table
// Inputs: Hash table array
// Outputs: None

	for(int i=0;i<9;i++){
		printf("%d: ",i+1);
		print_list(ptable[i]);
		printf("\n");
	}
}


void delete(node_t *table[],int key){
// Name: delete
// Purpose: Deletes a given value from hash table
// Inputs: Hash table array, value to delete
// Outputs: None

	int hash = key%9;

	int success = remove_node_with_value(&table[hash],key);

	if(success==1){
		printf("%d was deleted.\n",key);
	} else {
		printf("%d was not found.\n",key);
	}
}


void test(node_t *ptable[]){
// Name: test
// Purpose: Inputs test keys
// Inputs: Hash table array
// Outputs: None

	insert(ptable,7);
	insert(ptable,24);
	insert(ptable,18);
	insert(ptable,52);
	insert(ptable,36);
	insert(ptable,54);
	insert(ptable,11);
	insert(ptable,23);
}

void search(node_t *ptable[], int key){
// Name: search
// Purpose: Search for a value in the hash table
// Inputs: Hash table array, value to search for
// Outputs: None

	int hash = key%9; // Holds hash
	int c = 1; // Counter

	/* Is the list empty? */
	if (ptable[hash] == NULL) {
		printf("Value not found.\n");
		return;
	}

	node_t *p_node = ptable[hash];

	while(p_node->p_next != NULL && p_node->data != key){
		p_node=p_node->p_next;
		c++;
	}
	
	if(p_node->data==key){
		printf("Value found in hash %d, at position %d of the linked list.\n",hash+1,c);
	} else {
		printf("Value not found.\n");
	}
}