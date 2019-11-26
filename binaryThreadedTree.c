#include<stdio.h>
#include<stdlib.h>
/* threaded tree : child O == thread : 0 / child X == thread : X */
typedef struct threadedTree* threadedPointer;

typedef struct threadedTree{
    short int leftThread;
    threadedPointer leftChild;
    int data;
    threadedPointer rightChild;
    short int rightThread;
}Tree;

threadedPointer NewTree (int x) {
    threadedPointer temp = (threadedPointer)malloc(sizeof(Tree));
    temp->data = x;
    //temp->leftThread = temp->rightThread = 
    return temp;
}
threadedPointer insucc(threadedPointer tree){
    threadedPointer temp;
    temp = tree->rightChild;
    //printf("Insucc!\n");
    //if (temp == NULL) printf("NULL\n");
    //printf("temp->data = %d \n", temp->data);
    if(!tree->rightThread)
        while(!temp->leftThread) temp = temp->leftChild;
    return temp;
}

void Insertion (threadedPointer root,threadedPointer new, int pdata,int cdata ,char type){
   
   threadedPointer temp = root;
   threadedPointer parent,child;
   //child = NewTree();
   //child = (threadedPointer)malloc(sizeof(Tree));
   //child->data = cdata;
   child = new;
   //printf("root = %d \n", root->leftChild->data);
   //if (new == NULL) printf("NULL\n");
   //printf("new = %d \n",new->data);
   //printf("pdata = %d\n", pdata);
   /* finding parent node */
   for (;;) {
        temp = insucc(temp);
        //printf("temp->Data = %d\n",temp->data);
        if (temp->data == pdata) break;
        //break;
        //printf("finding parent (%d)\n", temp->data);
   } 
   parent = temp;
   if (type == 'R'){ /* Insert right Child */
        child->rightChild = parent->rightChild;
        child->rightThread = parent->rightThread;
        child->leftChild = parent;
        child->leftThread = 1;
        parent->rightChild = child;
        parent->rightThread = 0;
        if (!child->rightThread){
            temp = insucc(child);
            temp->leftChild = child;
        }
   }
   else {
        child->leftChild = parent->leftChild;
        child->leftThread = parent->leftThread;
        child->rightChild = parent;
        child->rightThread = 1;
        parent->leftChild = child;
        parent->leftThread = 0;
        if (!child->leftThread){
            temp = insucc(child);
            temp->rightChild = child;
        }
   }
   //free(new);
}

void Traversal (threadedPointer tree){
    
    threadedPointer temp=tree;
   
    for (;;){
        temp = insucc(temp);
        if(temp == tree) break;
        printf("%d\n", temp->data);
        //if(temp->rightChild->data == 0) break;
    }
}

int main () {
    char type, trash;
    int pnum, cnum;
    threadedPointer new,temp;
    threadedPointer root = (threadedPointer)malloc(sizeof(Tree));
    root->data = 0;
    root->leftThread = 0;
    root->rightThread = 0;
    root->rightChild = root;
    //printf("fllfllfl\n");
    FILE* fp = fopen("Tree.txt", "r");
    while(1){
        
        fscanf(fp, "%c", &type);
        //printf("%c\t" , type);
        if (type == 'E') break;
        else if (type == 'S'){
            fscanf(fp, " %c %d\n",&trash, &pnum);
            //printf("num = %d\n",pnum);
            new = (threadedPointer)malloc(sizeof(Tree));
            new->data = pnum;
            root->leftChild = new;
            root->leftThread = 0;
            new->leftThread = 1;
            new->rightThread = 1;
            new->leftChild = root;
            new->rightChild = root;
            //new->rightChild = new;
            //new->leftChild = root;
            //printf("%d", root->data);
            //free(new);
        }
        else if (type == 'R' || type == 'L'){
            fscanf(fp," %d %d\n", &pnum, &cnum);
            //printf("p = %d  c = %d\n", pnum,cnum);
            //printf("rrrr= %d \n", root->data);
            temp = NewTree(cnum);
            //new= (threadedPointer)malloc(sizeof(Tree));
            //if (temp == NULL) printf("temp is NULL\n");
            //new->data = cnum;
            //printf("rrrr= %d \n", root->data);
            //new->rightThread = 0;
            //new->leftThread = 0;
            //printf("dklfjksldf\n");
            //printf("%d \n", root->leftChild->data);
            Insertion(root,temp,pnum,cnum,type);
        }
        //free(new);
    }
    Traversal(root);

    return 0;
}



