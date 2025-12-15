#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//y= w * x---->2 approach ho raha hai through mathematical formula prediction bithayenge
//Training data jugaad
float data[][2]={
    {0,0},
    {1,7},
    {2,14},
    {3,21},
    {4,28}
};

#define DataSize sizeof(data)/sizeof(data[0])

float cost(float w,float bias){
    float sum=0;
    for(int i=0;i<DataSize;i++){
        float actual_y=(float)data[i][1];
        float pred_y=(w*(float)(data[i][0]))+bias;
        float diff=(actual_y-pred_y); 
        sum+=(pow(diff,2));
    }
    return sum;
}


int main(){
    srand(time(0));
    float omega=(float)rand()/(float)RAND_MAX;
    float bias=((float)rand()/(float)RAND_MAX)*5;
    float eps=1e-3;
    float rate=1e-3;
    printf("Random Number - %f\n",omega);
    printf("Random Number - %f\n",bias);
    printf("Cost Integer - %f\n",cost(omega,bias));
    //transitions automate ho...
    for(int i=0;i<4000000;i++){
        float initial_cost=cost(omega,bias);
        float dw=(cost(omega+eps,bias)-initial_cost)/eps;
        float db=(cost(omega,bias+eps)-initial_cost)/eps;
        omega-=(rate*dw);
        bias-=(rate*db);
    }
    printf("Random Number - %f\n",omega);
    printf("Random Number - %f\n",bias);
    printf("Hello World of Coders -2025\n");
    return 0;
}