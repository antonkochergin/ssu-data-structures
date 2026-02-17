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
                i++;
            while (a[j] > p)
                j--;
            if (i <= j)
            {
                swap(a[i], a[j]);
                i++;
                j--;
            }
        }
        quickSort(a, left, j);
        quickSort(a, i, right);
    }
}

int main()
{
    int ex[] = {1, 34, 56, 32, 53, 2, 8};
    int N = sizeof(ex) / sizeof(ex[0]);
    quickSort(ex, 0, N - 1);

    cout << "Отсортированный массив: ";
    for (int val : ex)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}