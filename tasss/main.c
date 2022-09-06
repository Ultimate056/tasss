#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <iso646.h>
#include <Windows.h>
#define SCREENW 40 // ������ ���� �������.
#define SCREENH 40 // ������ ���� �������.
#define SIZE_DYMANIC_ARRAY 50 // �������������� ������ �����.�������.
#define s '|' // ������ ��� �������� ������ � ���������� printf.

typedef double(*TFun1)(double); // �������� ������������ ���� ���������� �� ������� � 1-� ����������.
typedef double(*TFun2)(double, int); // �������� ������������ ���� ���������� �� ������� � 2-�� �����������.
double monofunc(double); // ���������� �������.
double bitfunc(double); // �������� ������� � �������������.
double row_amount_func(double, int); // ����� ����.
double* full_elements_dynamic_arr(double* arr, TFun1 f, TFun2 f2, double xmin, double xmax, int helper, int n, double dx); // ���������� �������� � ���.���������� ������.
double* get_sort_arr(double* arr, int sz); // ���������� ������� ��������.
double** Dop_sdvig(double** darr, size_t number_str, size_t number_stolb, int k, int sz, int k1, int helper3); // ����� ��������� ������� �� ����������������� ����� ���������.
double** get_dvumern_arr(double* arr, int number_str, int number_stolb, double** darr); // ��������� ���������� ������� �� �����������.
int get_size_dynamic_arr(double xmin, double xmax, int helper, int n, double dx); // ��������� ������� ������� �������.������� �������� �������.
int get_split_dynamic_arr(int sz); // ��������� �������� � ����� ����������� ��������� ����������� ������� �� ���������.
int get_size_for_split(int sz); // ��������� ������� ��� ��������� �������� (� ����� � ���, ��� ����� ��������� �����, ������� �� ������� �� ����� �� 2/9)
void Out_Rez_func(TFun1 f, TFun2 f2, double xmin, double xmax, double dx, int helper, int n); // ����� �������� � ���� �������.
void Out_graph_func(TFun1 f, TFun2 f2, double xmin, double xmax, int helper, int n, double dx); // ����� ������� �������.
void Out_sort_arr(double* arr, int sz); // ����� ���������������� �������.
void Out_dvumern_arr(double** darr, int number_str, int number_stolb); // ����� ���������� �������. 
void free_dvumern_arr(double** darr, int number_str); // ������� ��� ������������ ������ ���������� �������.
void main(void)
{
	setlocale(LC_ALL, "RUS");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��������� ����������� , ��������� ���������� ���� � ��� ������ � ��������� ������ ���������.
	double dx, xmin, xmax;
	int helper, helper2, helper3, n, split, number_str, number_stolb, k, k1, indeks;
	char helper4;
	double* arr; // ���������� ���������� �����.��������
	double* prot; // �������� ����������� �����.�������
	double** darr1, ** darr2, ** darr3; // ���������� ��������� ��������
	/*
	dx - ��� ���������;
	helper - ������������ ���� (����� ����� �� ���� �������)
	helper2 - ����� ������ ������
	n - ���������� ������ ��� ���� �������
	split - �������� ��� ��������� ����������� ������� �� ���������
	number_str, number_stolb - ����� ����� � �������� ���������� �������.
	k - ����� ��������� �������.
	k1 - ���������� ������ ������.
	helper3 - ������������ ��� ������� �� ������ �������.
	helper4 - �������� ��� ������ �� ����� ��� ��� ��������� �������.
	*/
	system("title �������� ������ �������� �.�."); // ���������� ��������� �������.
	while (1) // ����������� ����, ���� ������������ ��� �� ������� ��������� ���������, ��� �� ���������.
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14))); // ������� ��� ������������� ����� ������ � ����.
		arr = (double*)malloc(SIZE_DYMANIC_ARRAY * sizeof(double)); // �������� ������ ����������� �������
		printf("%c �������� �������(������� �����): %c\n------------------------------------\n%c (1) ���������� Y(x) %14c\n%c (2) �������� V(x) %16c\n%c (3) S(x) ����� ���� %14c\n", s, s, s, s, s, s, s, s);
		puts("------------------------------------");
		scanf("%d", &helper);
		switch (helper)
		{
		case 1:
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 11)));
			printf("�� ������� ���������� �������: | x*arctg(x)-ln(sqrt(1+x^2) |\n");
			printf("��� ���������� ������ ������� ���������� ����� ��������� �������� x � ����� ���������.\n������� ����������� ������� �� -1 �� 1\n");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14)));
			printf("������� ����������� �������� xmin<0 � ������������ �������� xmax>0 � ��� ���������:\n");
			scanf("%lf%lf%lf", &xmin, &xmax, &dx);
			Out_Rez_func(monofunc, 0, xmin, xmax, dx, helper, 0); // ����� �������� � ���� �������
			printf("���������� ������? <�� - y, ��� - ������� n>\n");
			scanf_s("%d", &helper4);
			if ((helper4 = getchar()) == 'y')
			{
				Out_graph_func(monofunc, 0, xmin, xmax, helper, 0, 0); // ����� ������� �������
			}
			full_elements_dynamic_arr(arr, monofunc, 0, xmin, xmax, helper, 0, dx); // ��������� ������
			int sz = get_size_dynamic_arr(xmin, xmax, helper, 0, dx); // � ���������� ��� �����������
			prot = (double*)malloc(sz * sizeof(double)); // �������� ������ ������ �����.������� ���������� ������������
			prot = arr; // ����������� �������� �������(� ������������ 50) ��� ��������� � ������ ������ �����������, � ����� ���������� ������� ������ � ��������.
			get_sort_arr(prot, sz); // ��������� ������ �� ����������.
			Out_sort_arr(prot, sz); // ������� ���������� ������.
			{ // ��������� ����� ����� � ��������.
				get_size_for_split(sz);
				number_str = sz / get_split_dynamic_arr(sz);
				number_stolb = get_split_dynamic_arr(sz);
			}
			darr1 = (double**)malloc(number_str * sizeof(double*)); // �������� ������ ���������� �������: ������� ����������
			for (int i = 0; i < number_str; i++) // � ����� ����� ��������
			{
				darr1[i] = (double*)malloc(number_stolb * sizeof(double));
			}
			darr1 = get_dvumern_arr(prot, number_str, number_stolb, darr1); // �������� ��������� ������
			Out_dvumern_arr(darr1, number_str, number_stolb); // ������� ��������� ������
			puts("���������� ������ ������� �� n ��������� ������ ��� ����:");
			printf("������� �� ������� ����� �������� �������: ");
			scanf("%d", &k);
			printf("������� ���������� ������ ������: ");
			scanf("%d", &k1);
			printf("������� 1, ���� ������ �������� ������� ������ � 0 - ���� ���� \n");
			scanf("%d", &helper3);
			darr1 = Dop_sdvig(darr1, number_str, number_stolb, k, sz, k1, helper3); // �������� ��������� ������
			Out_dvumern_arr(darr1, number_str, number_stolb); // ������� ��������� ������
			free(prot);
			free_dvumern_arr(darr1, number_str);
			break;
		case 2:
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 11)));
			printf("�� ������� �������� �������: V(x) = 0.25ln(1+x^1/5) + cos^2(K(x)+1)\n K(z) = { z^2 , z<1  \n z +1 , z>=1 }");
			printf("��� ���������� ������ ������� ���������� ����� ��������� �������� x � ����� ���������. \n ������� ����������� ������� �� -1 �� 1\n");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14)));
			printf("������� ����������� �������� x(���������� ������ 0) � ������������ �������� x(������ 0) � ��� ���������:  ");
			scanf("%lf %lf %lf", &xmin, &xmax, &dx);
			Out_Rez_func(bitfunc, 0, xmin, xmax, dx, helper, 0);
			printf("���������� ������? <�� - y, ��� - ������� n>\n");
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
			darr2 = (double**)malloc(number_str * sizeof(double*)); // �������� ������ ���������� �������: ������� ����������
			for (int i = 0; i < number_str; i++) // � ����� ����� ��������
			{
				darr2[i] = (double*)malloc(number_stolb * sizeof(double));
			}
			darr2 = get_dvumern_arr(prot, number_str, number_stolb, darr2); // �������� ��������� ������
			Out_dvumern_arr(darr2, number_str, number_stolb); // ������� ��������� ������
			puts("���������� ������ ������� �� n ��������� ������ ��� ����:");
			printf("������� �� ������� ����� �������� �������: ");
			scanf("%d", &k);
			printf("������� ���������� ������ ������: ");
			scanf("%d", &k1);
			printf("������� 1, ���� ������ �������� ������� ������ � 0 - ���� ���� \n");
			scanf("%d", &helper3);
			darr2 = Dop_sdvig(darr2, number_str, number_stolb, k, sz2, k1, helper3);
			Out_dvumern_arr(darr2, number_str, number_stolb); // ������� ��������� ������
			free(prot);
			free_dvumern_arr(darr2, number_str);
			break;

		case 3:
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 11)));
			printf("�� ������� ������� ����� ���� �������: E: (-1)^k+1 * x^2k / 2k(2k-1) \n");
			printf("��� ���������� ������ ������� ���������� ����� ��������� �������� x � ����� ��������� � ���������� ������ ����. \n ������� ����������� ������� �� �������\n");
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 14)));
			printf("������� �������� �������� xmin, xmax : \n");
			scanf("%lf %lf", &xmin, &xmax);
			printf("������� ��� ���������\n");
			scanf("%lf", &dx);
			printf("������� ���������� ������ ���� : \n");
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
			darr3 = (double**)malloc(number_str * sizeof(double*)); // �������� ������ ���������� �������: ������� ����������
			for (int i = 0; i < number_str; i++) // � ����� ����� ��������
			{
				darr3[i] = (double*)malloc(number_stolb * sizeof(double));
			}
			darr3 = get_dvumern_arr(prot, number_str, number_stolb, darr3); // �������� ��������� ������
			Out_dvumern_arr(darr3, number_str, number_stolb); // ������� ��������� ������
			puts("���������� ������ ������� �� n ��������� ������ ��� ����:");
			printf("������� �� ������� ����� �������� �������: ");
			scanf("%d", &k);
			printf("������� ���������� ������ ������: ");
			scanf("%d", &k1);
			printf("������� 1, ���� ������ �������� ������� ������ � 0 - ���� ���� \n");
			scanf("%d", &helper3);
			darr3 = Dop_sdvig(darr3, number_str, number_stolb, k, sz3, k1, helper3);
			Out_dvumern_arr(darr3, number_str, number_stolb); // ������� ��������� ������
			free(prot);
			free_dvumern_arr(darr3, number_str);
			break;
		default:
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 13)));
			printf("�� ������ �� �� �����\n");
			break;
		}
		char a;
		printf("��������� ���������? <�� - y, ��� - ������� n>\n");
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
double row_amount_func(double x, int n) // ��� �������
{
	double a_n = pow(x, 2) / 2;
	double sum = a_n;
	double a_n1;
	for (int k = 2; k < n; k++)
	{
		a_n1 = -a_n * (pow(x, 2) * (4 * k - 6) * (k - 1) / (2 * k * (2 * k - 1))); // ������������ �������
		sum = sum + a_n1;
	}
	return sum;
}
void Out_Rez_func(TFun1 f, TFun2 f2, double xmin, double xmax, double dx, int helper, int n) // ����� �����������
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
			y[i] = f(x); // ������ �������� ������� ��� ������ ����� ���� ������ �������
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
	// ���������� ���� � ���������� ������� ����������� ���������
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
	// ����������� ��������� �������� ������� �� ���� ������
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
	printf("��������������� �� ���������� ������ ���������� ��������:\n");
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
	puts("��������� ������ ���������� ��������:");
	for (int i = 0; i < number_str; i++) // ����� ���������� �������
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