//
//
//
//
//
//
//

#include<stdio.h>
#include<string.h>
#include <ctype.h> 


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

void display(stack_t *stack){
// Name: display
// Purpose: Display the stack
// Inputs: Stack pointer
// Outputs: None

    for(int i=((stack->top)-1);i!=-1;i--){
        printf("%c",stack->array[i]);
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

void input(char string[35]){
// Name: input
// Purpose: User input and parsing the string (removing non-letter chars)
// Inputs: Character string to fill with original user input
// Outputs: None

    char ch;
    int c=0;

    printf("Type your expression: ");

    while(ch!='\n'&&c<34){
    
        ch = getchar();

        string[c]=ch;
        c++;

    }
    string[c-1]='\0';
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
    printf("Infix: %s\n", expression);
    printf("Postfix: %s\n", output);

}

int postfixEval(char postfix[35],stacki_t *stacki){
// Name: postfixEval
// Purpose: Evaluates postfix expression
// Inputs: Postfix expression as an array, Pointer to stack with int array
// Outputs: Integer with expression result
    int c = 0; // Keeps count
    int n = 0; // Used for cast conversion
    int x1; // Cast conversion and operations
    int x2; // Cast conversion and operations
    int ans; // Transfers the answer to return

    while(postfix[c]!='\0'){
        if(postfix[c]==' '||postfix[c]=='\n'){
            c++;
            continue;
        }
    
        if(isdigit(postfix[c])==1){
            n=(int)(postfix[c]-'0');
            pushi(stacki,n);
        } else {

            x1 = popi(stacki);
            x2 = popi(stacki);

            if(postfix[c]=='+'){
                ans = x1+x2;
                pushi(stacki,ans);
            } else if(postfix[c]=='-'){
                ans = x2 - x1; 
                pushi(stacki,ans);
            } else if(postfix[c]=='*'){
                ans = x1*x2;
                pushi(stacki,ans);
            } else if(postfix[c]=='/'){
                ans = x2/x1;
                pushi(stacki,ans);
            }
        }
        c++;
    }

    ans = popi(stacki);
    return(ans);
}


int main(void) {

    char expression[35];
    char output[35];

    // Get user input
    input(expression);

    // Create Stack
    struct stack_s stack={0,35};
    stack_t *st_pt = &stack;
    st_pt->array[0]='\0';

    postfix(expression,output,st_pt);

    struct stacki_s stacki={0,35};
    stacki_t *sti_pt = &stacki;
    sti_pt->array[0]='\0';

    int x = postfixEval(output,sti_pt);

    printf("Result: %d",x);

    getchar();

    }