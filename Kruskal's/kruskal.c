//---------------------------------------------------
// AUTHOR: Mariano Arce Jop
// FILENAME: kruskal
// SPECIFICATION: Tenth Lab Fall 2021
// FOR: CS2413 Data Structures
// Time Spent: 6 hours
//---------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
	char name; //Holds the identifier 
	struct node_s *connections[20];
    int weights[20];
} node_t;

typedef struct stack_s {
int top; // Indicates the top position in the stack
int max; // Indicates the maximum number of characters in the stack
node_t *array[20]; // Holds the actual stack
} stack_t;

typedef struct queue_s { 
    int front; // Holds front of queue index
    int end; // Holds end of queue index
    node_t *array[20]; // Holds Queue Array
} queue_t;

node_t* pop(stack_t *stack); // Stack Pop
void push(stack_t *stack, node_t *node); // Stack Push
node_t* search(char letter, node_t *start); // Node Search 
int addConnection(node_t **start, char n1, char n2, int weight); // Add connection
int checkArray(node_t *node, node_t *array[20]); // Check array for value
node_t* newNode(node_t* node,char letter); // Add new node to graph
void writeConnections(node_t *start); // Write file with connections
void depthFirst(node_t *start); // Depth First Traversal
void orderArrays(char (*n1a)[100],char (*n2a)[100],int (*weights)[100]); // Order Arrays
int isCycle(node_t *start); // Checks if there is a cycle
int kruskal(int vertices, char n1a[100], char n2a[100],int weights[100]);
int vertexCount(node_t *start);

void main(){

	node_t *start = NULL; // Graph Start
    FILE *fp; // File pointer
	int weights[100]; //Weights
	char n1a[100]; // Node 1 array
	char n2a[100]; // Node 2 Array
    char ch; // File Character
	char n1='\0'; // Node 1
	char n2='\0'; // Node 2
	int weight=0; // Weight
	int done=0; // Loop Control
	int suc; // Connection success
	int i=0; // Counter variable
	int num;

	printf("Graph Reader\n");
	printf("\n==============\n");
	printf("Creating graph\n");

    fp = fopen("connections.txt","r");

	if(fp == NULL){
		printf("Couldn't open file\n");
		return;
	}

	for(int c=0;c<100;c++){
		weights[c]=1000;
		n1a[c]='\0';
		n2a[c]='\0';
	}

	while(!done){
    	ch = getc(fp);
		switch(ch){

			case ',':
				break;

			case '\n':
				if(!addConnection(&start,n1,n2,weight)){
					printf("Couldn't Add Node");
					return;
				}

				n1a[i]=n1;
				n2a[i]=n2;
				weights[i]=weight;
				i++;

				n1='\0';
				n2='\0';
				weight=0;
				break;

			case EOF:
				done=1;
				break;

			default:
				if(n1=='\0'){
					n1=ch;

				} else if(n2=='\0'){
					n2=ch;

				} else {
					weight=(int)ch-48;
				}
		}
	}

	printf("Graph created\n\n");

	depthFirst(start);
	num=vertexCount(start);

	printf("\n");
	printf("Writing Connections\n");

	writeConnections(start);

	printf("%d",isCycle(start));

	//kruskal(num-1,n1a,n2a,weights);

	printf("Connections Written\n\n");

	printf("Press enter to exit");

	getchar();
}

// ****************
// STACK FUNCTIONS
// ****************

void push(stack_t *stack, node_t *node){
// Name: push
// Purpose: Push functionality implementation (ad character to stack)
// Inputs: Stack pointer and input character
// Outputs: None

     if(stack->top<stack->max-1){
        stack->array[stack->top]=node;
        stack->top += 1;
        stack->array[stack->top]='\0';
    } else{
        printf("The stack is full\n");
    }
}

node_t* pop(stack_t *stack){
// Name: pop 
// Purpose: Pop functionality implementation (remove character from stack top)
// Inputs: Stack pointer
// Outputs: Character that was removed from stack

    node_t *ptr;
    if(stack->top!=0){
        ptr = stack->array[stack->top-1];
        stack->array[stack->top-1]='\0';
        stack->top -= 1;
        return(ptr);
    } else {
        printf("UNDERFLOW\n");
    }
}

// ****************
// GRAPH FUNCTIONS
// ****************

