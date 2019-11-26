#include<stdio.h>
#include<stdlib.h>
#define MAX_TERMS 10000
#define COMPARE(x,y) (((x)>(y))? 1:(((x)==(y)) ? 0 : -1))
typedef struct {
    float coef;
    int expon;
} polynomial;
polynomial terms[MAX_TERMS];

int startA,finishA,startB,finishB,avail,p_start,p_fin;

void readPoly() {
    int i=0,j;
    int cof,exp;
    FILE *fp = fopen("A.txt", "r");
    while (fscanf(fp, "%d %d",&cof, &exp) != EOF){
        if (cof == 0) continue;
        terms[i].coef = cof;
        terms[i].expon = exp;
        i++;
    }
   // printf("i = %d\n\n",i);
   /* fscanf(fp, "%d %d",&cof, &exp);
    terms[i].coef = cof;
    terms[i].expon = exp;*/
    startA = 0;
    finishA = i-1;
    startB = i;
    fclose(fp);
    //B.txt 
    
    fp = fopen("B.txt","r");
    while (fscanf(fp, "%d %d",&cof,&exp) != EOF){
        if (cof == 0) continue;
        terms[i].coef = cof;
        terms[i].expon = exp;
        i++;
    }
    /*fscanf(fp, "%d %d",&cof, &exp);
    terms[i].coef = cof;
    terms[i].expon = exp;*/
    finishB = i-1;
    avail = i;

    fclose(fp);
    int temp,temp2;
    for (int k=finishA; k>=startA; k--){
        for (int j =0; j<=k; j++){
            if(terms[j].expon < terms[j+1].expon){
                temp = terms[j].expon;
                terms[j].expon = terms[j+1].expon;
                terms[j+1].expon = temp;
                temp2 = terms[j].coef;
                terms[j].coef = terms[j+1].coef;
                terms[j+1].coef = temp2;

            }
        }
    }
    for (int k=finishB; k>=startB; k--){
        for (int j =startB; j<=k; j++){
            if(terms[j].expon < terms[j+1].expon){
                temp = terms[j].expon;
                terms[j].expon = terms[j+1].expon;
                terms[j+1].expon = temp;
                temp2 = terms[j].coef;
                terms[j].coef = terms[j+1].coef;
                terms[j+1].coef = temp2;

            }
        }
    }


}




void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS){
        fprintf(stderr, "Too many terms in the polynomial");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void padd() {
    float coefficient;
    p_start = avail;
    while (startA <= finishA && startB <= finishB) {
        switch(COMPARE(terms[startA].expon, terms[startB].expon)){
            case -1 : attach(terms[startB].coef, terms[startB].expon);
                      startB++;
                      break;
            case 0 : coefficient = terms[startA].coef + terms[startB].coef;
                     if (coefficient)
                            attach(coefficient, terms[startA].expon);
                     startA++; startB++;
                     break;
            case 1 : attach(terms[startA].coef, terms[startA].expon);
                     startA++;
                     break;

        }
   }
   for (; startA <= finishA; startA++)
       attach(terms[startA].coef,terms[startA].expon);
   for (; startB <= finishB; startB++)
       attach(terms[startB].coef, terms[startB].expon);
   p_fin = avail-1;
    
}

void printPoly() {
    int i;
    for (i =p_start; i< p_fin; i++){
        printf("(%.0f,%d),", terms[i].coef, terms[i].expon);
    }
    printf("(%.0f,%d)\n", terms[i].coef, terms[i].expon);
}

int main () {
    readPoly();
    padd();
    printPoly();
}
