#include<stdio.h>
#include<malloc.h>
#include<time.h>

void printsorted(int * list, int no){
    FILE *fp =fopen( "output.txt", "w");
    for(int i =0; i<no; i++)
        fprintf(fp, "%d\n", list[i]);
} 

void main () {
    int i=0, num;
    double start, stop, t_time;
    start = clock();
    FILE* fp = fopen("input.txt","r");
    fscanf(fp, "%d", &num);
      
    int* list = (int*)malloc(sizeof(int) * (num+1));
    for (i=0; i< num; i++)
        fscanf(fp, "%d", &list[i]);
    fclose(fp);
    int target, tar_idx,j;
    for (i=0; i< num; i++){
        target = list[i];
        for (j=i-1; j>=0 && list[j]>target; j--)
            list[j+1]= list[j];
        list[j+1] = target;
    }
    printsorted(list, num);
    stop= clock();
    t_time = ((double)(stop-start))/CLOCKS_PER_SEC;
    printf("Elapsed time (sec): %.3lf sec\n",t_time);
}
