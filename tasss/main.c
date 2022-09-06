#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <iso646.h>
#include <Windows.h>
#define SCREENW 40 // Ширина поля графика.
#define SCREENH 40 // Высота поля графика.
#define SIZE_DYMANIC_ARRAY 50 // Первоначальный размер динам.массива.
#define s '|' // Символ для удобства работы с оператором printf.

typedef double(*TFun1)(double); // Создание собственного типа указателей на функции с 1-м аргументом.
typedef double(*TFun2)(double, int); // Создание собственного типа указателей на функции с 2-мя аргументами.
double monofunc(double); // Монотонная функция.
double bitfunc(double); // Кусочная функция с разветвлением.
double row_amount_func(double, int); // Сумма ряда.
double* full_elements_dynamic_arr(double* arr, TFun1 f, TFun2 f2, double xmin, double xmax, int helper, int n, double dx); // Заполнение значений в дин.одномерный массив.
double* get_sort_arr(double* arr, int sz); // Сортировка массива значений.
double** Dop_sdvig(double** darr, size_t number_str, size_t number_stolb, int k, int sz, int k1, int helper3); // Сдвиг элементов матрицы на пользовательского число элементов.
double** get_dvumern_arr(double* arr, int number_str, int number_stolb, double** darr); // Получение двумерного массива из одномерного.
int get_size_dynamic_arr(double xmin, double xmax, int helper, int n, double dx); // Получение точного размера динамич.массива значений функций.
int get_split_dynamic_arr(int sz); // Получение делителя с целью дальнейшего разбиения одномерного массива на двумерный.
int get_size_for_split(int sz); // получение размера для получения делителя (В связи с тем, что может попасться число, которое не делится на цифры от 2/9)
void Out_Rez_func(TFun1 f, TFun2 f2, double xmin, double xmax, double dx, int helper, int n); // Вывод значений в виде таблицы.
void Out_graph_func(TFun1 f, TFun2 f2, double xmin, double xmax, int helper, int n, double dx); // Вывод графика функции.
void Out_sort_arr(double* arr, int sz); // Вывод отсортированного массива.
void Out_dvumern_arr(double** darr, int number_str, int number_stolb); // Вывод двумерного массива. 
void free_dvumern_arr(double** darr, int number_str); // функция для освобождения памяти двумерного массива.
void main(void)
{
	setlocale(LC_ALL, "RUS");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Получение дескриптора , позволяет определять цвет и фон текста в различных местах программы.
	double dx, xmin, xmax;
	int helper, helper2, helper3, n, split, number_str, number_stolb, k, k1, indeks;
	char helper4;
	double* arr; // объявление одномерных динам.массивов
	double* prot; // прототип одномерного динам.массива
	double** darr1, ** darr2, ** darr3; // объявление двумерных массивов
	/*
	dx - шаг табуляции;
	helper - путеводитель меню (выбор одной из трех функций)
	helper2 - выбор потока данных
	n - количество членов для ряда Тейлора
	split - делитель для разбиения одномерного массива на двумерный
	number_str, number_stolb - число строк и столбцов двумерного массива.
	k - сдвиг элементов матрицы.
	k1 - количество циклов сдвига.
	helper3 - путеводитель для функции по сдвигу матрицы.
	helper4 - помощник для выхода из цикла или для различных условий.
	*/
	system("title Курсовая работа Копылова В.Ю."); // объявление заголовка консоли.
	while (1) // бесконечный цикл, пока пользователь сам не захочет завершить программу, она не закроется.
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14))); // функция для распределения цвета текста и фона.
		arr = (double*)malloc(SIZE_DYMANIC_ARRAY * sizeof(double)); // выделяем память одномерному массиву
		printf("%c Выберите функцию(впишите цифру): %c\n------------------------------------\n%c (1) Монотонная Y(x) %14c\n%c (2) Кусочная V(x) %16c\n%c (3) S(x) Сумма ряда %14c\n", s, s, s, s, s, s, s, s);
		puts("------------------------------------");
		scanf("%d", &helper);
		switch (helper)
		{
		case 1:
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 11)));
			printf("Вы выбрали монотонную функцию: | x*arctg(x)-ln(sqrt(1+x^2) |\n");
			printf("Для выполнения данной функции необходимо любое множество значений x с шагом табуляции.\nОбласть определения функции от -1 до 1\n");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14)));
			printf("Введите минимальное значение xmin<0 и максимальное значение xmax>0 и шаг табуляции:\n");
			scanf("%lf%lf%lf", &xmin, &xmax, &dx);
			Out_Rez_func(monofunc, 0, xmin, xmax, dx, helper, 0); // вывод значений в виде таблицы
			printf("Нарисовать график? <Да - y, Нет - введите n>\n");
			scanf_s("%d", &helper4);
			if ((helper4 = getchar()) == 'y')
			{
				Out_graph_func(monofunc, 0, xmin, xmax, helper, 0, 0); // вывод графика функции
			}
			full_elements_dynamic_arr(arr, monofunc, 0, xmin, xmax, helper, 0, dx); // заполняем массив
			int sz = get_size_dynamic_arr(xmin, xmax, helper, 0, dx); // и запоминаем его размерность
			prot = (double*)malloc(sz * sizeof(double)); // выделяем память новому динам.массиву полученной размерностью
			prot = arr; // присваиваем значения массива(с размерностью 50) его прототипу с точным числом размерности, с целью дальнейшей удобной работы с массивом.
			get_sort_arr(prot, sz); // сортируем массив по неубыванию.
			Out_sort_arr(prot, sz); // выводим полученный массив.
			{ // получение числа строк и столбцов.
				get_size_for_split(sz);
				number_str = sz / get_split_dynamic_arr(sz);
				number_stolb = get_split_dynamic_arr(sz);
			}
			darr1 = (double**)malloc(number_str * sizeof(double*)); // выделяем память двумерному массиву: массиву указателей
			for (int i = 0; i < number_str; i++) // а здесь самим массивам
			{
				darr1[i] = (double*)malloc(number_stolb * sizeof(double));
			}
			darr1 = get_dvumern_arr(prot, number_str, number_stolb, darr1); // получаем двумерный массив
			Out_dvumern_arr(darr1, number_str, number_stolb); // выводим двумерный массив
			puts("Реализация сдвига матрицы на n элементов вправо или вниз:");
			printf("Введите на сколько нужно сдвинуть матрицу: ");
			scanf("%d", &k);
			printf("Введите количество циклов сдвига: ");
			scanf("%d", &k1);
			printf("Нажмите 1, если хотите сдвинуть матрицу вправо и 0 - если вниз \n");
			scanf("%d", &helper3);
			darr1 = Dop_sdvig(darr1, number_str, number_stolb, k, sz, k1, helper3); // сдвигаем двумерный массив
			Out_dvumern_arr(darr1, number_str, number_stolb); // выводим двумерный массив
			free(prot);
			free_dvumern_arr(darr1, number_str);
			break;
		case 2:
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 11)));
			printf("Вы выбрали кусочную функцию: V(x) = 0.25ln(1+x^1/5) + cos^2(K(x)+1)\n K(z) = { z^2 , z<1  \n z +1 , z>=1 }");
			printf("Для выполнения данной функции необходимо любое множество значений x с шагом табуляции. \n Область определения функции от -1 до 1\n");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14)));
			printf("Введите минимальное значение x(желательно меньше 0) и максимальное значение x(больше 0) и шаг табуляции:  ");
			scanf("%lf %lf %lf", &xmin, &xmax, &dx);
			Out_Rez_func(bitfunc, 0, xmin, xmax, dx, helper, 0);
			printf("Нарисовать график? <Да - y, Нет - введите n>\n");
			scanf_s("%d", &helper4);
			if ((helper4 = getchar()) == 'y')
			{
				Out_graph_func(bitfunc, 0, xmin, xmax, helper, 0, 0);
			}
			full_elements_dynamic_arr(arr, bitfunc, 0, xmin, xmax, helper, 0, dx);
			int sz2 = get_size_dynamic_arr(xmin, xmax, helper, 0, dx);
			prot = (double*)malloc(sz2 * sizeof(double));
			prot = arr;
			get_sort_arr(prot, sz2);
			Out_sort_arr(prot, sz2);
			{
				get_size_for_split(sz2);
				number_str = sz2 / get_split_dynamic_arr(sz2);
				number_stolb = get_split_dynamic_arr(sz2);
			}
			darr2 = (double**)malloc(number_str * sizeof(double*)); // выделяем память двумерному массиву: массиву указателей
			for (int i = 0; i < number_str; i++) // а здесь самим массивам
			{
				darr2[i] = (double*)malloc(number_stolb * sizeof(double));
			}
			darr2 = get_dvumern_arr(prot, number_str, number_stolb, darr2); // получаем двумерный массив
			Out_dvumern_arr(darr2, number_str, number_stolb); // выводим двумерный массив
			puts("Реализация сдвига матрицы на n элементов вправо или вниз:");
			printf("Введите на сколько нужно сдвинуть матрицу: ");
			scanf("%d", &k);
			printf("Введите количество циклов сдвига: ");
			scanf("%d", &k1);
			printf("Нажмите 1, если хотите сдвинуть матрицу вправо и 0 - если вниз \n");
			scanf("%d", &helper3);
			darr2 = Dop_sdvig(darr2, number_str, number_stolb, k, sz2, k1, helper3);
			Out_dvumern_arr(darr2, number_str, number_stolb); // выводим двумерный массив
			free(prot);
			free_dvumern_arr(darr2, number_str);
			break;

		case 3:
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 11)));
			printf("Вы выбрали функцию суммы ряда Тейлора: E: (-1)^k+1 * x^2k / 2k(2k-1) \n");
			printf("Для выполнения данной функции необходимо любое множество значений x с шагом табуляции и количество членов ряда. \n Область определения функции не имеется\n");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14)));
			printf("Введите диапазон значений xmin, xmax : \n");
			scanf("%lf %lf", &xmin, &xmax);
			printf("Введите шаг табуляции\n");
			scanf("%lf", &dx);
			printf("Введите количество членов ряда : \n");
			scanf("%d", &n);
			Out_Rez_func(0, row_amount_func, xmin, xmax, dx, helper, n);
			full_elements_dynamic_arr(arr, 0, row_amount_func, xmin, xmax, helper, n, dx);
			int sz3 = get_size_dynamic_arr(xmin, xmax, helper, n, dx);
			prot = (double*)malloc(sz * sizeof(double));
			prot = arr;
			get_sort_arr(prot, sz3);
			Out_sort_arr(prot, sz3);
			{
				get_size_for_split(sz3);
				number_str = sz3 / get_split_dynamic_arr(sz3);
				number_stolb = get_split_dynamic_arr(sz3);
			}
			darr3 = (double**)malloc(number_str * sizeof(double*)); // выделяем память двумерному массиву: массиву указателей
			for (int i = 0; i < number_str; i++) // а здесь самим массивам
			{
				darr3[i] = (double*)malloc(number_stolb * sizeof(double));
			}
			darr3 = get_dvumern_arr(prot, number_str, number_stolb, darr3); // получаем двумерный массив
			Out_dvumern_arr(darr3, number_str, number_stolb); // выводим двумерный массив
			puts("Реализация сдвига матрицы на n элементов вправо или вниз:");
			printf("Введите на сколько нужно сдвинуть матрицу: ");
			scanf("%d", &k);
			printf("Введите количество циклов сдвига: ");
			scanf("%d", &k1);
			printf("Нажмите 1, если хотите сдвинуть матрицу вправо и 0 - если вниз \n");
			scanf("%d", &helper3);
			darr3 = Dop_sdvig(darr3, number_str, number_stolb, k, sz3, k1, helper3);
			Out_dvumern_arr(darr3, number_str, number_stolb); // выводим двумерный массив
			free(prot);
			free_dvumern_arr(darr3, number_str);
			break;
		default:
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 13)));
			printf("Вы нажали не ту цифру\n");
			break;
		}
		char a;
		printf("Повторить программу? <Да - y, Нет - введите n>\n");
		scanf_s("%d", &a);
		if ((a = getchar()) == 'n')
		{
			break;
		}
		else
		{
			system("cls");
		}
	}
	system("pause");
}
double monofunc(double x)
{
	return x * atan(x) - log(sqrt(1 + pow(x, 2)));
}
double bitfunc(double x)
{
	if (x < 1)
	{
		return 0.25 * log(1 + pow(x, 1 / 5)) + pow(cos(pow(x, 2) + 1), 2);
	}
	else
	{
		return 0.25 * log(1 + pow(x, 1 / 5)) + pow(cos(x + 2), 2);
	}
}
double row_amount_func(double x, int n) // ряд тейлора
{
	double a_n = pow(x, 2) / 2;
	double sum = a_n;
	double a_n1;
	for (int k = 2; k < n; k++)
	{
		a_n1 = -a_n * (pow(x, 2) * (4 * k - 6) * (k - 1) / (2 * k * (2 * k - 1))); // рекуррентная формула
		sum = sum + a_n1;
	}
	return sum;
}
void Out_Rez_func(TFun1 f, TFun2 f2, double xmin, double xmax, double dx, int helper, int n) // вывод результатов
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 10)));
	puts("-------------------");
	printf("|  x   %2c   Y(x) %3c \n", s, s);
	if (helper == 1 or helper == 2)
	{
		for (double x = xmin; x <= xmax; x += dx)
		{
			printf("| %5.2lf %c %6.2lf %3c \n", x, s, f(x), s);
		}
		puts("-------------------");
	}
	else if (helper == 3)
	{
		for (double x = xmin; x <= xmax; x += dx)
		{
			printf("| %5.2lf %c %6.2lf %3c \n", x, s, f2(x, n), s);
		}
		puts("-------------------");
	}
}
void Out_graph_func(TFun1 f, TFun2 f2, double xmin, double xmax, int helper, int n, double dx)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 10)));
	char screen[SCREENW][SCREENH];
	double x, y[SCREENW];
	double ymin = 0, ymax = 0;
	int i, j, xz, yz;
	double hy, hx;
	hx = (xmax - xmin) / (SCREENW - 1);
	for (i = 0, x = xmin; i < SCREENW and xmin <= xmax; i++, x += hx)
	{
		if (helper == 1 or helper == 2)
		{
			y[i] = f(x); // расчёт значений функций для каждой точки поля вывода графика
		}
		else
		{
			y[i] = f2(xmin, n, xmax, dx);
		}
		if (y[i] < ymin)
		{
			ymin = y[i];
		}
		if (y[i] > ymax)
		{
			ymax = y[i];
		}
	}
	hy = (ymax - ymin) / (SCREENH - 1);
	yz = (int)floor(ymax / hy + 0.5);
	xz = (int)floor((0. - xmin) / hx + 0.5);
	// построение осей и заполнение массива отображения пробелами
	for (j = 0; j < SCREENH; ++j)
	{
		for (i = 0; i < SCREENW; ++i)
		{
			if (j == yz and i == xz)
			{
				screen[i][j] = '*';
			}
			else if (j == yz)
			{
				screen[i][j] = '-';
			}
			else if (i == xz)
			{
				screen[i][j] = '|';
			}
			else screen[i][j] = ' ';
		}
	}
	// определение положения значения функции на поле вывода
	for (i = 0; i < SCREENW; ++i)
	{
		j = (int)floor((ymax - y[i]) / hy + 0.5);
		screen[i][j] = '*';
	}
	for (j = 0; j < SCREENH; ++j)
	{
		for (i = 0; i < SCREENW; ++i)
		{
			putchar(screen[i][j]);
		}
		putchar('\n');
	}
}
double* full_elements_dynamic_arr(double* arr, TFun1 f, TFun2 f2, double xmin, double xmax, int helper, int n, double dx)
{
	if (helper == 1 or helper == 2)
	{
		for (double x = xmin; x <= xmax; x += dx, arr++)
		{
			*arr = f(x);
		}
	}
	if (helper == 3)
	{
		for (double x = xmin; x <= xmax; x += dx, arr++)
		{
			*arr = f2(x, n);
		}
	}
	return arr;
}
int get_size_dynamic_arr(double xmin, double xmax, int helper, int n, double dx)
{
	int sz = 0;
	if (helper == 1 or helper == 2)
	{
		for (double x = xmin; x <= xmax; x += dx)
		{
			sz++;
		}
	}
	else
	{
		int i = 0;
		for (double x = xmin; x <= xmax; x += dx)
		{
			sz++;
		}
	}
	return sz;
}
double* get_sort_arr(double* arr, int sz)
{
	for (int i = 1; i < sz; ++i)
	{
		int k = i;
		while (k > 0 and arr[k - 1] > arr[k])
		{
			double tmp = arr[k - 1];
			arr[k - 1] = arr[k];
			arr[k] = tmp;
			k -= 1;
		}
	}
	return arr;
}
void Out_sort_arr(double* arr, int sz)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 10)));
	printf("Отсортированный по неубыванию массив полученных значений:\n");
	for (int i = 0; i < sz; i++, arr++)
	{
		printf("A[%d] = %lf\n", i, *arr);
	}
	puts("-----------------------------------------------------------");
}
int get_split_dynamic_arr(int sz)
{
	int split;
	{
		if (sz % 4 == 0 and sz % 6 == 0 and sz % 8 == 0) split = 8;
		if (sz % 4 == 0 and sz % 6 == 0 and sz % 8 != 0) split = 6;
		if (sz % 4 == 0 and sz % 6 != 0 and sz % 6 != 0) split = 4;
		if (sz % 2 == 0 and sz % 4 != 0 and sz % 6 != 0 and sz % 8 != 0) split = 2;
		if (sz % 3 == 0) split = 3;
		if (sz % 9 == 0) split = 9;
		if (sz % 5 == 0) split = 5;
		if (sz % 7 == 0) split = 7;
	}
	return split;
}
int get_size_for_split(int sz)
{
	if (sz % 2 != 0 and sz % 3 != 0 and sz % 4 != 0 and sz % 5 != 0 and sz % 6 != 0 and sz % 7 != 0 and sz % 8 != 0 and sz % 9 != 0)
	{
		sz = sz - 1;
		return sz;
	}
	else
	{
		return sz;
	}
}
double** get_dvumern_arr(double* arr, int number_str, int number_stolb, double** darr)
{
	for (int i = 0; i < number_str; i++)
	{
		for (int j = 0; j < number_stolb; j++, arr++)
		{
			darr[i][j] = *arr;
		}
	}
	return darr;
}
void Out_dvumern_arr(double** darr, int number_str, int number_stolb)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 10)));
	puts("Двумерный массив полученных значений:");
	for (int i = 0; i < number_str; i++) // вывод двумерного массива
	{
		for (int j = 0; j < number_stolb; j++)
		{
			printf("%.2lf ", darr[i][j]);
		}
		printf("\n");
	}
	puts("-----------------------------------------------------------");
}
double** Dop_sdvig(double** darr, size_t number_str, size_t number_stolb, int k, int sz, int k1, int helper3)
{
	int nmin, mmin;
	double buf_a;
	switch (helper3)
	{
	case 0:
		for (int z = 0; z < k1; z++)
		{
			for (int i = number_str - 1; i > 0; i--)
			{
				nmin = i - 1;
				for (int j = 0; j < number_stolb; j++)
				{
					buf_a = darr[i][j];
					darr[i][j] = darr[nmin][j];
					darr[nmin][j] = buf_a;
				}

			}

		}
		break;
	case 1:
		for (int z = 0; z < k1; z++)
		{
			for (int j = number_stolb - 1; j > 0; j--)
			{
				mmin = j - 1;
				for (int i = 0; i < number_str; i++)
				{
					buf_a = darr[i][j];
					darr[i][j] = darr[i][mmin];
					darr[i][mmin] = buf_a;
				}
			}
		}
		break;
	}
	return darr;
}
void free_dvumern_arr(double** darr, int number_str)
{
	for (int i = 0; i < number_str; i++)
	{
		free(darr[i]);
	}
	free(darr);
}