#include <vector>
#include <iostream>

using namespace std;

int digit(int num, int d)
{
    for (int i = 1; i < d; i++)
    {
        num /= 10;
    }
    return num % 10;
}

void radixSortLSD(int A[], int N, int m, int P = 10)
{
    // Карзины для чисел
    int **d = new int *[P];
    for (int i = 0; i < P; i++)
    {
        d[i] = new int[N];
    }
    // Счётчик элементов в каждой карзине
    int *ds = new int[P]();

    // Сортировка по каждому разряду от меньшего в большему
    for (int i = 1; i <= m; i++)
    {
        // Очистка карзин
        for (int b = 0; b < P; b++)
        {
            ds[b] = 0;
        }
        // Распределение по карзинам
        for (int j = 0; j < N; j++)
        {
            int di = digit(A[j], i);
            d[di][ds[di]] = A[j];
            ds[di]++;
        }
        // Вытаскиваем из карзин элементы уже в отсортированном виде
        int pos = 0;
        for (int b = 0; b < P; b++)
        {
            for (int j = 0; j < ds[b]; j++)
            {
                A[pos] = d[b][j];
                pos++;
            }
        }
    }
    // Очистка
    for (int i = 0; i < P; i++)
    {
        delete[] d[i];
    }
    delete[] d;
    delete[] ds;
}

int main()
{
    int a[] = {7, 45, 321, 2, 98, 1, 6543, 23, 876, 4};
    int N = sizeof(a) / sizeof(a[0]); // Количество элементов массива

    int mx = 0;
    for (int i = 0; i < N; i++)
    {
        if (a[i] > mx)
            mx = a[i];
    }

    int m = 0; // Максимальное число разрядов числа в массиве
    int tmp = mx;
    while (tmp > 0)
    {
        tmp /= 10;
        m++;
    }
    if (m == 0)
        m = 1; // для числа 0

    radixSortLSD(a, N, m, 10);

    for (size_t i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}