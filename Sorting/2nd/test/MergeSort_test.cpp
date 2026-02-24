#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;
using namespace std::chrono;

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

void testMergeSort()
{
    cout << "2. СОРТИРОВКА СЛИЯНИЕМ (MERGESORT)\n";
    cout << "====================================\n\n";

    int sizes[] = {50000, 100000, 500000, 1000000};
    int runs = 5;

    for (int size : sizes)
    {
        cout << size << " элементов\n";
        cout << "Запуск\tВремя выполнения\n";

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

            mergeSort(testArr, 0, size - 1);

            auto end = high_resolution_clock::now();
            double duration = duration_cast<microseconds>(end - start).count() / 1000000.0;

            cout << run << "\t" << fixed << setprecision(7) << duration << "\n";
            totalTime += duration;
        }

        double average = totalTime / runs;
        cout << "\n\n";
        cout << "Среднее значение: " << fixed << setprecision(7) << average << "\n\n";

        delete[] originalArr;
        delete[] testArr;
    }
}

int main()
{
    testMergeSort();
    return 0;
}