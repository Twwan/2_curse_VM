#include <stdio.h>
#include <conio.h>

int main() {
    system("chcp 1251");
    system("cls");

    int n = 5;
    double A[n][n], obrA[n][n], A_1[n][n], E[n][n];

    A[0][0] = 24; A[0][1] = 2; A[0][2] = 2; A[0][3] = 2; A[0][4] = 2;
    A[1][0] = 1; A[1][1] = 24; A[1][2] = 1; A[1][3] = 3; A[1][4] = 2;
    A[2][0] = 2; A[2][1] = 1; A[2][2] = 32; A[2][3] = 1; A[2][4] = 3;
    A[3][0] = 2; A[3][1] = 2; A[3][2] = 2; A[3][3] = 24; A[3][4] = 3;
    A[4][0] = 3; A[4][1] = 1; A[4][2] = 1; A[4][3] = 1; A[4][4] = 24;
    
    printf("Начальная матрица:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.1f ", A[i][j]);
            A_1[i][j] = A[i][j];
        }
        printf("\n");
    }
    
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (i == k && j == k)
                    obrA[i][j] = 1 / A[i][j];
                if (i == k && j != k)
                    obrA[i][j] = -A[i][j] / A[k][k];
                if (i != k && j == k)
                    obrA[i][j] = A[i][k] / A[k][k];
                if (i != k && j != k)
                    obrA[i][j] = A[i][j] - A[k][j] * A[i][k] / A[k][k];
            }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) A[i][j] = obrA[i][j];
    }
    
    printf("\nОбратная матрица: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.1f ", A[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            E[i][j] = 0;
            for (int k = 0; k < n; k++)
                E[i][j] += A[i][k] * A_1[k][j];
        }
    }

    printf("\nЕдиничная матрица:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.1f ", E[i][j]);
        }
        printf("\n");
    }

    return 0;
}