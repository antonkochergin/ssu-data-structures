#include <iostream>
using namespace std;

void merge(int A[], int l, int r, int m)
{
    // Проверка граничных условий
    if (l >= r || m < l || m > r)
    {
        return;
    }

    // Если в массиве 2 элемента и они не отсортированы
    if (r - l == 1 && A[l] > A[r])
    {
        swap(A[l], A[r]);
        return;
    }

    // Создаем дополнительный массив buf размерностью r - l + 1
    int size = r - l + 1;
    int *buf = new int[size];
    int cur = 0;
    int i = l;
    int j = m + 1;

    // Цикл пока не заполним весь buf
    while (cur < size)
    {
        if (i > m)
        {
            // Дописываем оставшиеся элементы от j до r
            for (int k = j; k <= r; ++k)
            {
                buf[cur++] = A[k];
            }
            break;
        }
        else if (j > r)
        {
            // Дописываем оставшиеся элементы от i до m
            for (int k = i; k <= m; ++k)
            {
                buf[cur++] = A[k];
            }
            break;
        }
        else if (A[i] > A[j])
        {
            buf[cur++] = A[j];
            ++j;
        }
        else
        {
            buf[cur++] = A[i];
            ++i;
        }
    }

    // Записываем массив buf в начальный массив A, начиная с индекса l
    for (int k = 0; k < size; ++k)
    {
        A[l + k] = buf[k];
    }

    delete[] buf;
}

void mergeSort(int A[], int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int m = (r + l) / 2;

    mergeSort(A, l, m);
    mergeSort(A, m + 1, r);
    merge(A, l, r, m);
}

int main()
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    mergeSort(arr, 0, size - 1);

    cout << "Отсортированный массив: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}