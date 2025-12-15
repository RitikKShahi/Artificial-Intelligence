#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


float sigmoidf(float x){
    return 1.f/(1.f+expf(-x));
}


float or_data [][3]={
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1}
};

#define DataSize sizeof(or_data)/sizeof(or_data[0])

float rand_float(){
    return (float)rand()/(float)RAND_MAX;
}

float cost(float w1,float w2,float bias){
    float sum=0;
    for(int i=0;i<DataSize;i++){
        float actual_y=(or_data[i][2]);
        float pred_y=sigmoidf((w1*(float)or_data[i][0])+(w2*(float)or_data[i][1])+bias);
        float diff=actual_y-pred_y;
        sum+=(pow(diff,2));
    }
    return sum;
}
int main(){
    srand(time(0));
    float w1=rand_float()*10.0f;
    float w2=rand_float()*10.0f;
    float eps=1e-3;
    float rate=1e-3;
    float bias=rand_float()*5.0f;
    printf("%f %f %f\n",w1,w2,bias);
    for(int i=0;i<50000;i++){
        float initial_cost=cost(w1,w2,bias);
        float dw1=(cost(w1+eps,w2,bias)-initial_cost)/eps;
        float dw2=(cost(w1,w2+eps,bias)-initial_cost)/eps;
        float db=(cost(w1,w2,bias+eps)-initial_cost)/eps;
        w1-=(rate*dw1);
        w2-=(rate*dw2);
        bias-=(rate*db);
    }
    printf("%f %f %f\n",w1,w2,bias);
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d %d = %f\n",i,j,sigmoidf((w1*i)+(w2*j)+bias));
        }
    }
}