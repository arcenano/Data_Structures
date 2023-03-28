//---------------------------------------------------
// AUTHOR: Mariano Arce Jop
// FILENAME: tree 
// SPECIFICATION: Fifth Lab Fall 2021
// FOR: CS2413 Data Structures
// Time Spent: 8 hours
//---------------------------------------------------

#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<time.h>
#include<stdlib.h>

struct node {
    int data; // Holds integer value
    struct node *left; // Points to left child
    struct node *right; // Points to right child
};

struct node *tree;
void create_tree(struct node *);
struct node *insertElement(struct node *,int);
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
struct node *deleteTree(struct node *);
struct node *deleteNode(struct node *, int);
int height(struct node*);
void print_tree(struct node*,int);

int main(){
    srand(time(0));
    int option,val; // Hold user selection and integer values

    create_tree(tree);

    do{
        printf("\n\n*******************MAIN MENU*******************\n");
        printf("\n 1. Create tree");
        printf("\n 2. Preorder traversal");
        printf("\n 3. Inorder traversal");
        printf("\n 4. Postorder traversal");
        printf("\n 5. Delete an element");
        printf("\n 6. Print tree");
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
                    
                for(int i=0;i<12;i++){
                    val = 100 + rand() % 899;
                    tree = insertElement(tree,val); 
                }
    
                break;

            case 2: 
                if(tree==NULL){
                    printf("\n -- The tree is empty\n");
                    break;
                }
                printf(" -- Traversing in preorder.\n");
                printf("\n -- The elements of the tree are: \n");
                preorder(tree);
                break;

            case 3:
                if(tree==NULL){
                    printf("\n -- The tree is empty\n");
                    break;
                }
                printf(" -- Traversing Inorder.\n");
                printf("\n -- The elements of the tree are: \n");
                inorder(tree);
                break;

            case 4:
                if(tree==NULL){
                    printf("\n The tree is empty\n");
                    break;
                }
                printf(" -- Traversing in postorder.\n");
                printf("\n -- The elements of the tree are: \n");
                postorder(tree);
                break;

            case 5:
                printf("\n -- Enter the element to be deleted:");
                scanf("%d",&val);
                if(tree==NULL){
                    printf("\n -- The tree is Empty.\n");
                } else {
                    tree = deleteNode(tree,val);
                }
                break;
            case 6:
                printf("\n Printing Tree\n");
                print_tree(tree,0);
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

struct node *insertElement(struct node *tree, int val){
// Name: insertElement
// Purpose: Insert an element into the BST
// Inputs: Pointer to the root of the tree, int to be entered 
// Outputs: Pointer to the root of the tree

    struct node *ptr, *nodeptr, *parentptr; // Pointers used to keep track of parents and new node
    ptr = (struct node*)malloc(sizeof(struct node));

    ptr -> data = val;
    ptr -> left = NULL;
    ptr -> right = NULL;

    if (tree==NULL){
        tree = ptr;
        tree -> left = NULL;
        tree -> right = NULL;
    } else {
        parentptr=NULL;
        nodeptr=tree;

        while(nodeptr != NULL){
    
            parentptr=nodeptr;

            if(val<nodeptr->data)
                nodeptr=nodeptr->left;
            else
                nodeptr=nodeptr->right;
        }
        if(val<parentptr->data)
            parentptr->left = ptr;
        else    
            parentptr->right=ptr;
    }
    return tree;
}

void preorder(struct node *tree){
// Name: preorder
// Purpose: Prints the tree in preorder
// Inputs: Pointer to the root of the tree
// Outputs: None

    if(tree != NULL){
        printf("%d\t",tree->data);
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
        printf("%d\t",tree->data);
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
        printf("%d\t",tree->data);
    }
}

struct node* minValueNode(struct node* node){
// Name: minValueNode
// Purpose: Finds the leftmost leaf
// Inputs: Pointer to a node in the tree
// Outputs: Tree root

    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

struct node* deleteNode(struct node* root, int val){
// Name: deleteNode
// Purpose: Deletes a given value from the BST
// Inputs: Pointer to the root of the tree, value to delete
// Outputs: Pointer to the root of the tree
// Function from the web

    // base case
    if (root == NULL){
        printf("\n -- Element is not in tree. \n");
        return root;
    }
 
    // If the key to be deleted 
    // is smaller than the root's
    // key, then it lies in left subtree
    if (val < root->data)
        root->left = deleteNode(root->left, val);
 
    // If the key to be deleted 
    // is greater than the root's
    // key, then it lies in right subtree
    else if (val > root->data)
        root->right = deleteNode(root->right, val);
 
    // if key is same as root's key, 
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            printf("\n -- Element Deleted. \n");
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            printf("\n -- Element Deleted. \n");
            return temp;
        }
 
        // node with two children: 
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minValueNode(root->right);
 
        // Copy the inorder 
        // successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return(root);
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

int height(struct node *tree){
    int leftheight, rightheight;
    if(tree==NULL){
        return(0);
    } else {
        leftheight=height(tree->left);
        rightheight=height(tree->right);
        if(leftheight>rightheight){
            return(leftheight+1);
        } else {
            return(rightheight+1);
        }
    }
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
		printf("%d\n", tree->data);
		
		print_tree(tree->left, level+2);
	}
}