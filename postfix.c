#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>
#define MAX_EXPR_SIZE 1000

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;

/* Global Variables */
/* expression */
char expr[MAX_EXPR_SIZE];
/* isp, icp */
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0};
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

typedef struct _NODE{
    struct _NODE *link;
    precedence data;
}NODE;
/*typedef struct Stack{
  NODE* top;
  }Stack;
  Stack stack;
 */
NODE* top = NULL;
/* Functions already implemented by MDH */
void readExpr(FILE* _fp, char* _expr);
precedence getToken(char*, int*);
void postfix();
void printToken(precedence);
precedence pop();
void push(precedence );
/* Functions to be implemented by student */
int main()
{
    /* Local variables */
    FILE* readfp = fopen("Infix.txt","r");
    top = (NODE*)malloc(sizeof(NODE));
    readExpr(readfp, expr);
    postfix();
    return 0;
}
precedence getToken(char* symbol, int* n){
    *symbol = expr[(*n)++];
    switch(*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod;
        case '\0' : return eos;
        default : return operand;
    }
}
void postfix(){
    char symbol;
    precedence token;
    int n = 0;
    //stack->top = (NODE*)malloc(sizeof(NODE));
    //top->data = eos;
    //top->link = NULL;
    for(token = getToken(&symbol, &n); token != eos; token = getToken(&symbol,&n)){
        if (token == operand)
            printf("%c",symbol);
        else if (token == rparen){
            while (top->data != lparen)
                printToken(pop());
            pop();
        }
        else {
            while(isp[top->data] >= icp[token]) printToken(pop());
            push(token);
        }
    }
    while(top->link != NULL) {
        token=pop();
        printToken(token);
    }
    //while ((token=pop())!= eos) printToken(token);
    printf("\n");
}
void printToken(precedence token){
    char t;
    switch(token){
        case plus : t='+'; break;
        case minus : t='-'; break;
        case divide : t='/'; break;
        case times : t='*'; break;
        case mod : t='%'; break;
                   //        case eos : t='\0';
                   //        default : t = (char)token-'0';
    }
    printf("%c",t);
}

precedence pop(void){
    NODE* new;
    precedence re = top->data;
    if (top == NULL){
       printf("the stack is empty!\n");
        exit(-1);
    }
    else{
        new = top;
        //re = new->data;
        top = top->link;
        free(new);
        return re;
    }
}
void push(precedence item){
    NODE *new = (NODE*)malloc(sizeof(NODE));
    new->data = item;
    new->link = top;
    if(top == NULL)
    {
        top = new;
        return;
    }
    top = new;
}


void readExpr(FILE* _fp, char* _expr)
{

    /* File Existence Check */
    if( !_fp){
        fprintf(stderr, "Input file doesn't exist\n");
        fprintf(stderr, "Program will be shuts down\n");
        exit(0);
    }

    /* Scanning Input */
    fscanf(_fp,"%s",_expr);

    fclose(_fp);
}
