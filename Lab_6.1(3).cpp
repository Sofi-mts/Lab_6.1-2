// Лабораторна робота № 6.1 (рекурсивний спосіб)
// Пошук елементів одновимірного масиву
// Варіант 8
// Кучер Софія
// Діапазон значень елементів: (-15, ..., 75)
// Одновимірний масив b із 24 елементів цілого типу.
// Критерій: всі парні, крім додатних  ( b[i] - парний  і  b[i] <= 0 ).
// Обчислити кількість та суму таких елементів і замінити їх нулями.
// Параметр i у всіх функціях - номер поточного елемента
// (перший виклик з i = 0).

#include <time.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

// формування масиву випадковими числами з діапазону [Low, High]
void Create(int* b, const int size, const int Low, const int High, int i) {
    b[i] = Low + rand() % (High - Low + 1);
    if (i < size - 1) Create(b, size, Low, High, i + 1);
}

// виведення масиву в рядок
void Print(int* b, const int size, int i) {
    cout << setw(4) << b[i];
    if (i < size - 1)
        Print(b, size, i + 1);
    else
        cout << endl;
}

// кількість елементів, що задовольняють критерію
int Count(int* b, const int size, int i) {
    if (i < size) {
        if (b[i] % 2 == 0 && b[i] <= 0)
            return 1 + Count(b, size, i + 1);
        else
            return Count(b, size, i + 1);
    } else
        return 0;
}

// сума елементів, що задовольняють критерію
int Sum(int* b, const int size, int i) {
    if (i < size) {
        if (b[i] % 2 == 0 && b[i] <= 0)
            return b[i] + Sum(b, size, i + 1);
        else
            return Sum(b, size, i + 1);
    } else
        return 0;
}

// заміна нулями елементів, що задовольняють критерію
void Replace(int* b, const int size, int i) {
    if (i < size) {
        if (b[i] % 2 == 0 && b[i] <= 0) b[i] = 0;
        Replace(b, size, i + 1);
    }
}

int main() {
    srand((unsigned)time(NULL));  // ініціалізація генератора випадкових чисел

    const int n = 24;
    int b[n];

    int Low = -15;
    int High = 75;

    Create(b, n, Low, High, 0);
    Print(b, n, 0);

    cout << "Count = " << Count(b, n, 0) << endl;
    cout << "Sum   = " << Sum(b, n, 0) << endl;

    Replace(b, n, 0);
    Print(b, n, 0);

    return 0;
}
