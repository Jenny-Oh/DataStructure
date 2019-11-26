#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 50

typedef struct _node {
    char data;
    struct _node *leftChild;
    struct _node *rightChild;
}node;

typedef struct Queue {
    //int front, rear;
    int size;
    node* *array;
} queue;

node* newNode(char x){
    node* new = (node*) malloc(sizeof(node));
    new->data = x;
    new->leftChild = new -> rightChild = NULL;
    return new;
}

void Inorder (node* tree) {
   if (tree){
    Inorder(tree->leftChild);
    printf("%c",tree->data);
    Inorder(tree->rightChild);
   }
}

void Preorder (node* tree){
    if(tree){
        printf("%c",tree->data);
        Preorder(tree->leftChild);
        Preorder(tree->rightChild);
    }
}
void Postorder(node* tree){
    if(tree){
        Postorder(tree->leftChild);
        Postorder(tree->rightChild);
        printf("%c",tree->data);
    }
}
void IterativeInorder(node* tree){
    int top =-1;
    node* tmp= tree;
    node* stack[MAX_SIZE];
    for(;;){
        for (;tmp; tmp=tmp-> leftChild)
            stack[++top]=tmp;
        tmp= stack[top--];
        //printf("tmp = %c\n", tmp->data);
        if(!tmp) break;
        printf("%c",tmp->data);
        tmp= tmp->rightChild; 
    }
}
void Levelorder(node* tree){
    int front=0,rear = 0;
    node* queue[MAX_SIZE];
    if (!tree) return;
    queue[rear++]=tree;
    for (;;){
        tree = queue[front++];
        if(tree){
            printf("%c",tree->data);
            if(tree->leftChild)
                queue[rear++]= tree->leftChild;
            if(tree->rightChild)
                queue[rear++]= tree->rightChild;
        }
        else break;
    }
}
int main () {
    int size,i,newflag=0;
    char *arr;
    int front, rear;
    FILE* fp = fopen("Tree.txt", "r");
    fscanf(fp, "%d\n", &size);
    //rear = size-1;
    arr = (char *)malloc(sizeof(char)*size);
    for (i=0; i<size; i++){
        fscanf(fp, "%c\n", &arr[i]);
        //printf("%c\n", arr[i]);
    }
    fclose(fp);
    
    /* make queue */
    queue* Qarr = (queue*) malloc(sizeof(queue));
    //Qarr->front = queue->rear = 0;
    Qarr->size = size;
    Qarr->array = (node**)malloc(sizeof(node*)*size);
    
    /* construct tree */

    //node* new;
    node* new = (node*)malloc(sizeof(node));
    node* root = (node*)malloc(sizeof(node));
    
    // initial node
    root->data=arr[0];
    root->leftChild = NULL;
    root->rightChild = NULL;
    node* temp;
    front = 0;
    rear = 1;
    Qarr->array[front] = root;
    //printf("%c %c \n", root->data,Qarr->array[front]->data);
    
    for (i=1; i <size; i++){
        new = newNode(arr[i]);
        temp= Qarr->array[front];
        //printf("%c %c %c\n",arr[i], new->data,temp->data);
        if (temp->leftChild == NULL)
           temp->leftChild = new;
        else if (temp->rightChild == NULL){
            temp->rightChild= new;
            front++;
        }
        Qarr->array[rear++]=new;
    }

    /* print tree */
    printf("Inorder: ");
    Inorder(root); 
    printf("\nPreorder: ");
    Preorder(root);
    printf("\nPostorder: ");
    Postorder(root);
    printf("\nIterative Inorder: ");
    IterativeInorder(root);
    printf("\nLevel order: ");
    Levelorder(root);
    printf("\n");
}


