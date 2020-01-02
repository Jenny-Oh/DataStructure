#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 30
#define MIN2(x,y) ((x)<(y)?(x):(y))
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
short int visited[MAX_VERTICES];
int n,num;
typedef struct adjlist* listptr;
typedef struct adjlist{
    int idx;
    listptr link;
}list;
listptr* header;
void init(){
    int i;
    for (i=0; i<n; i++){
        visited[i] = FALSE;
        dfn[i]=low[i]=-1;
    }
    num = 0;
}
int stack[MAX_VERTICES];
int top=-1;
void push(int u, int v) {
    top++;
    stack[top++] = u;
    stack[top]=v;
    return ;
}
void pop(int* x, int* y) {
    *y = stack[top--];
    *x = stack[top--];
    return ;
}

void bicon(int u,int v){
    listptr ptr;
    int w,x,y;
    dfn[u] = low[u] = num++;
    for (ptr = header[u]; ptr; ptr=ptr->link){
        w = ptr->idx;
        if (v!= w && dfn[w] < dfn[u])
            push(u,w);
        if (dfn[w]<0) {
            bicon(w,u);
            low[u] = MIN2(low[u],low[w]);
            if(low[w] >= dfn[u]){
                printf("New biconnected component: ");
                do {
                    pop(&x, &y);
                    printf(" <%d,%d>",x,y);
                } while (!((x==u)&&(y==w)));
                printf("\n");
            }
        }
        else if (w != v ) low[u] = MIN2(low[u],dfn[w]);
    }
} 


void main () {
    int vtx;
    char ch, hch;

    FILE* fp = fopen("input.txt","r");
    int no,i;
    fscanf(fp,"%d",&no);
    // printf("no = %d \n", no);
    fscanf(fp, "%c",&ch);
    listptr walker;
    header  = (listptr *)malloc(sizeof(listptr)*no); 
    //listptr new = (listptr)malloc(sizeof(struct adjlist));
    for(i=0; i< no; i++){
        header[i]= (listptr)malloc(sizeof(list));
        header[i]->link = NULL;
        header[i]->idx = i;
    }    
    for (i=0; i<no; i++){
        fscanf(fp,"%c",&hch);
        //printf("hch = %c\n",hch);
        if((hch-'0')==i) {
            for(;;) {
                fscanf(fp, "%c", &ch);
                //printf("ch = %c\n", ch);
                //if (ch == (i + '0')) fscanf(fp,"%c",&ch);
                if (ch == '\n') break;
                else {
                    if(ch == ' ') fscanf(fp,"%c",&ch);
                    //printf("ch = %c\n",ch);
                    listptr new = (listptr)malloc(sizeof(list));
                    new->idx =(int)(ch-'0');
                    new->link = NULL;
                    //printf("!!%d\n", new->idx);
                    for (walker = header[i]; walker->link; walker = walker->link);
                    walker->link=new;
                    //printf("walk = %d\n", walker->idx);
                }         
            }
        }
    }
    fclose(fp);
    // print adj lists 
    /*
    for (i=0; i< no; i++){
        printf("head[%d] => ", i);
        for (walker = header[i]; walker; walker = walker-> link)
            printf("%d ", walker->idx);
        printf("\n");
    }
    */
    n = no;
    init();
    bicon(3,-1);

}
