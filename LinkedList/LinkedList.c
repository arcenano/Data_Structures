/*
**-------------------------------------------------------------------------------
** AUTHOR: Mariano Arce Jop
** FILENAME: LinkedList
** SPECIFICATION: Second Lab Fall 2021
** FOR: CCS2413 Data Structures
** TIME SPENT: ~8 Hrs
**-------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>

// Node Structure

typedef struct node_s
{
	char data; //Holds the character 
	struct node_s *p_next; // Holds the next node's address
} node_t;

// Function Prototypes

void add_node_at_front(node_t **pp_head, char value);
void add_node_at_end(node_t **pp_head, char value);
int add_node_after_value(node_t **pp_head, char posval, char value);
int remove_node_with_value(node_t **pp_head, char value);
void delete_list(node_t **pp_head);
void print_list(node_t *p_head);
void fill(node_t **pp_head);
void min_max(node_t *p_head);
void order_list(node_t **pp_head);
void find_mean(node_t *p_head);
void find_median(node_t *p_head);
void find_mode(node_t *p_head);
void remove_duplicates(node_t **pp_head);

int main(void){

node_t *p_head = NULL; // Holds the pointer to the list's first node

printf("Character Linked List Stats Calculator\n");

fill(&p_head);

min_max(p_head);

printf("Printing List\n");

print_list(p_head);

order_list(&p_head);

find_mean(p_head);

find_median(p_head);

find_mode(p_head);

printf("Removing Duplicates\n");

remove_duplicates(&p_head);

printf("Printing List\n");


print_list(p_head);

find_mean(p_head);

find_median(p_head);

find_mode(p_head);

delete_list(&p_head);

getchar();

}

// Function Definitions

void add_node_at_front(node_t **pp_head, char value) {
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

void add_node_at_end(node_t **pp_head, char value) {
//Name: add_node_at_end
//Purpose: Adds a node at the end of the list
//Inputs: Pointer to list and character
//Outputs: No Outputs

	node_t *p_node; // Pointer to a node
	node_t *p_last; // Pointer to the last node
	
	/* Add one node */
	p_node = malloc(sizeof(node_t));
	if (p_node == NULL) {
		printf("Failed to allocate memory\n");
		return;
	}
	
	/* Initialize node */
	p_node->data = value;
	p_node->p_next = NULL;
	
	/* Was the list empty? */
	if (*pp_head == NULL) {
		/* Make the head point to the new node */
		*pp_head = p_node;
	}
	else {
		/* Find the last node on the list */
		p_last = *pp_head;                                
		while (p_last->p_next != NULL) {
			p_last = p_last->p_next;
		}

		/* Make the last node point to the new node */
		p_last->p_next = p_node;
	}
}



int add_node_after_value(node_t **pp_head, char posval, char value) {
//Name: add_node_after_value
//Purpose: Adds a node to the list after a value
//Inputs: Pointer to head, char before insertion, char to add
//Outputs: 1 if successful or 0 if unsuccessful

	node_t *p_node; // Pointer to a node
	node_t *p_last; // Pointer to the last node

	/* Is the list empty? */
	if (*pp_head == NULL) {
		return (0);
	}
	
	/* Is the first node a match? */
	if ((*pp_head)->data == posval) {
		/* Add one node */
		p_node = malloc(sizeof(node_t));
		if (p_node == NULL) {
			printf("Failed to allocate memory\n");
			return(0);
		}

		/* Initialize Value */
		p_node->data = value;

		/* Add node in order */
		p_node->p_next = (*pp_head)->p_next;
		(*pp_head)->p_next = p_node;

		return(1);		
	}
	else {
		/* Find the first match.  Keep track of the last node */
		p_last = *pp_head;
		while((p_last != NULL) && (p_last->data != value)) {
			p_last = p_last->p_next;
		}

		/* Did we find it? */
		if (p_last == NULL) {
			/* Didn't find it */
			return(0);
		}
		else
		{
			/* Found it.  Add new node */
			p_node = malloc(sizeof(node_t));
			if (p_node == NULL) {
				printf("Failed to allocate memory\n");
				return(0);
			}

			/* Initialize Value */
			p_node->data = value;

			/* Add node in order */
			p_node->p_next = p_last->p_next;
			p_last->p_next = p_node;
			return(1);
		}
	}
}

