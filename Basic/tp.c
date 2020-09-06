#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

int main(){
    srand((unsigned)time(NULL));
    float i = (rand()%150)-40+0.75*((float)rand()/RAND_MAX);
    float j= (rand()%100)+0.75*((float)rand()/RAND_MAX);
    int k= (rand()%298)+3;
    float l= (rand()%14)+((float)rand()/RAND_MAX);

    float m= (rand()%100)+0.75*((float)rand()/RAND_MAX);
    int n= rand()%2;
    for(int r=0; r<15; r++){
        //printf("%.2f\t %.3f\t %d\t %.1f\n",i,j,k,l);
        //i =(rand()%150)-40+0.75*((float)rand()/RAND_MAX);
        //j= (rand()%100)+0.75*((float)rand()/RAND_MAX);
        //k= (rand()%298)+3;
        //l= (rand()%14)+0.7*((float)rand()/RAND_MAX);
        if (n==0){
            printf("OFF\n");
        }else{
            printf("ON\n");
        }
        //n= rand()%2;
    }
    return 0;
}
