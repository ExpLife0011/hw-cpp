#include <iostream>

#include "arraysort.h"
#include "quicksort.h"
#include "bubblesort.h"

#include "bubblesortTest.h"
#include "quicksortTest.h"

using namespace std;

int main()
{
    BubbleSortTest t1;
    QuickSortTest t2;
    QTest::qExec(&t1);
    QTest::qExec(&t2);

    int a[10];
    cout << "Input 10 elemnts:" << endl;
    for (int i = 0; i < 10; i++)
        cin >> a[i];

    ArraySort *sort = new QuickSort();

    sort->sort(a, 10);

    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";

    return 0;
}