int remove_node_with_value(node_t **pp_head, char value) {
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

void delete_list(node_t **pp_head){
//Name:  delete_list
//Purpose: Deletes the linked list
//Inputs: Pointer to list head
//Outputs: No outputs

	node_t *p_node = *pp_head; // Pointer to the first node
	node_t *p_nexxt; // Pointer to the next node

	/* Traverse list deleting nodes */
	while(p_node!=NULL){
		p_nexxt = p_node->p_next;
		free(p_node);
		p_node = p_nexxt;
	}

	/* Dereference head pointer */
	*pp_head = NULL;

	printf("List was deleted.\n");
}


/* Traverses the linked list printing all the values */
void print_list(node_t *p_head){
//Name: print_list
//Purpose: Prints the list
//Inputs: Pointer to head
//Outputs: No outputs

	node_t *p_node; // Pointer to a node
	
	p_node = p_head;
	while (p_node != NULL)
	{
		printf("%c\n", p_node->data);
		p_node = p_node->p_next;
	}
}

void fill(node_t **pp_head) {
//Name: fill
//Purpose: Fills the list with random characters
//Inputs: Pointer to the list head
//Outputs: No Outputs

	for(int c = 0;c<75;c++) {
		char randomletter = 'A' + (rand() % 26);
		add_node_at_end(pp_head,randomletter);
	}
}

void min_max(node_t *p_head){
//Name: min_max
//Purpose: Finds the min and max values and their position
//Inputs: Pointer to list head
//Outputs: No outputs

	node_t *p_node = p_head; // Pointer to the first node
	char min = 'Z'; // Largest Character
	char max = 'A'; // Smallest Character
	int pos = 1; // Holds the current position
	int minpos; //Saves the position of the minimum value
	int maxpos; // Saves the position of the maximum value

	/* Traversing the list */
	while(p_node!=NULL){
		/* Checking and assigning min and max */
		if((p_node->data)<min){
			min = p_node->data;
			minpos = pos;
		} if ((p_node->data)>max) {
			max = p_node->data;
			maxpos= pos;
		}

		/* Moving to next node */
		p_node = p_node->p_next;
		pos += 1;
	}

	/* Print Results */
	printf("The Maximum is %c. ",max);
	printf("This letter is at position: %d\n",maxpos);
	printf("The Minimum is %c. ",min);
	printf("This letter is at position: %d\n",minpos);
}

void order_list(node_t **pp_head) {
//Name: order_list
//Purpose: Orders the list in alphabetical order
//Inputs: Pointer to list head
//Outputs: No Outputs

	node_t *p_node; // Pointer to a node
	node_t *p_old = *pp_head; // Pointer to the first current node
	char letter = 'Z'; // First character counting backwards

	/* Ordering the first node */
	while(!remove_node_with_value(&p_old,letter)){
		letter-=1;
	}

	/* Add one node */
	p_node = malloc(sizeof(node_t));
	if (p_node == NULL) {
		printf("Failed to allocate memory\n");
		return;
	}
	
	/* Initialize node */
	p_node->data = letter;
	
	/* The new node points to whatever p_head was pointing to (could be NULL) */
	p_node->p_next = NULL;
	
	/* Make the head point to the new node */
	*pp_head = p_node;

	/* Looping through old list moving ordered items to front*/
	while(p_old!=NULL){
		if(remove_node_with_value(&p_old,letter)){
			add_node_at_front(pp_head,letter);
		} else {
			letter -= 1;
		}
	} 
}

void find_mean(node_t *p_head){
//Name: find_mean
//Purpose: Computes the mean of the list
//Inputs: Pointer to list head
//Outputs: No Outputs

	node_t *p_node = p_head; // Pointer to the first node
	int sum = 0; // Adds the total sum
	int c = 0; // Keeps count
	char mean; // Holds the mean value

	while (p_node != NULL) {
		sum += p_node->data;
		p_node = p_node->p_next;
		c+=1;
	}

	mean = (char)(sum/c);

	printf("The mean is: %c\n",mean);
}

void find_median(node_t *p_head){
//Name: find_median
//Purpose: Computes the median of the list
//Inputs: Pointer to list head
//Outputs: No Outputs

	node_t *p_node = p_head; // Pointer to the first node
	int c = 0; // Keeps count
	double mid; // To compute the midpoint
	char median; // Holds the median

	/* Finding list midpoint */
	while (p_node != NULL) {
		p_node = p_node->p_next;
		c+=1;
	} 
	
	p_node = p_head;

	mid = c/2;

	/* Computing and printing median */
	if(c%2==0){
		for(c=1;c<mid;c++){
			p_node = p_node->p_next;
		}
		median = (char)((p_node->data+p_node->p_next->data)/2);

	} else {
		mid += 0.5;
		for(c=1;c<mid;c++) {
			p_node = p_node->p_next;
		}
		median = p_node->data;
	}
	printf("The median is: %c\n",median);
}

void find_mode(node_t *p_head){
//Name: find_mode
//Purpose: Computes the mode of the list
//Inputs: Pointer to the list head
//Outputs: No outputs

	node_t *p_node = p_head; // Pointer to the first node
	int c = 0; // Keeps count
	int tc = 0; // Total Count
	int i = 0; // Looping variable
	char mode[10]; // Array holding the most popular characters
	char cmp; // Character to compare
	char ch; // Holds the character being checked

		/*Traverse through the list */
		while(p_node!=NULL) {
		ch = p_node->data;
		cmp = p_node->data;

			/* Count each character's reps */
			while(ch==cmp) {
				c += 1;
				p_node=p_node->p_next;
				if(p_node!=NULL){
					cmp = p_node->data;
				} else {
					cmp = 'a';
				}
			}

			/* Keep the highest rep count */
			if(c>tc){
				tc = c;
			}
			c = 0;
		}

		if(tc==1){
			printf("All characters have 1 repetition, they are all the mode.\n");
		} else {
			/* Obtain all other characters with the same reps */
			p_node = p_head;
			while(p_node!=NULL) {
			ch = p_node->data;
			cmp = p_node->data;

				/* Count each character's reps */
				while(ch==cmp) {
					c += 1;
					p_node=p_node->p_next;
					if(p_node!=NULL){
						cmp = p_node->data;
					} else {
						cmp = 'a';
					}
				}

				/* Add all other modes */
				if(c==tc){
					mode[i]=ch;
					i++;
				}
				c = 0;
			}
					
			/* Print Results */ 
			printf("The modes, with %d repetitions are: ",tc);

			for(c=0;c<(i-1);c++){
				printf("%c, ",mode[c]);
			}
			printf("and %c.\n",mode[c]);
		}
}

void remove_duplicates(node_t **pp_head) {
//Name: remove_duplicates
//Purpose: Removing the letter duplicates from the list
//Inputs: Pointer to the head of the list
//Outputs: No Outputs

	node_t *p_node = *pp_head; // Pointer to the first node
	int i; // Checks if removal was successful
	char ch; //Holds character whose duplicates are being removed
	
	while(p_node!=NULL){
		ch=p_node->data;
		i = 1;
		while(i==1){
			i = remove_node_with_value(&p_node->p_next,ch);
		}
		p_node=p_node->p_next;
	}
}
