#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;
using namespace std::chrono;

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
            }
        }
        quickSort(a, left, j);
        quickSort(a, i, right);
    }
}

void fillRandom(int A[], int n)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);

    for (int i = 0; i < n; i++)
    {
        A[i] = dist(gen);
    }
}

void copyArray(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

void testQuickSort()
{
    cout << "1. БЫСТРАЯ СОРТИРОВКА (QUICKSORT)\n";
    cout << "===================================\n\n";

    int sizes[] = {50000, 100000, 500000, 1000000};
    int runs = 5;

    for (int size : sizes)
    {
        cout << size << " элементов\n";
        cout << "<table>Запуск\tВремя выполнения\n";

        // Создаем исходный массив
        int *originalArr = new int[size];
        fillRandom(originalArr, size);
        int *testArr = new int[size];

        double totalTime = 0;

        for (int run = 1; run <= runs; run++)
        {
            // Копируем массив
            copyArray(originalArr, testArr, size);

            // Замеряем время
            auto start = high_resolution_clock::now();

            quickSort(testArr, 0, size - 1);

            auto end = high_resolution_clock::now();
            double duration = duration_cast<microseconds>(end - start).count() / 1000000.0;

            cout << run << "\t" << fixed << setprecision(7) << duration << "\n";
            totalTime += duration;
        }

        double average = totalTime / runs;
        cout << "</table>\n\n";
        cout << "Среднее значение: " << fixed << setprecision(7) << average << "\n\n";

        delete[] originalArr;
        delete[] testArr;
    }
}

int main()
{
    testQuickSort();
    return 0;
}