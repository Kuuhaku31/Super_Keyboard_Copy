
#include <stdio.h>
#include <math.h>

const float PI = 3.14;

int inv(int m)
{
    int result = 0;
    for (int i = 0; i < 5; ++i)
    {
        result = result * 10 + m % 10;
        m /= 10;
    }
    return result;
}

int main()
{
    int i_a = 0, i_b = 0, i_c = 0, i_d = 0, i_e = 0, i_f = 0, i_g = 0, io1 = 0, io2 = 0; float f_a = 0, f_b = 0, f_c = 0, f_d = 0, f_e = 0, f_f = 0, f_g = 0, fo1 = 0, fo2 = 0;
//  scanf("%d %d %d %d %d %d %d",&i_a,&i_b,&i_c,&i_d,&i_e,&i_f,&i_g);
    scanf("%f %f %f %f %f %f %f", &f_a, &f_b, &f_c, &f_d, &f_e, &f_f, &f_g);

    fo1 = f_a*f_b+f_c;

    printf("实发工资为%.2f", fo1);
//  printf("%.2f%.2f", o1, o2);

    return 0;
}