node_t* search(char letter, node_t *start){
	node_t *visited[20]; // Holds visited nodes array
	struct stack_s stack={0,20}; // Stack
    stack_t *st_pt = &stack; // Stack pointer
	node_t *vertex; // Holds vertex pointer
	node_t *node; // Holds node pointer
	int c=1; // Counter
	int i; // Counter

	// Name: search
	// Purpose: Search for a node
	// Inputs: Node ID, graph start
	// Outputs: Node pointer

	if(start->name==letter){
		return(start);
	}

	push(st_pt, start);
	visited[0]=start;

	while(st_pt->top!=0){

		i=0;
		vertex = pop(st_pt);
		node=vertex->connections[0];
	
		while(node!=NULL){
			
			if(!checkArray(node,visited)){
				push(st_pt,node);
				visited[c]=vertex;
				c++;
			}

			if(node->name==letter){
				return(node);
			}
			i++;
			node=vertex->connections[i];
		}	
	}
	return(NULL);
}

int checkArray(node_t *node, node_t *array[20]){
	// Name: checkArray
	// Purpose: Check for node in array
	// Inputs: Array for with node pointers and pointer to search for
	// Outputs: Integer 1 if found or 0 if not

	for(int i=0;i<19;i++){
		if(node==array[i]){
			return(1);
		}
	}
	return(0);
}

node_t* newNode(node_t *node, char letter){
	// Name: newNode
	// Purpose: Allocates a new node
	// Inputs: Empty pointer and letter ID
	// Outputs: Node pointer

	node = malloc(sizeof(node_t));

	if (node == NULL) {
		printf("Failed to allocate memory\n");
	return(NULL);
	}

	node->name=letter;

	for(int i=0;i<19;i++){
		node->connections[i]=NULL;
		node->weights[i]=0;
	}

	return(node);
}

int addConnection(node_t **start, char n1, char n2, int weight){
	// Name: addConnection
	// Purpose: Adds a connection to the graph
	// Inputs: Pointer to pointer to graph, node 1 ID, node 2 ID, weight
	// Outputs: 1 If succesful 0 othewise.

	node_t *node1=NULL; // Node Pointer
	node_t *node2=NULL; // Node Pointer
	int i=0; // Counter Variable

	if(*start==NULL){
		*start=newNode(*start,n1);
	}

	node1=search(n1,*start);

	node2=search(n2,*start);

	if(node1==NULL){
		node1=newNode(node1,n1);	}

	if(node2==NULL){
		node2=newNode(node2,n2);
	}

	if (checkArray(node2,node1->connections)){
		return(1);
	}
	
	while(node1->connections[i]!=NULL){
		i++;
	}

	node1->connections[i]=node2;
	node1->weights[i]=weight;
	i=0;

	return(1);
}

void writeConnections(node_t *start){
	// Name: writeConnections
	// Purpose: Writes the connections in the file
	// Inputs: Graph start pointer
	// Outputs: None
	
    FILE *fp; // File pointer
	node_t *visited[20]; // Visited nodes array
	struct stack_s stack={0,20}; // Stack
    stack_t *st_pt = &stack; // Stack pointer
	node_t *vertex; // Vertex pointer
	node_t *node; // Node pointer
	int ctr=0; // Counter
	int c=1; // Counter
	int i; // Counter

	for(i=0;i<19;i++){
		visited[i]=NULL;
	}

	fp = fopen("newConnections.txt","w");

	if(fp == NULL){
		printf("Couldn't open file\n");
		return;
	}

	while(start->connections[ctr]!=NULL){
		putc(start->name,fp);
		putc(',',fp);
		putc(start->connections[ctr]->name,fp);
		putc(',',fp);
		putc((char)start->weights[ctr]+48,fp);
		putc('\n',fp);
		ctr++;
	}

	push(st_pt, start);
	visited[0]=start;

	while(st_pt->top!=0){

		i=0;
		vertex = pop(st_pt);
		node=vertex->connections[0];

		while(node!=NULL){
			
			if(!checkArray(node,visited)){
				push(st_pt,node);
				visited[c]=node;
				c++;
			}

			ctr=0;

			while(node->connections[ctr]!=NULL){
				if(!checkArray(node->connections[ctr],visited)){
				putc(node->name,fp);
				putc(',',fp);
				putc(node->connections[ctr]->name,fp);
				putc(',',fp);
				putc((char)node->weights[ctr]+48,fp);
				putc('\n',fp);
				}
				ctr++;
			}
			
			i++;
			node=vertex->connections[i];
		}
	}
}

