//---------------------------------------------------
// AUTHOR: Mariano Arce Jop
// FILENAME: queue 
// SPECIFICATION: Fourth Lab Fall 2021
// FOR: CS2413 Data Structures
// Time Spent: 8 hours
//---------------------------------------------------
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define Size 10

typedef struct queue_s { 
    int front; // Holds front of queue index
    int end; // Holds end of queue index
    int array[Size]; // Holds Queue Array
} queue_t;

typedef queue_t *queueptr;

int isFull(queue_t *queue){
// Name: isFull
// Purpose: Checks if queue is full
// Inputs: Pointer to queue
// Outputs: Int 1 if full or 0 if not

    if(queue->front-abs(queue->end)==1||queue->end-queue->front==(Size-1)){
        return(1);
    } else {
        return(0);
    }
}

int isEmpty(queue_t *queue){
// Name: isEmpty
// Purpose: Checks if queue is empty
// Inputs: Pointer to queue
// Outputs: Int 1 if empty or 0 if not

    if(queue->end==-1){
        return(1);
    } else if(queue->front==queue->end){
        return(1);
    } else {
        return(0);
    }
}

int insert(int value, queue_t *queue){
// Name: insert
// Purpose: Inserts a value into the queue if not full
// Inputs: Pointer to queue and value to insert
// Outputs: Int 1 if succesful or 0 if not

    //If queue is not full move end to next position and insert
    if(!isFull(queue)){
        if(queue->end==Size-1){
            queue->end=0;
        } else { 
            queue->end+=1;
        }
    queue->array[queue->end]=value;
    printf("Value Entering: %d\n",value);
    return(1);
    } else {
    //If queue is full print Overflow
        printf("OVERFLOW!\n");
        return(0);
    }
}   

int out(queue_t *queue){
// Name: out
// Purpose: Removes a value from the queue
// Inputs: Pointer to queue
// Outputs: Int 1 if succesful or 0 if not

    if(!isEmpty(queue)){
    //If queue is not empty remove and move front
        printf("Value Leaving: %d\n",queue->array[queue->front]);
        queue->array[queue->front]='\0';
        if(queue->front==Size-1){
            queue->front=0;
        } else {
            queue->front+=1;
        }
        return(1);
    } else {
    //If queue is empty print Underflow
        printf("UNDERFLOW!\n");
        return(0);
    }
}

void printqueue(queue_t *queue){
// Name: printqueue
// Purpose: Prints the queue
// Inputs: Pointer to queue
// Outputs: None

    int i=queue->front; // Queue Index
    int c=1; // Counter

    while(queue->array[i]!='\0'&&c<Size+1){
        printf("Value %d: %d\n",c,queue->array[i]);
        if(i==Size-1){
            i=0;
        } else {
            i++;
        }
        c++;
    }

    if(c==1){
        printf("Queue is empty.\n");
    }
}

int inflow(queueptr priority[3],int reps){
// Name: inflow
// Purpose: Inputs random values into random priorities
// Inputs: Pointer to queue and 'reps' ammount of values to input
// Outputs: Int 1 if succesful or 0 if not

    for(int i=0;i<reps;i++){
    // Loop reps times entering random numbers into random priorities
        int r1=100+rand()%899; // Random number to input
        int r2=rand()%3; // Random priority

        int s = insert(r1,priority[r2]);

        if(s==0){
            return(s);
        }
    }
    return(1);
}

int outflow(queueptr priority[3],int *c){
// Name: isFull
// Purpose: Checks if queue is full
// Inputs: Pointer to queue
// Outputs: Int 1 if full or 0 if not

    int s; // Status of output function calls

    for(int r=2+rand()%3;r>0;r--){
    // Removes 2-4 items from the priority queue in order 1-3
        if(!isEmpty(priority[0])){
            s=out(priority[0]);
        } else if(!isEmpty(priority[1])){
            s=out(priority[1]);
        } else {
            s=out(priority[2]);
        }
        if(s==0){
            return(s);
        }
        *c+=1;
        if(*c>48){
            return(s);
        }
    }
    return(s);
}

void printpriority(queueptr priority[3]){
// Name: printpriority
// Purpose: Prints the priority queue
// Inputs: Pointer to priority array with queues
// Outputs: None

    for(int i=0;i<3;i++){
        printf("\nPriority %d:\n",i+1);
        printqueue(priority[i]);
    }
}

int main(void){
    srand(time(0));
    int c=0; // Counter for removed elements
    int s1; // Status for input function calls
    int s2; // Status for output function calls

    struct queue_s queue1={0,-1}; // Queue 1 initialization
    struct queue_s queue2={0,-1}; // Queue 2 initialization
    struct queue_s queue3={0,-1}; // Queue 3 initialization

    queueptr priority[]={&queue1,&queue2,&queue3}; // Priority queue array initialization

    inflow(priority,6);


    while(c<49){
        s1=inflow(priority,3);
        if(s1){
        s2=outflow(priority,&c);
        } else {
        printf("The process was stopped due to overflow, printing results so far.\n");
        break;
        }
        if(!s2){
        printf("The process was stopped due to underflow, printing results so far.\n");
        break;
        }
    }
        if(c==49){
            printf("\nSimulation was succesful, 50 elements exit the priority queue.\n");
        }

    printpriority(priority);

    getchar();

}