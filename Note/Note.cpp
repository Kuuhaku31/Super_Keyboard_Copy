﻿
#include <math.h> 
#include <stdio.h>

float bmi(float height, float weight)
{
    return weight/(height*height);
}

int main()
{
    float height, weight, bmiValue;

    scanf("%f %f", &height, &weight);

    bmiValue = bmi(height, weight);

    if(bmiValue<18.5)
    {
        printf("身体质量偏瘦");
    }
    else if(bmiValue<24)
    {
        printf("身体质量正常");
    }
    else if(bmiValue<28)
    {
        printf("身体质量偏胖");
    }
    else
    {
        printf("身体质量肥胖");
    }

    return 0;
}