#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CLASSES 3
#define CLASS_SIZE 10
#define PASSING_GRADE 50

// Function prototypes
float calculateAverage(int grades[], int size);

int main()
{
    /////////////////////////assinment 1/////////////////////////

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

    /////////////////////////assinment 2/////////////////////////

    int classes[NUM_CLASSES][CLASS_SIZE];
    srand(time(NULL)); // Initialize random seed

    // display student grades
    for (int i = 0; i < NUM_CLASSES; ++i)
    {
        printf("Class %d grades:\n", i + 1);
        for (int j = 0; j < CLASS_SIZE; ++j)
        {
            classes[i][j] = rand() % 101; // Generate random grades between 0 and 100
            printf("Student %d: %d\n", j + 1, classes[i][j]);
        }
    }

    int passed = 0, failed = 0;
    int highestGrade = 0, lowestGrade = 100;
    float totalGrade = 0;

    // Calculate statistics
    for (int i = 0; i < NUM_CLASSES; ++i)
    {
        for (int j = 0; j < CLASS_SIZE; ++j)
        {
            if (classes[i][j] >= PASSING_GRADE)
            {
                passed++;
            }
            else
            {
                failed++;
            }

            if (classes[i][j] > highestGrade)
            {
                highestGrade = classes[i][j];
            }

            if (classes[i][j] < lowestGrade)
            {
                lowestGrade = classes[i][j];
            }

            totalGrade += classes[i][j];
        }
    }

    float averageGrade = totalGrade / (NUM_CLASSES * CLASS_SIZE);

    printf("\nStatistics:\n");
    printf("Number of passed students: %d\n", passed);
    printf("Number of failed students: %d\n", failed);
    printf("Highest grade: %d\n", highestGrade);
    printf("Lowest grade: %d\n", lowestGrade);
    printf("Average grade: %.2f\n", averageGrade);

    /////////////////////////assinment 3/////////////////////////

    return 0;
}

// Function to calculate the average of an array of grades
float calculateAverage(int grades[], int size)
{
    float total = 0;
    for (int i = 0; i < size; ++i)
    {
        total += grades[i];
    }
    return total / size;
}
