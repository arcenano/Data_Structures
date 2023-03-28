//---------------------------------------------------
// AUTHOR: Mariano Arce Jop
// FILENAME: treeMath
// SPECIFICATION: Sixth Lab Fall 2021
// FOR: CS2413 Data Structures
// Time Spent: 10 hours
//---------------------------------------------------

#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

struct node {
    char data; // Holds character value
    struct node *left; // Points to left child
    struct node *right; // Points to right child
};

typedef struct stacki_s {
int top; // Indicates the top position in the stack
int max; // Indicates the maximum number of characters in the stack
int array[35]; // Holds the actual stack
} stacki_t;

typedef struct stack_s {
int top; // Indicates the top position in the stack
int max; // Indicates the maximum number of characters in the stack
char array[35]; // Holds the actual stack
} stack_t;

struct node *tree;
void create_tree(struct node *);
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
struct node *deleteTree(struct node *);
void print_tree(struct node*,int);
void input(char string[35]);
void push(stack_t *stack, char value);
char pop(stack_t *stack);
char peek(stack_t *stack);
int isEmpty(stack_t *stack);
void isFull(stack_t *stack);
char c2l(char c);
int isOperand(char ch);
int precedence(char ch);
void pushi(stacki_t *stacki, int value);
int popi(stacki_t *stacki);
void postfix(char expression[35],char output[35], stack_t *stack);
int postfixEval(char postfix[35],stacki_t *stacki);
void reverse(char orig[35],char reverse[35]);
char* buildtree(struct node**, char*);
double evaluate(struct node* tree);

int main(){
    srand(time(0));
    char uinput[35]; // Holds user input
    char rev[35]; // Holds reverse user input
    char out[35]; // Holds reverse postfix
    double val; // Holds expression value
    int option; // Hold user selection 


    // Create Stack
    struct stack_s stack={0,35};
    stack_t *st_pt = &stack;
    st_pt->array[0]='\0';

    // Create Tree
    create_tree(tree);

    do{
        printf("\n\n*******************MAIN MENU*******************\n");
        printf("\n 1. Create Expression tree");
        printf("\n 2. Print Prefix Expression");
        printf("\n 3. Print Infix Expression");
        printf("\n 4. Print Postfix Expression");
        printf("\n 5. Print tree");
        printf("\n 6. Evaluate Expression");
        printf("\n 7. Exit");
        printf("\n -- Enter your selection:");

        scanf("%d",&option);
    
        switch(option){
            case 1:
                printf("\n -- Creating Tree.\n");
                //If a tree exists delete it and create a new one
                if(tree!=NULL){
                    tree=deleteTree(tree);
                }

                create_tree(tree);
                    
                input(uinput);

                if(isOperand(uinput[0])==1){
                    // Convert to Prefix
                    reverse(uinput,rev);
                    postfix(rev,out,st_pt);
                    reverse(out,uinput);
                }

                buildtree(&tree,uinput);

                printf("\nTree Created \n");
    
                break;

            case 2: 
                if(tree==NULL){
                    printf("\n -- The tree is empty\n");
                    break;
                }
                printf(" -- Printing prefix expression.\n");
                printf("\n -- The elements of the tree are: \n");
                preorder(tree);
                break;

            case 3:
                if(tree==NULL){
                    printf("\n -- The tree is empty\n");
                    break;
                }
                printf(" -- Printing infix expression.\n");
                printf("\n -- The elements of the tree are: \n");
                inorder(tree);
                break;

            case 4:
                if(tree==NULL){
                    printf("\n The tree is empty\n");
                    break;
                }
                printf(" -- Printing Postfix Expression.\n");
                printf("\n -- The elements of the tree are: \n");
                postorder(tree);
                break;

            case 5:
                printf("\nPrinting Tree\n");
                print_tree(tree,0);
                break;

            case 6:
                printf("\nEvaluating Expresson: \n");

                if(tree!=NULL){

                val = evaluate(tree);

                inorder(tree);

                printf(" = %.2lf",val);

                } else {
                    printf("Empty Tree");
                }
                break;

            case 7:
                break;

            default:
                printf("Unknown command");

        }
    }while(option!=7);

    printf("\n -- Exiting...\n");
    getch();
    return 0;
}

void create_tree(struct node *tree){
// Name: create_tree
// Purpose: Creates the BST
// Inputs: Pointer of type node
// Outputs: None

    tree = NULL;
}


