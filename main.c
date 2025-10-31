#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>

#define PI 3.14159265358979323846

float area_pentagon(float radius)
{
    // S = (5/2) * R^2 * tan(54°)
    float result = (5.0 / 2.0) * radius * radius * tan(54 * PI / 180);
    return result;
}

int isPointInsidePentagon(double x, double y, double centerX, double centerY, double outside_radius, double aspect_ratio)
{
    int n = 0;

    for (int i = 0; i < 5; i++)
    {
        double angle1 = i * (2 * PI / 5) - PI / 2;
        double x1 = centerX + outside_radius * cos(angle1);
        double y1 = centerY + (outside_radius / aspect_ratio) * sin(angle1);

        double angle2 = (i + 1) * (2 * PI / 5) - PI / 2;
        double x2 = centerX + outside_radius * cos(angle2);
        double y2 = centerY + (outside_radius / aspect_ratio) * sin(angle2);

        if (((y1 > y) != (y2 > y)) &&
            (x < (x2 - x1) * (y - y1) / (y2 - y1) + x1))
        {
            n++;
        }
    }
    if (n % 2 == 1) 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Функция для сравнения двух пентагонов по площади
float compare_pentagon(float radius1, float radius2)
{
    float area1 = area_pentagon(radius1);
    float area2 = area_pentagon(radius2);
    float result = area1 - area2;
    return result;
}

int main()
{
    setlocale(LC_ALL, "RUS");

    int choice;
    float radius, radius1, radius2;
    char symbol;

    do
    {
        printf("\nМеню:\n");
        printf("1. Рассчитать площадь пентагона\n");
        printf("2. Вывести определение пентагона\n");
        printf("3. Нарисовать пентагон\n");
        printf("4. Сравнить два пентагона по площади\n");
        printf("5. Выход\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Введите радиус вписанной окружности пентагона: ");
            scanf("%f", &radius);
            if (radius > 0)
            {
                float area = area_pentagon(radius);
                printf("Площадь пентагона с радиусом вписанной окружности %.2f = %.4f\n",
                       radius, area);
            }
            else
            {
                printf("Ошибка: радиус должен быть положительным числом!\n");
            }
            break;

        case 2:
            printf("Пентагон (Правильный пятиугольник) - это правильный многоугольник с пятью равными сторонами\n");
            printf("и пятью равными углами (108 градусов каждый).\n");
            printf("Все вершины пентагона лежат на одной окружности (описанная окружность),\n");
            printf("а все стороны касаются другой окружности (вписанная окружность).\n");
            break;

        case 3:
            printf("Введите символ для отображения фигуры: ");
            scanf(" %c", &symbol);
            printf("Введите радиус вписанной окружности пентагона: ");
            scanf("%f", &radius);
            if (radius > 0)
            {
                double aspect_ratio = 2.0;

                // Вычисляем радиус описанной окружности
                double outside_radius = radius / cos(36 * PI / 180);

                int width = 2 * (int)ceil(outside_radius) + 4;
                int height = 2 * (int)ceil(outside_radius / aspect_ratio) + 2;

                // Координаты центра пентагона
                int centerX = width / 2;
                int centerY = height / 2;

                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        int isOnBorder = 0;
                        int is_inside = 0;

                        for (int i = 0; i < 5; i++)
                        {
                            double angle1 = (i * 72 - 90) * PI / 180.0;
                            double x1 = centerX + outside_radius * cos(angle1);
                            double y1 = centerY + (outside_radius / aspect_ratio) * sin(angle1);

                            double angle2 = ((i + 1) * 72 - 90) * PI / 180.0;
                            double x2 = centerX + outside_radius * cos(angle2);
                            double y2 = centerY + (outside_radius / aspect_ratio) * sin(angle2);

                            double distance = fabs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) /
                                              sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));

                            double eps = 0.3;
                            int betweenX = (x >= fmin(x1, x2) - 0.5 && x <= fmax(x1, x2) + 0.5);
                            int betweenY = (y >= fmin(y1, y2) - 0.5 && y <= fmax(y1, y2) + 0.5);

                            if (distance <= eps && betweenX && betweenY)
                            {
                                isOnBorder = 1;
                                break;
                            }
                        }

                        is_inside = isPointInsidePentagon(x, y, centerX, centerY, outside_radius, aspect_ratio);

                        if (isOnBorder || is_inside)
                        {
                            printf("%c", symbol);
                        }
                        else
                        {
                            printf(" ");
                        }
                    }
                    printf("\n");
                }
            }
            else
            {
                printf("Ошибка: радиус должен быть положительным числом!\n");
            }
            break;

        case 4:
            printf("Введите радиус вписанной окружности первого пентагона: ");
            scanf("%f", &radius1);
            printf("Введите радиус вписанной окружности второго пентагона: ");
            scanf("%f", &radius2);

            if (radius1 > 0 && radius2 > 0)
            {
                float difference = compare_pentagon(radius1, radius2);
                float area1 = area_pentagon(radius1);
                float area2 = area_pentagon(radius2);

                printf("\nРезультаты сравнения:\n");
                printf("Пентагон 1 (R=%.2f): площадь = %.4f\n", radius1, area1);
                printf("Пентагон 2 (R=%.2f): площадь = %.4f\n", radius2, area2);

                if (difference > 0)
                {
                    printf("Пентагон 1 больше пентагона 2 на %.4f\n", difference);
                }
                else if (difference < 0)
                {
                    printf("Пентагон 2 больше пентагона 1 на %.4f\n", -difference);
                }
                else
                {
                    printf("Пентагоны имеют одинаковую площадь\n");
                }
            }
            else
            {
                printf("Ошибка: радиусы должны быть положительными числами!\n");
            }
            break;

        case 5:
            break;

        default:
            printf("Выбран неверный номер пункта меню!\n");
        }

    } while (choice != 5);

    return 0;
}