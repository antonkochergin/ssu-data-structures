#include <iostream>

using namespace std;

void countingSort(int a[], int N, int k)
{
    // Создаем вспомогательный массив для учета количества элементов
    int *b = new int[k]();
    // Считаем сколько каких элементов в массиве
    for (int i = 0; i < N; i++)
    {
        b[a[i]]++;
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < b[i]; j++)
        {
            cout << i << " ";
        }
    }

    delete[] b; // освобождаем память
}

int main()
{
    int a[] = {4, 2, 2, 8, 3, 3, 1, 4, 2, 7};
    int n = sizeof(a) / sizeof(a[0]);

    int mx = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > mx)
            mx = a[i];
    }
    int k = mx + 1;

    cout << "Отсортированный массив: ";
    countingSort(a, n, k);
    cout << endl;

    return 0;
}