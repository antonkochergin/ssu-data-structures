#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void quickSort(int a[], int left, int right)
{

    if (left < right)
    {
        int p = a[(left + right) / 2];
        int i = left, j = right;
        while (i <= j)
        {
            while (a[i] < p)
            {
                i++;
            }
            while (a[j] > p)
            {
                j--;
            }
            if (i <= j)
            {
                swap(a[i], a[j]);
                i++;
                j--;
                for (int i = left; i <= right; i++)
                {
                }
            }
        }
        quickSort(a, left, j);
        quickSort(a, i, right);
    }
}

int main()
{
    int ex[] = {78, 6, 82, 67, 55, 44, 34};
    int N = sizeof(ex) / sizeof(ex[0]);

    cout << "Исходный массив: ";
    for (int val : ex)
    {
        cout << val << " ";
    }
    cout << endl;

    quickSort(ex, 0, N - 1);

    cout << "Отсортированный массив: ";
    for (int val : ex)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}