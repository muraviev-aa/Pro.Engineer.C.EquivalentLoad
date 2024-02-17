// Консольное приложение для определения эквивалентной нагрузки на балку
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void equivalentLoadFromLocalLoad(double localLoad, double beamLength);


int main()
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    double beamLength = 0.0;     // пролет балки
    double localLoad = 0.0;      // значение сосредоточенной силы
    //double equivalentLoad = 0.0; // значение эквивалентной нагрузки
    //double offNodeLoad = 0.0;    // значение внеузловой нагрузки

    puts("Введите длину балки, м:");
    scanf("%Lf", &beamLength);
    fflush(stdin);
    puts("Введите значение сосредоточенной силы, т:");
    scanf("%Lf", &localLoad);
    fflush(stdin);

    equivalentLoadFromLocalLoad(localLoad, beamLength);

    return 0;
}

void equivalentLoadFromLocalLoad(double localLoad, double beamLength)
{
    double equivalentLoad = 2 * localLoad / beamLength;
    double offNodeLoad = 0.5 * (localLoad - equivalentLoad * beamLength);
    printf("Эквивалентная нагрузка: %.2f т\\м\n", equivalentLoad);
    printf("Внеузловая нагрузка: %.2f т\n", offNodeLoad);
}
