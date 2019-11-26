#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE true
#define FALSE false

#define M 103
#define P 103
#define MAX_DIRECTION_SIZE 8
#define MAX_STACK_SIZE M * P

#define _MDH_DEBUG_

/* Structure definition  */
typedef struct{
	short int row;
	short int col;
	short int dir;
}element;

typedef struct{
	short int vert;
	short int horiz;
}offsets;

/* Maze-Related Variables Region */
// maze is variable for representing maze itself by using 0 or 1.
// 0 value means available path. On the otherhand, 1 value means wall so we cannot go this way.
char maze[M][P];
// mark is variable for presenting that you've already visited.
// 0 value means that you haven't been there and 1 value means that you have already visited.
char mark[M][P];
offsets move[MAX_DIRECTION_SIZE]={{-1,0}, {-1,1}, {0,1}, {1,1},
	{1,0}, {1,-1}, {0,-1}, {-1,-1}};
// Coordinate (Row and Column of maze) of EXIT respectively.
int EXIT_ROW, EXIT_COL;

/* Stack-Related Variables Region */
element stack[MAX_STACK_SIZE];
int top=-1;

/* Functions to be implemented by student */
element Pop();
void Push(element item);
void Path();
void PrintExitPath();

/* Functions already implemented by MDH */
void PrintMaze();
void ReadMaze();

/* main Function */
int main()
{
	ReadMaze();
	PrintMaze();

	Path();

    return 0;
}
void Push(element item) {
    if (top >= MAX_STACK_SIZE-1)
       printf("stack is full!\n");
    stack[++top] = item;
    //printf("push  row = %d col = %d dir = %d\n", item.row, item.col, item.dir);
}
element Pop() {
    if(top == -1)
        printf("stack is empty!!\n");
    //printf("pop  row = %d col = %d dir = %d\n", stack[top].row, stack[top].col, stack[top].dir);
    return stack[top--];
}

void Path(){
    element new;
    int visited = 0;
    short int cd=0,dir;
    int i,j;
    short int h,v,cr=1,cc=1;
    while (cr != EXIT_ROW && cc !=  EXIT_COL){
        //printf("cr = %d cc = %d \n", cr,cc);
        cd = 0;
        mark[cr][cc] = '1';
        visited = 0;
        for (dir=cd; dir<8; dir++){
            //printf("cd = %d\n", dir);
            h = move[dir].vert;
            v = move[dir].horiz;
            if (maze[h+cr][v+cc] == '0'&& mark[h+cr][v+cc] != '1'){
                //printf("mark!\n");
                new.row= h+cr;
                new.col=v+cc;
                new.dir =dir;
                Push(new);
               // printf("row = %d col = %d dir = %d\n", new.row, new.col, new.dir);
                visited = 1;
                cd = 0;
                break;
            }
            /*if (visited == 1) {
                cd = 0;
                break;
            }*/
        }
        // retracing
        int cnt =0;
        if (visited == 0){
            for (dir=0; dir<8; dir++){
                h = move[dir].vert;
                v = move[dir].horiz;
                if (maze[h+stack[top].row][v+stack[top].col] == '1' || mark[h+stack[top].row][v+stack[top].col] == '1') cnt++;
            }
            if (cnt == 8) new = Pop();
            else new = stack[top];
        }
        cr = new.row;
        cc = new.col;
        cd = new.dir;
    }
   /* if (i == 7) {
        printf("-1\n");
        return 0;
    } */
    PrintExitPath();
}
void PrintExitPath(){
   int i;
   printf("1\t1\n");
   for (i=0; i<=top; i++){
        printf("%d\t%d\n", stack[i].row, stack[i].col);
   }
}

void ReadMaze()
{
	FILE* _read_fp = fopen("maze.txt","r");
	char _buf[M];
	int i;

	/* File Pointer Validation Check */
	if( !_read_fp ){
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be Shutdown\n");
		exit(0);
	}
	
	/* Scanning Input */
	fscanf(_read_fp, "%d %d", &EXIT_ROW, &EXIT_COL);
	for( i=1 ; i<= EXIT_ROW ;i++){
		fscanf(_read_fp, "%s",&maze[i][1]);
	}
	
	/* Enveloping maze in '1' which indicates artificial wall */
	for( i=0 ; i<=EXIT_COL + 1 ; i++){
		maze[0][i]='1';
		maze[EXIT_ROW+1][i]='1';
	}
	for( i=0 ; i<=EXIT_ROW + 1 ; i++){
		maze[i][0]='1';
		maze[i][EXIT_COL+1]='1';
	}
	fclose(_read_fp);

}
void PrintMaze()
{
	int i, j;
#ifdef _MDH_DEBUG_
	printf("Input Checking\n");
	printf("%d %d\n",EXIT_ROW, EXIT_COL);
#endif
	for( i=0 ; i <= EXIT_ROW+1 ; i++)
	{
		printf("%s\n",maze[i]);
	}
}
