#include <iostream>
#include <windows.h>
#include <chrono>
#include <cmath>

int ALGORITHM_S(char* mas, char x, int n, int* sravn); //последовательный поиск
int ALGORITHM_Q(char* mas, char x, int n, int* sravn); //быстрый последовательный поиск
int ALGORITHM_T(char* mas, char x, int n, int* sravn); //последовательный поиск в упорядоченной таблице
int BinarySearch(char* mas, char x, int n, int* sravn); //бинарный поиск

void Sort(char* mass, int n);//сортировка массива
void CheckForResult(int rez); //проверка результата и его вывод

using namespace std::chrono;
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	//Ввод искомого элемента
	char x;
	cout << "Enter desired element:\n";
	cin >> x;

	//Ввод количества элементов
	long n;
	cout << "\nEnter the number of elements in the array:\n";
	do
	{
		cin >> n;
		if (!(n >= 1))
		{
			cout << "Error, enter the number more than 1\n";
			return 0;
		}

	} while (!(n >= 1));

	//Выбор типа ввода массива
	int j;
	cout << "\nEnter:\n 1 - for manually entering an array,\n 2 - for randomly generste elements arrays\n";
	do
	{
		cin >> j;
		if (!((j == 1) || (j == 2)))
		{
			cout << "Error, enter 1 or 2\n";
			return 0;
		}

	} while (!((j == 1) || (j == 2)));

	//Cоздание массива
	char* mas_SQ = new char[n];
	if (j == 1)
	{
		//Ручной ввод массива
		cout << "\nEnter elements in the array:\n";
		for (int i = 0; i < n; i++)
		{
			cin >> mas_SQ[i];
		}
	}
	else
	{
		//Случайная генерация массива 		
		for (int i = 0; i < n; i++)
		{
			mas_SQ[i] = 'a' + rand() % 26;
			//cout << mas_SQ[i]<<",";

		}
	}

	//Переменная для результата
	int rez;
	//Переменная для количества сравнений
	int u = 0;
	int* sravn = &u;

	//Алгоритм S
	*sravn = 0;
	auto begin = std::chrono::steady_clock::now();
	rez = ALGORITHM_S(mas_SQ, x, n, sravn);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	CheckForResult(rez);
	cout << "\ntime S = " << elapsed_ms.count() << "McS" << "\ncomparations =  " << *sravn;

	//Алгоритм Q
	*sravn = 0;
	begin = std::chrono::steady_clock::now();
	rez = ALGORITHM_Q(mas_SQ, x, n, sravn);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	CheckForResult(rez);
	cout << "\ntime Q = " << elapsed_ms.count() << "McS" << "\ncomparations =  " << *sravn;

	//Создаем упорядоченный массив для бинарного поиска и алгоритма T
	char* mas_TB = new char[n + 1];

	for (int i = 0; i < n; i++)
	{
		mas_TB[i] = mas_SQ[i];
	}
	mas_TB[n] = '}'; //Фиктивный элемент с макс. значением ключа

	//Сортировка массива
	Sort(mas_TB, n);

	//Алгоритм T
	*sravn = 0;
	begin = std::chrono::steady_clock::now();
	rez = ALGORITHM_T(mas_TB, x, n + 1, sravn);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	CheckForResult(rez);
	cout << "\ntime T = " << elapsed_ms.count() << "McS" << "\ncomparations =  " << *sravn;

	//Бинарный поиск
	*sravn = 0;
	begin = std::chrono::steady_clock::now();
	rez = BinarySearch(mas_TB, x, n, sravn);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	CheckForResult(rez);
	cout << "\ntime BinS = " << elapsed_ms.count() << "McS" << "\ncomparations =  " << *sravn;
	cout << "\n";

	return 0;
}

///////////////////Подпрограммы
//Алгоритм S (последовательный поиск)
int ALGORITHM_S(char* mas, char x, int n, int* sravn)
{
	int i = 0;
	for (; i < n; i++, (*sravn)++)
	{
		(*sravn)++;
		if (mas[i] == x)
		{
			return i + 1;
		}
	}
	return NULL;
}

//Алгоритм Q (быстрый последовательный поиск)
int ALGORITHM_Q(char* mas, char x, int n, int* sravn)
{
	int i = 0;
	int last = mas[n];
	mas[n] = x;
	while (mas[i] != x)
	{
		(*sravn)++;
		i++;
	}
	mas[n] = last;
	(*sravn)++;
	if ((i < n) || (mas[n] == x))
	{
		return i + 1;
	}
	else
	{
		return NULL;
	}
}

//Алгоритм Т (последовательный поиск в упорядоченной таблице)
int ALGORITHM_T(char* mas, char x, int n, int* sravn)
{
	int i = 0;
	while (true)
	{
		(*sravn)++;
		if (mas[i] >= x)
		{
			if (mas[i] == x)
			{
				return i + 1;
			}
			else return NULL;
		}
		else
		{
			i++;
		}
	}

}

//Бинарный поиск
int BinarySearch(char* mas, char x, int n, int* sravn)
{
	int p = 0,
		r = n,
		q;
	while (p <= r)
	{
		q = (p + r) / 2;
		(*sravn)++;
		if (mas[q - 1] == x)
		{
			return q;
		}
		if (mas[q - 1] > x)
		{
			r = q - 1;
		}
		if (mas[q - 1] < x)
		{
			p = q + 1;
		}
	}
	return NULL;
}

//Проверка результата и его вывод
void CheckForResult(int rez)
{
	if (rez == NULL)
	{
		cout << "\n\nElement is not present in the array";
	}
	else
	{
		cout << "\n\nElement found at position: " << rez;
	}
}

//Сортировка массива для его использования в алгоритме Т и бинарном поиске
void Sort(char* mass, int n)
{
	int left = 0, right = n - 1; // левая и правая границы сортируемой области массива
	int flag = 1;
	while ((left < right) && flag > 0)
	{
		flag = 0;
		for (int i = left; i < right; i++)  //двигаемся слева направо
		{
			if (mass[i] > mass[i + 1]) // если следующий элемент меньше текущего,меняем их местами
			{
				char t = mass[i];
				mass[i] = mass[i + 1];
				mass[i + 1] = t;
				flag = 1;
			}
		}
		right--;
		for (int i = right; i > left; i--)  //двигаемся справа налево
		{
			if (mass[i - 1] > mass[i]) // если предыдущий элемент больше текущего,
			{            // меняем их местами
				char t = mass[i];
				mass[i] = mass[i - 1];
				mass[i - 1] = t;
				flag = 1;    // перемещения в этом цикле были
			}
		}
		left++; // сдвигаем левую границу на следующий элемент
	}
}
