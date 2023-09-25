#include <stdio.h>

int getMaximum(int a, int b, int c, int d)
{
    int max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    if (d > max)
        max = d;
    return max;
}

int getMinimum(int a, int b, int c, int d)
{
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    if (d < min)
        min = d;
    return min;
}

int calculate(int operation, int a, int b)
{
    switch (operation)
    {
    case 1:
        return a + b;
    case 2:
        return a - b;
    case 3:
        return a * b;
    case 4:
        return b != 0 ? a / b : 0;
    case 5:
        return a || b;
    case 6:
        return a && b;
    case 7:
        return !a;
    case 8:
        return (a || b) && !(a && b);
    case 9:
        return a % b;
    case 10:
        return a + 1;
    case 11:
        return a - 1;
    default:
        return 0;
    }
}
int main()
{

    /////////////////////////assinment 1/////////////////////////

    // int num1, num2, num3, num4;

    // printf("Enter four numbers: ");
    // scanf("%d %d %d %d", &num1, &num2, &num3, &num4);

    // int max = getMaximum(num1, num2, num3, num4);
    // int min = getMinimum(num1, num2, num3, num4);

    // printf("Maximum: %d\n", max);
    // printf("Minimum: %d\n", min);
    /////////////////////////assinment 2/////////////////////////

    // int operationId;
    // printf("Enter operation ID: ");
    // scanf("%d", &operationId);

    // int operand1, operand2;
    // int operand;

    // switch (operationId)
    // {
    // case 1 ... 6:
    // case 8:
    // case 9:
    //     printf("Enter two operands: ");
    //     scanf("%d %d", &operand1, &operand2);
    //     printf("Result: %d\n", calculate(operationId, operand1, operand2));
    //     break;
    // case 7:
    // case 10:
    // case 11:
    //     printf("Enter an operand: ");
    //     scanf("%d", &operand);
    //     printf("Result: %d\n", calculate(operationId, operand, 0));
    //     break;

    // default:
    //     printf("Invalid operation ID\n");
    // }

    return 0;
}