#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;
using namespace std::chrono;

void siftDown(vector<int> &A, int i, int N)
{
    while (true)
    {
        int parent = i;        // полагаем, что i-тый элемент является максимальным
        int left = 2 * i + 1;  // левый ребенок
        int right = 2 * i + 2; // правый ребенок

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

void heapSort(vector<int> &A, int N)
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

void fillRandom(vector<int> &A, int n)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);

    A.resize(n);
    for (int i = 0; i < n; i++)
    {
        A[i] = dist(gen);
    }
}

void copyArray(const vector<int> &src, vector<int> &dest)
{
    dest = src;
}

void testHeapSort()
{
    cout << "3. ПИРАМИДАЛЬНАЯ СОРТИРОВКА (HEAPSORT)\n";
    cout << "========================================\n\n";

    int sizes[] = {50000, 100000, 500000, 1000000};
    int runs = 5;

    for (int size : sizes)
    {
        cout << size << " элементов\n";
        cout << "Запуск\tВремя выполнения\n";

        // Создаем исходный массив
        vector<int> originalArr;
        fillRandom(originalArr, size);

        double totalTime = 0;

        for (int run = 1; run <= runs; run++)
        {
            // Копируем массив
            vector<int> testArr;
            copyArray(originalArr, testArr);

            // Замеряем время
            auto start = high_resolution_clock::now();

            heapSort(testArr, size);

            auto end = high_resolution_clock::now();
            double duration = duration_cast<microseconds>(end - start).count() / 1000000.0;

            cout << run << "\t" << fixed << setprecision(7) << duration << "\n";
            totalTime += duration;
        }

        double average = totalTime / runs;
        cout << "\n\n";
        cout << "Среднее значение: " << fixed << setprecision(7) << average << "\n\n";
    }
}

int main()
{
    testHeapSort();
    return 0;
}