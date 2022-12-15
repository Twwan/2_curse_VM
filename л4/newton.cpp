#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main() {
    system("chcp 1251");
    double f[1000];
    int i, k=0;
    double p=0, sx=0;//Pn(x), sin(x)
    double xp=0, a=0, b=0;//целевая точка 
    double x[1000];
    int n=0 ;
    double h=0;
    printf("Введите a");
    scanf("%lf", &a);
    printf("Введите b");
    scanf("%lf", &b);
    printf("Введите n");
    scanf("%d", &n);
    printf("Введите x");
    scanf("%lf", &xp);
    h=(b-a)/(int)n;
    for (i = 0; i<n; i++) { 
        x[i]= a + h * i;
    }
    for (i = 0; i<n; i++) {
        f[i]= sin(x[i]);
    }
    for (k = 1; k<n; k++) {
        for (i = 0;i< n - k; i++) {
            f[i]= (f[i + 1] - f[i]) / (x[i + k] - x[i]);
        }
    }
    p= f[0];
    for (i = 1;i<n; i++) {
        p= p * (xp - x[i]) + f[i];
    }
    printf("  P( %f ) = %f",xp, p);
    sx = sin(xp);
    printf("f(x)( %f ) = %f",xp, sx);

}