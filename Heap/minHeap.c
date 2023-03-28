//---------------------------------------------------
// AUTHOR: Mariano Arce Jop
// FILENAME: inHeap
// SPECIFICATION: Seventh Lab Fall 2021
// FOR: CS2413 Data Structures
// Time Spent: 8 hours
//---------------------------------------------------

#include<stdio.h>
#include<math.h>
#define S 35

void buildHeap(int array[]);
void minHeapify(int i,int array[]);
void deleteRoot(int array[]);
void insert(int array[], int elem);
void print(int array[]);

void main(){
    int option; // Holds choice
    int heap[S]; // Holds the heap
    int num; // Insert holder


    do{
        printf("\n\n*******************MAIN MENU*******************\n");
        printf("\n 1. Build Heap");
        printf("\n 2. Insert Element");
        printf("\n 3. Delete Root");
        printf("\n 4. Print tree");
        printf("\n 5. Exit");
        printf("\n -- Enter your selection:");

        scanf("%d",&option);
    
        switch(option){
            case 1:
                printf("\n -- Creating Heap.\n");
               
                buildHeap(heap);
        
                break;

            case 2: 
                printf("\nWhat value do you wish to insert?");
                scanf("%d",&num);
                insert(heap,num);
                break;

            case 3:
                printf("\nDeleting Root\n");
                deleteRoot(heap);
                break;

            case 4:
                printf("\nPrinting Heap\n");
                print(heap);
                break;

            default:
                printf("\nUnknown command\n");

        }
    }while(option!=5);

    printf("\n -- Exiting...\n");
}


void minHeapify(int i, int array[]){
// Name: minHeapify
// Purpose: Heapifies with minimum method
// Inputs: Position to check and Heap array
// Outputs: None


    int left = 2*i+1; // Left Child
    int right = 2*i+2; // Right Child
    int mark = 0; // Swap marker
    int size = 0; // Size of heap
    int temp; // Placeholds

    while(array[size]!='\0'){
        size+=1;
    }

    if(array[left]<array[i]&&left<size){
        temp = array[left];
        array[left]=array[i];
        array[i]=temp;
        mark = 1;
    }

    if(array[right]<array[i]&&right<size){
        temp = array[right];
        array[right]=array[i];
        array[i]=temp;
        mark = 2;
    }

    if(mark==1){
        minHeapify(left,array);
    } else if(mark==2){
        minHeapify(right,array);
    }

}

void buildHeap(int array[]){
// Name: buildHeap
// Purpose: Builds a heap with required numbers from an empty array
// Inputs: Heap Array
// Outputs: None


    int i; // Counting variable

    // Clear Array
    for(i=0;i<S;i++){
        array[i]='\0';
    }
    
    int numbers[]={28,12,17,5,7,22,13,12,4,11,16};

    for(i=0; i<11; i++){
        array[i]=numbers[i];
    }
    
    for(i=6;i>=0;i--){
        minHeapify(i,array); 
    }  
}

void deleteRoot(int array[]){
// Name: deleteRoot
// Purpose: Deletes the root of the heap keeping the property
// Inputs: Heap Array
// Outputs: None

    int size = 0; // Holds the size of the array
    int i; // Counter variable

    for(int i=0;i<S-1;i++){
        array[i]=array[i+1];
    }
    array[S-1]='\0';


    while(array[size]!='\0'){
        size++;
    }

    for(i=(size/2-1);i>=0;i--){
        minHeapify(i,array); 
    }
}


void insert(int array[], int elem){
// Name: insert
// Purpose: Inserts an element into the heap keeping the propertiess
// Inputs: Array with heap and element to insert
// Outputs: None

    int size = 0; // Holds the size of the array
    int i = 0; // Counter

    while(array[size]!='\0'){
        size++;
    }
    
    if(size<S){
        array[size]=elem;

        for(i=((size+1)/2-1);i>=0;i--){
            minHeapify(i,array); 
        }
        
    } else {
        printf("Array is full");
    }
}


void print(int array[]){
// Name: print
// Purpose: Prints the heap by rows
// Inputs: Heap Array
// Outputs: None

    int size = 0; // Holds the size of the array
    int row = 0; // Holds current row
    int elem = 0; // Holds elements in row
    int i = 0; // Index

    while(array[size]!='\0'){
        size++;
    }

    while(i<size){
        while(pow(2,row)!=elem){
            if(i==size){
                break;
            }
            printf("%d ",array[i]);
            elem++;
            i++;
        }
        printf("\n");
        row++;
        elem=0;
    }
}
