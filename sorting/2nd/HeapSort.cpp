#include <iostream>
using namespace std;

void siftDown(int A[], int i, int N)
{
    while (true)
    {
        int parent = i; // i элемент является максимальным
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // если есть левый ребенок, находим максимум между ним и родителем
        if (left < N && A[left] > A[parent])
        {
            parent = left;
        }

        // если есть правый ребенок, находим максимум между ним и родителем
        if (right < N && A[right] > A[parent])
        {
            parent = right;
        }

        // если максимум - это родитель, прекращаем цикл
        if (parent == i)
        {
            break;
        }

        // иначе меняем местами максимум и родителя
        swap(A[i], A[parent]);
        i = parent; // i = max
    }
}

void heapSort(int A[], int N)
{
    // строим пирамиду (цикл для i = N/2 до 0)
    for (int i = N / 2; i >= 0; i--)
    {
        siftDown(A, i, N);
    }

    // извлекаем элементы из пирамиды (цикл для i = N-1 до 1)
    for (int i = N - 1; i > 0; i--)
    {
        swap(A[0], A[i]);  // меняем местами a[0] и a[i]
        siftDown(A, 0, i); // перестраиваем пирамиду
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int N = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    heapSort(arr, N);

    cout << "Отсортированный массив: ";
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}