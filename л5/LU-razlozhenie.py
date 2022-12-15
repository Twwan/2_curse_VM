def show(matrix):
    for i in range(0, len(matrix)):
        for j in range(0, len(matrix[i])):
            print(matrix[i][j], end=' ')
        print()

def main():
    A = [[24.0, 1.0, 1.0, 2.0, 3.0], [3.0, 16.0, 1.0, 2.0, 3.0], [1.0, 3.0, 16.0, 2.0, 1.0],
         [1.0, 1.0, 2.0, 16.0, 3.0], [2.0, 2.0, 3.0, 3.0, 56.0]]

    B = [28.0, 37.0, -4.0, 46.0, -44.0]

    L = []
    U = []
    for i in range(0, 5):
        L.append([0.0]*5)
        U.append([float(0)]*5)
        for j in range(i, 5):
            if i == j:
                L[i][j] = 1.0


    for i in range(0, 5):
        for j in range(0, 5):
            if i >= j:
                summ = 0
                for k in range(1, i-1):
                    summ += float(L[i][k] * U[k][j])
                L[i][j] = float(A[i][j] - summ)
            else:
                summ = 0
                for k in range(1, j-1):
                    summ += L[i][k] * U[k][j]
                U[i][j] = (A[i][j] - summ)/L[i][i]
    y = []
    y = [0 for i in range(5)]
    x = []
    x = [0 for i in range(5)]

    for i in range (0, 5):
        summ = 0
        for k in range(0, i):
            summ += L[i][k]*y[k]
        y[i] = (B[i] - summ)/L[i][i]
    for i in range(4, -1, -1):
        summ = 0
        for k in range(i, 5):
            summ += U[i][k]*x[k]
        x[i] = (y[i]-summ)
    print("Матрица U :")
    show(U)
    print("\n\nМатрица L :")
    show(L)
    print("\n\nСписок значений x :\n")
    for i in range(5):
        print(x[i], end=' ')


if __name__ == '__main__':
    main()