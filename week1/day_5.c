#include <stdio.h>

void bubbleSort(int array[], int size);
void printArray(int array[], int size);

int main()
{

    /////////////////////////assinment 1/////////////////////////
    // int size;
    // printf("Enter the size of the array: ");
    // scanf("%d", &size);
    // int array[size];
    // printf("Enter %d elements:\n", size);
    // for (int i = 0; i < size; ++i) {
    //     scanf("%d", &array[i]);
    // }
    // bubbleSort(array, size);
    // printf("Sorted array:\n");
    // printArray(array, size);

    /////////////////////////assinment 2/////////////////////////

    // int values[10];
    // int min, max;
    // for (int i = 0; i < 10; ++i)
    // {
    //     printf("Enter value %d: ", i + 1);
    //     scanf("%d", &values[i]);
    //     if (i == 0 || values[i] < min)
    //         min = values[i];
    //     if (i == 0 || values[i] > max)
    //         max = values[i];
    // }
    // printf("Minimum value: %d\n", min);
    // printf("Maximum value: %d\n", max);

    /////////////////////////assinment 3/////////////////////////
    int x, y, z;
    int *p, *q, *r;

    x = 10;
    y = 20;
    z = 30;

    p = &x;
    q = &y;
    r = &z;

    printf("a) Values:\n");
    printf("x = %d, y = %d, z = %d\n", x, y, z);
    printf("p = %p, q = %p, r = %p\n", (void *)p, (void *)q, (void *)r);
    printf("*p = %d, *q = %d, *r = %d\n", *p, *q, *r);

    printf("\nb) Swapping pointers.\n");

    int *temp = r;
    r = p;
    p = q;
    q = temp;

    printf("\nd) Values after swapping pointers:\n");
    printf("\nx = %d, y = %d, z = %d\n", x, y, z);
    printf("p = %p, q = %p, r = %p\n", (void *)p, (void *)q, (void *)r);
    printf("*p = %d, *q = %d, *r = %d\n\n", *p, *q, *r);

    return 0;
}

void bubbleSort(int array[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
