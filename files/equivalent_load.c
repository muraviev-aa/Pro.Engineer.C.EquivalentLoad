// Консольное приложение для определения эквивалентной нагрузки на балку
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

double equivalentLoad = 0.0;        // значение эквивалентной нагрузки
double offNodeLoadEqual = 0.0;      // значение внеузловой нагрузки равной по значению слева и справа
double offNodeLoadA = 0.0;          // значение внеузловой нагрузки у левой опоры балки
double offNodeLoadB = 0.0;          // значение внеузловой нагрузки у правой опоры балки
double beamLength = 0.0;            // пролет балки
double localLoad = 0.0;             // значение сосредоточенной силы
double triangularDistributed = 0.0; // значение треугольной распределенной нагрузки
double sizeLengthA = 0.0;           // привязка внешнего воздействия к левой опоре
double sizeLengthB = 0.0;           // привязка внешнего воздействия к правой опоре

int menu(void);                              // меню программы
void equivalentLoadFromLocalLoad(void);      // эквивалентная от сосредоточенной силы в середине пролета
void equivalentLoadFromFreeLocalLoad(void);  // эквивалентная от сосредоточенной силы в произвольном месте балки
void equivalentLoadFromSimTwoLocalLoad(void);// эквивалентная от двух симметричных сосредоточенных нагрузки
void equivalentLoadFromTriangularLoad(void); // эквивалентная от треугольной нагрузки по всей длине балки
void help(void);                             // справка по работе с программой

int main()
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);

    int choice = 0;

    while(1)
    {
        choice = menu();
        switch(choice)
        {
            case 'S':
            equivalentLoadFromLocalLoad();
            break;
        case 'A':
            equivalentLoadFromFreeLocalLoad();
            break;
        case 'D':
            equivalentLoadFromSimTwoLocalLoad();
            break;
        case 'I':
            equivalentLoadFromTriangularLoad();
            break;
        case 'H':
            help();
            break;
        case 'Q':
            puts("Всего доброго!");
            exit(EXIT_SUCCESS);
            break;
        default:
            puts("Некорректный ввод. Введите букву английского алфавита.");
            break;
        }

    }
    system("pause");
    return 0;
}

// меню программы
int menu(void)
{
    int ch = 0;
    puts("Меню:");
    printf("S - сосредоточенная сила в середине пролета, \
\nA - сосредоточенная сила в произвольном месте балки, \
\nD - две равные по значению симметрично расположенные сосредоточенные силы, \
\nI - треугольная нагрузка по всей длине балки,\nH - справка,\nQ - выход;\n");

    ch = getch(); // ожидает нажатия клавиши, после которого она немедленно возвращает значение

    putchar(ch); // вывод символа в стандартный поток вывода
    putch('\n'); // функция производит вывод прямо на экран
    ch = toupper(ch); // преобразование строчных букв в прописные
    // после выбора действия в меню сперва очищается экран
     if(ch == 'S' || ch == 'A'|| ch == 'D'|| ch == 'I'|| ch == 'H'|| ch == 'Q'||
        ch != 'S'|| ch != 'A'|| ch != 'D'|| ch != 'I'|| ch != 'H' || ch != 'Q')
    {
        system("cls");
    }
    return ch;
}

