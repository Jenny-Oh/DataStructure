#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_NUM 1000
int failure[MAX_NUM];
// "%[^\n]s"
void fail (char *pat) {
    int i,j, n = strlen(pat);
    failure[0] = -1;
    for (j=1; j<n; j++){
        i = failure[j-1];
        while((pat[j] != pat[i+1])&&(i>=0))
            i = failure[i];
        if(pat[j] == pat[i+1])
            failure[j] = i+1;
        else failure[j] = -1;
    }
}

int pmatch(char *string, char *pat){
    int i=0, j=0;
    int lens = strlen(string);
    int lenp = strlen(pat);
    while(i <lens && j <lenp){
        if(string[i] == pat[j]) { i++; j++; }
        else if (j==0) i++;
        else j = failure[j-1] +1;
    }
    return ((j == lenp ) ? (i-lenp) : -1);
}
void main () {
   int matching_idx;
   char string[MAX_NUM],pat[MAX_NUM];
   FILE *fp = fopen("kmp.txt", "r");
   fscanf(fp,"%[^\n]s",string);
   fscanf(fp,"%s",pat);
   fclose(fp);
   fail(pat);
   matching_idx = pmatch(string,pat);
   printf("%d\n",matching_idx);
}