void depthFirst(node_t *start){
	// Name: depthFirst
	// Purpose: Depth first search
	// Inputs: Graph start pointer
	// Outputs: None

	node_t *visited[20]; // Visited nodes array
	struct stack_s stack={0,20}; // Stack
    stack_t *st_pt = &stack; // Stack pointer
	node_t *vertex; // Vertex pointer
	node_t *node; // Node pointer
	int c=1; // Counter
	int i; // Counter

	for(i=0;i<19;i++){
		visited[i]=NULL;
	}

	push(st_pt, start);
	visited[0]=start;

	while(st_pt->top!=0){

		i=0;
		vertex = pop(st_pt);
		node=vertex->connections[i];
	
		while(node!=NULL){
			
			if(!checkArray(node,visited)){
				push(st_pt,node);
				visited[c]=node;
				c++;
			}
			i++;
			node=vertex->connections[i];
		}
	}

	printf("Depth First Traversal: ");
	printf("%c",visited[0]->name);

	i=1;

	while(visited[i]!=NULL){
		printf(" - %c",visited[i]->name);
		i++;
	}
	printf("\n");
}

void orderArrays(char (*n1a)[100],char (*n2a)[100],int (*weights)[100]){
	int i;
	int j;
	int t1;
	int t2;
	int t3;

	for (i = 0; i < 100; ++i){
		for (j = i + 1; j < 100; ++j){

			if ((*weights)[i] > (*weights)[j]) {

				t1 = (*n1a)[i];
				(*n1a)[i]=(*n1a)[j];
				(*n1a)[j]=t1;

				t2 = (*n2a)[i];
				(*n2a)[i]=(*n2a)[j];
				(*n2a)[j]=t2;

				t3 = (*weights)[i];
				(*weights)[i]=(*weights)[j];
				(*weights)[j]=t3;
			}
		}
    }
}

int isCycle(node_t *start){
	struct stack_s stack={0,20};
    stack_t *st_pt = &stack;
	node_t *vertex;
	node_t *node;
	char letter;
	int ctr;
	int ctr2;
	int c=1;
	int i;

	letter=start->name;

	push(st_pt, start);

	while(st_pt->top!=0){

		i=0;
		vertex = pop(st_pt);
		node=vertex->connections[0];

		for(ctr=0;ctr<19;ctr++){
			vertex->connections[ctr]=vertex->connections[ctr+1];
		}

		vertex->connections[19]=NULL;

	
		while(node!=NULL){
			
			push(st_pt,node);

			if(node->name==letter){
				return(1);
			}
			i++;

			node=vertex->connections[i];

			for(ctr=i;ctr<19;ctr++){
				vertex->connections[ctr]=vertex->connections[ctr+1];
			}

			vertex->connections[19]=NULL;		
		}
	}
	return(0);
}


int kruskal(int vertices, char n1a[100], char n2a[100],int weights[100]){
	node_t *kstart = NULL; // Krusk's start
	node_t *n;
	int i=1;
	int c=0;

	addConnection(&kstart,n1a[0],n2a[0],weights[0]);

	while(c<vertices-1){

		addConnection(&kstart,n1a[i],n2a[i],weights[i]);

		if(isCycle(kstart)){
			n=search(n1a[i],kstart);
			for(int c=0;c<20;c++){
				if(n->connections[c]->name=n2a[i]){
					n->connections[c]=NULL;
					printf("ha");
					c--;
				}
			}
		}
		c++;
	}
	printf("Kruskal Results");
	depthFirst(kstart);
}


int vertexCount(node_t *start) {

	node_t *visited[20]; // Visited nodes array
	struct stack_s stack={0,20}; // Stack
    stack_t *st_pt = &stack; // Stack pointer
	node_t *vertex; // Vertex pointer
	node_t *node; // Node pointer
	int c=1; // Counter
	int i; // Counter

	for(i=0;i<19;i++){
		visited[i]=NULL;
	}

	push(st_pt, start);
	visited[0]=start;

	while(st_pt->top!=0){

		i=0;
		vertex = pop(st_pt);
		node=vertex->connections[i];
	
		while(node!=NULL){
			
			if(!checkArray(node,visited)){
				push(st_pt,node);
				visited[c]=node;
				c++;
			}
			i++;
			node=vertex->connections[i];
		}
	}

	c=0;

	for(i=0;i<20;i++){
		if(visited[i]!=NULL){
			c++;
		}
	}
	return(c);
}