// эквивалентная от сосредоточенной силы в середине пролета
void equivalentLoadFromLocalLoad()
{
    puts("Введите длину балки, м:");
    scanf("%Lf", &beamLength);
    fflush(stdin);
    puts("Введите значение сосредоточенной силы, т:");
    scanf("%Lf", &localLoad);
    fflush(stdin);
    equivalentLoad = 2 * localLoad / beamLength;
    offNodeLoadEqual = 0.5 * (localLoad - equivalentLoad * beamLength);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Исходные данные:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Длина балки = %.2f м\n", beamLength);
    printf("Значение сосредоточенной силы = %.2f т\n", localLoad);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Результат вычисления:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Эквивалентная нагрузка q = %.2f т/м\n", equivalentLoad);
    printf("Внеузловая нагрузка F1 = F2 = %.2f т\n", offNodeLoadEqual);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

// эквивалентная от сосредоточенной силы в произвольном месте балки
void equivalentLoadFromFreeLocalLoad()
{
    puts("Введите длину балки, м:");
    scanf("%Lf", &beamLength);
    fflush(stdin);
    puts("Введите значение размера привязки сосредоточенной силы к левой опоре балки, м");
    scanf("%Lf", &sizeLengthA);
    fflush(stdin);
    puts("Введите значение сосредоточенной силы, т:");
    scanf("%Lf", &localLoad);
    fflush(stdin);
    sizeLengthB = beamLength - sizeLengthA;
    equivalentLoad = 8 * localLoad * sizeLengthA * sizeLengthB / pow(beamLength, 3);
    offNodeLoadA = localLoad * sizeLengthB / beamLength - 0.5 * equivalentLoad * beamLength;
    offNodeLoadB = localLoad * sizeLengthA / beamLength - 0.5 * equivalentLoad * beamLength;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Исходные данные:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Длина балки = %.2f м\n", beamLength);
    printf("Размер привязки сосредоточенной силы к левой опоре балки = %.2f м\n", sizeLengthA);
    printf("Значение сосредоточенной силы = %.2f т\n", localLoad);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Результат вычисления:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Эквивалентная нагрузка q = %.2f т/м\n", equivalentLoad);
    printf("Внеузловая нагрузка F1 = %.2f т\n", offNodeLoadA);
    printf("Внеузловая нагрузка F2 = %.2f т\n", offNodeLoadB);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

// эквивалентная от двух симметричных сосредоточенных нагрузки
void equivalentLoadFromSimTwoLocalLoad()
{
    puts("Введите длину балки, м:");
    scanf("%Lf", &beamLength);
    fflush(stdin);
    puts("Введите значение размера привязки левой сосредоточенной силы к левой опоре балки, м");
    scanf("%Lf", &sizeLengthA);
    fflush(stdin);
    puts("Введите значение одной сосредоточенной силы, т:");
    scanf("%Lf", &localLoad);
    fflush(stdin);
    equivalentLoad = 8 * localLoad * sizeLengthA / pow(beamLength, 2);
    offNodeLoadEqual = localLoad - 0.5 * equivalentLoad * beamLength;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Исходные данные:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Длина балки = %.2f м\n", beamLength);
    printf("Размер привязки левой сосредоточенной силы к левой опоре балки = %.2f м\n", sizeLengthA);
    printf("Значение сосредоточенной силы = %.2f т\n", localLoad);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Результат вычисления:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Эквивалентная нагрузка q = %.2f т/м\n", equivalentLoad);
    printf("Внеузловая нагрузка F1 = F2 = %.2f т\n", offNodeLoadEqual);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

// эквивалентная от треугольной нагрузки по всей длине балки
void equivalentLoadFromTriangularLoad()
{
    puts("Введите длину балки, м:");
    scanf("%Lf", &beamLength);
    fflush(stdin);
    puts("Введите значение треугольной нагрузки по всей балке, т/м:");
    scanf("%Lf", &triangularDistributed);
    fflush(stdin);
    equivalentLoad = 0.512 * triangularDistributed;
    offNodeLoadA = beamLength * (triangularDistributed / 6 - 0.5 * equivalentLoad);
    offNodeLoadB = beamLength * (triangularDistributed / 3 - 0.5 * equivalentLoad);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Исходные данные:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Длина балки = %.2f м\n", beamLength);
    printf("Значение треугольной нагрузки по всей балке = %.2f т/м\n", triangularDistributed);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Результат вычисления:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Эквивалентная нагрузка q = %.2f т/м\n", equivalentLoad);
    printf("Внеузловая нагрузка F1 = %.2f т\n", offNodeLoadA);
    printf("Внеузловая нагрузка F2 = %.2f т\n", offNodeLoadB);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

// справка по работе с программой
void help(void)
{
    printf("\nСправка:\n");
    printf("* Программа предназначена для определения эквивалентной нагрузки.\n");
    printf("* Знак \"минус\" внеузловой нагрузки означает её направление вверх.\n");
}
