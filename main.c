#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float train[][2]={
    {0,0},
    {1,3},
    {2,6},
    {3,9},
    {4,12}
};
#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(){
    //MAX_RAND
    return (float)rand()/(float)RAND_MAX;
}

float cost(float w,float b){
    float res=0.0f;
    for(size_t i=0;i<train_count;i++){
        float x=train[i][0];
        float y=x*w +b;
        float d=y- train[i][1];
        res+=(d*d);
        // printf("actual: %f, expected: %f\n",y,train[i][1]);
    }
    res /=train_count;
    return res;
}
//forward difference
//central difference

int main(){
    srand(time(0));
    float w=rand_float()*10.0f;
    float b=rand_float()*3.0f;
    printf("Initial w: %f Initiail b: %f\n",w,b);
    float eps=1e-3;
    float rate=1e-3;
    for(size_t i=0;i<5000;i++){
    float c=cost(w,b);
    float dw=(cost(w+eps,b)-c)/(eps);
    float db=(cost(w,b+eps)-c)/(eps);
    w -=(rate*dw);
    b-=(rate*db);
    // printf("%f\n",cost(w,b));
    }
    printf("---------------\n");
    printf("Final w: %f Final b: %f\n",w,b);
}