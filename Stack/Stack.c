//---------------------------------------------------
// AUTHOR: Mariano Arce Jop
// FILENAME: Stack 
// SPECIFICATION: First Lab Fall 2021
// FOR: CS2413 Data Structures
// Time Spent: 4 hours
//---------------------------------------------------

#include<stdio.h>
#include<string.h>

typedef struct stack_s {
int top; // Indicates the top position in the stack
int max; // Indicates the maximum number of characters in the stack
char array[35]; // Holds the actual stack
} stack_t;

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
        printf("No Elements in the Stack");
    } else {
        return(stack->array[stack->top-1]);
    }
}

void display(stack_t *stack){
// Name: display
// Purpose: Display the stack
// Inputs: Stack pointer
// Outputs: None

    for(int i=((stack->top)-1);i!=-1;i--){
        printf("%c",stack->array[i]);
    }
}

void isEmpty(stack_t *stack){
// Name:  isEmpty
// Purpose: Checks if the stack is empty
// Inputs: Stack pointer
// Outputs: None
    if(stack->top=0){
        printf("Stack is empty");
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

void parse(stack_t *stack, char string[35]){
// Name: parse
// Purpose: User input and parsing the string (removing non-letter chars)
// Inputs: Stack pointer and character string to fill with original user input
// Outputs: None

    char ch;
    int c=0;

    printf("Type a phrase to check: ");

    while(ch!='\n'&&c<34){
    
        ch = getchar();

        string[c]=ch;
        c++;

        if((ch<='Z')&&(ch>='A')){
            ch = c2l(ch);
            push(stack,ch);
        } else if((ch<='z')&&(ch>='a')){
            push(stack,ch);
        }
    }
    string[c]='\0';
}

void print(char string[35]){
// Name: print
// Purpose: Prints a string
// Inputs: Char to print
// Outputs: None

    for(int i=0;i<strlen(string);i++){
        printf("%c",string[i]);
    }
}

int palindrome(stack_t *stack){
// Name: palindrome
// Purpose: Checks if a phrase is a palindrome
// Inputs: Stack pointer
// Outputs: Boolean int (0 if true)

    int max = stack->top;
    char string1[35];
    char string2[35];
    int i;

    for(i=0;i<max;i++){
        string1[i]=pop(stack);
    } string1[i]='\0';

    for(i=0;i<max;i++){
        push(stack,string1[i]);
    }

    for(i=0;i<max;i++){
        string2[i]=pop(stack);
    } string2[i]='\0';

    return(strcmp(string1,string2));
}

int main(void){

    struct stack_s stack={0,35};
    stack_t *st_pt = &stack;
    char string[35];
    int p;

    printf("Welcome to Palindrome Verifier 9000\n");

    parse(st_pt,string);

    p = palindrome(st_pt);

    printf("Your string: ");

    print(string);

    if(p==0){
        printf("Is a palindrome!\n");
    } else {
        printf("Is not a palindrome.\n");
    }

    getchar();
}