#include <stdio.h>
#include <stdlib.h>

#define N 10
#define a -5.0
#define b 5.0

const double h = (b - a) / N;

double func(double x)
{
    double y;
    y = 1 / (x * x + 1);

    return y;
}

double avg_dev(double f1, double f2, int s)
{
    s = (double) s;
    return ((f2 - f1) / (s * h));
}

int main()
{
    int i, j;
    double f = 0.0, Xn = 0.0, x = 0.0;
    double *avg_devi;
    double stemp = 0, temp = 0;

    printf("Please enter the x: ");
    scanf("%lf", &x);

    avg_devi = (double *) malloc((N + 1) * sizeof(double));

    for (i = 0; i <= N; i++)
    {
        for (j = i; j <= N; j++)
        {
            if (i == 0)
            {
                Xn = a + j * h;
                avg_devi[j] = func(Xn);
            }
            else
            {
                if (j == i)
                {
                    stemp = avg_devi[j - 1];
                }
                temp = avg_dev(stemp, avg_devi[j], i);
                //save the avg_devi[j] before it is overlapped.
                stemp = avg_devi[j];
                avg_devi[j] = temp;
            }
        }
    }
    printf("The averages of the deviation:\n");
    for (i = 0; i <= N; i++)
    {
        printf("a%d: %lf\n", i, avg_devi[i]);
    }
    //clear the variable Xn
    Xn = 1.0;
    for (i = 0; i <= N; i++)
    {
        if (i != 0)
            Xn *= (x - (a + (i - 1) * h));
        f += avg_devi[i] * Xn;
    }

    printf("The approximate value is: %lf\n", f);
    printf("The real value is: %lf\n", func(x));
    free(avg_devi);
    return 0;
}