void preorder(struct node *tree){
// Name: preorder
// Purpose: Prints the tree in preorder
// Inputs: Pointer to the root of the tree
// Outputs: None

    if(tree != NULL){
        printf("%c\t",tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void inorder(struct node *tree){
// Name: inorder
// Purpose: Prints the tree in inorder
// Inputs: Pointer to the root of the tree
// Outputs: None

    if(tree != NULL){
        inorder(tree->left);
        printf("%c\t",tree->data);
        inorder(tree->right);
    } 
}

void postorder(struct node *tree){
// Name: postorder
// Purpose: Prints the tree in postorder
// Inputs: Pointer to the root of the tree
// Outputs: None
    if(tree != NULL){
        postorder(tree->left);
        postorder(tree->right);
        printf("%c\t",tree->data);
    }
}

struct node *deleteTree(struct node *tree){
// Name: deleteTree
// Purpose: Deletes the BST
// Inputs: Pointer to the root of the tree
// Outputs: Pointer to NULL

    if(tree!=NULL){
        deleteTree(tree->left);
        deleteTree(tree->right);
        free(tree);
    }
    tree=NULL;
    return(tree);
}

/* Print tree contents hierarchically */
void print_tree(struct node *tree, int level){

	int i;
	
	if (tree != NULL)
	{
		print_tree(tree->right, level+2);

		for (i=0; i<level; i++)
		{
			putchar(' ');
		}
		printf("%c\n", tree->data);
		
		print_tree(tree->left, level+2);
	}
}

void input(char string[35]){
// Name: input
// Purpose: User input and parsing the string (removing non-letter chars)
// Inputs: Character string to fill with original user input
// Outputs: None

    char ch;
    int c=0;

    getchar();

    printf("Type your expression: ");

    while(ch!='\n'&&c<34){
    
        ch = getchar();

        string[c]=ch;
        c++;

    }
    string[c-1]='\0';
}


void push(stack_t *stack, char value){
// Name: push
// Purpose: Push functionality implementation (ad character to stack)
// Inputs: Stack pointer and input character
// Outputs: None

     if(stack->top<stack->max-1){
        stack->array[stack->top]=value;
        stack->top += 1;
        stack->array[stack->top]='\0';
    } else{
        printf("The stack is full\n");
    }
}

char pop(stack_t *stack){
// Name: pop 
// Purpose: Pop functionality implementation (remove character from stack top)
// Inputs: Stack pointer
// Outputs: Character that was removed from stack

    char ch;
    if(stack->top!=0){
        ch = stack->array[stack->top-1];
        stack->array[stack->top-1]='\0';
        stack->top -= 1;
        return(ch);
    } else {
        printf("UNDERFLOW\n");
    }
}


char peek(stack_t *stack){
// Name: peek
// Purpose: Peek functionality implementation (return character in stack top)
// Inputs: Stack pointer
// Outputs: Character in stack top

    if(stack->top==0){
        //printf("No Elements in the Stack");
    } else {
        return(stack->array[stack->top-1]);
    }
}

int isEmpty(stack_t *stack){
// Name:  isEmpty
// Purpose: Checks if the stack is empty
// Inputs: Stack pointer
// Outputs: None
    if(stack->top==0){
        return(1);
    } else {
        return(0);
    }
}

void isFull(stack_t *stack){
// Name: isFull
// Purpose: Checks if the stack is full
// Inputs: Stack pointer
// Outputs: None
    if(stack->top==stack->max-1){
        printf("Stack is full");
    }
}

char c2l(char c) {
// Name: c2l (Character to lower)
// Purpose: Turns a character into lowercase
// Inputs: Character
// Outputs: Character in lowercase
    if((c<='Z')&&(c>='A')){
        c = c + 32;
    }
    return(c);
}

int isOperand(char ch) 
// Name: isOperand
// Purpose: Checks if a char is a digit
// Inputs: Character
// Outputs: Integer with 1 if true or 0 if false
{ 
    if(ch >= '0' && ch <= '9'){
        return(1);
    } else {
        return(0);
    }
} 
  
int precedence(char ch) 
// Name: precedence
// Purpose: Computes the operator presedence
// Inputs: Character
// Outputs: Integer with presedence
{ 
    switch (ch) { 
    case '+': 
    case '-': 
        return(0); 
  
    case '*': 
    case '/': 
    case '%':
        return(1); 
    } 
    return(-1); 
} 

void pushi(stacki_t *stacki, int value){
// Name: pushi
// Purpose: Push functionality implementation (add int to stack)
// Inputs: Stack pointer and input integer
// Outputs: None

     if(stacki->top<stacki->max-1){
        stacki->array[stacki->top]=value;
        stacki->top += 1;
        stacki->array[stacki->top]='\0';
    } else{
        printf("The stack is full\n");
    }
}

int popi(stacki_t *stacki){
// Name: popi
// Purpose: Pop functionality implementation (remove integer from stack top)
// Inputs: Stack pointer
// Outputs: Integer that was removed from stack

    int num; //Holds value being removed
    if(stacki->top!=0){
        num = stacki->array[stacki->top-1];
        stacki->array[stacki->top-1]='\0';
        stacki->top -= 1;
        return(num);
    } else {
        printf("UNDERFLOW\n");
    }
}

void postfix(char expression[35],char output[35], stack_t *stack){
// Name: postfix
// Purpose: Changes a mathematical expression to postfix
// Inputs: Expression array, output array, and a pointer to a stack
// Outputs: None

    int c = 0;
    int z = 0;
    while(expression[c]!='\0'){
        if(expression[c]==' '){
            c++;
            continue;
        }
        
        if(expression[c]=='('){
            expression[c]=')';
        } else if(expression[c]==')'){
            expression[c]='(';
            
        }

        if(isOperand(expression[c])==1){
            output[z]=expression[c];
            z++;
        } else if(expression[c]==')'||expression[c]=='}'||expression[c]==']'){

            while((peek(stack)!='(')&&(peek(stack)!='{')&&(peek(stack)!='[')&&(isEmpty(stack)==0)){
                output[z] = pop(stack);
                z++;
            }
            pop(stack);
            
        } else if(expression[c]=='('||expression[c]=='{'||expression[c]=='['){
            push(stack,expression[c]);
        } else {
            output[z]=' ';
            z++;
            while((precedence(expression[c])<=precedence(peek(stack)))&&(isEmpty(stack)==0)){
                output[z] = pop(stack);
                z++;
            }
            push(stack,expression[c]);
        }
        c++;
    }

    while(isEmpty(stack)==0){
        output[z] = pop(stack);
        z++;
    }

    output[z]='\0';
}

void reverse(char orig[35],char reverse[35]){
// Name: reverse
// Purpose: Reverses a string
// Inputs: Original string and output string
// Outputs: None
    
    int l = strlen(orig); // Holds string length
    int i; // Counter Variable

    for(i=1;i<=l;i++){
        reverse[i-1]=orig[l-i];
    }
    reverse[i-1]='\0';
}

char* buildtree(struct node** tree, char* string){
// Name: buildtree
// Purpose: Creates a tree from an expression string
// Inputs: Pointer to tree root and string 
// Outputs: Pointer to last character extracted

    if(*string=='\0'){
        return('\0');
    }

    while(1){

        if(*string==' '){
            string+=1;
            continue;
        }
        
        if(*tree==NULL){
            struct node* new=(struct node*)malloc(sizeof(struct node)); // Pointer to new node
            new->data = *string;
            new->left = NULL;
            new->right = NULL;
            *tree = new;

        } else {

            if(isOperand(*string)){
                return(string);
            }

            char* ptr = NULL; // Pointer to last character extracted

            ptr = buildtree(&(*tree)->left,string+1);
            ptr = buildtree(&(*tree)->right,ptr+1);

            return(ptr);

        }
    }
}

double evaluate(struct node* tree){
// Name: evaluate
// Purpose: Evaluates the expression in the tree
// Inputs: Pointer to the expression tree root
// Outputs: The expression evaluation as type double

    double leftn; // Holds solution to the left branch
    double rightn; // Holds solution to the right branch

    if(tree==NULL){
        return(0);
    }

    if(tree->left==NULL&&tree->right==NULL){
        return(((double)tree->data)-48);
    }

    leftn = evaluate(tree->left);
    rightn = evaluate(tree->right);

    switch(tree->data){
        case('+'):
            return(leftn+rightn);
        case('-'):
            return(leftn-rightn);
        case('*'):
            return(leftn*rightn);
        case('/'):
            return(leftn/rightn);
        case('%'):
            return((int)leftn%(int)rightn);
    }

    return(0);
}
