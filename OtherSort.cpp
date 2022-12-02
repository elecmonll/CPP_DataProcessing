#include <iostream>
#include <chrono>
#include <windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ShellSort(int* mas, int n); //Сортировка Шелла
void SelectionSort(int* mas, int size); //Сортировка Выбором
void RandomMas1(int* mas1, int* mas2, int n, int min, int max); //Подпрограмма для рандомного заполнения массива 

using namespace std;
int main()
{
	int min = 20;
	int max = 100;

	//Кол-во элементов в массиве
	long n;
	cout << "Enter number of elements in the array: ";
	cin >> n;
	cout << "\n";

	//Динамический массив
	int* mas1 = new int[n];
	int* mas2 = new int[n];
	
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
	RandomMas1(mas1, mas2, n, min, max); //Записываем случайные элементы в массив
	cout << "Output array:";
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << mas1[i] << " ";
	}
	cout << "\n\n";
	auto begin = std::chrono::steady_clock::now();
	ShellSort(mas1, n); //Выполняем сортировку Шелла по убыванию
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "Time ShellSort in the array (" << n << " - elements in the array): " << elapsed_ms.count() << " McS\n\n";

	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
	cout << "Output array: ";
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << mas2[i] << " ";
	}
	cout << "\n\n";
	begin = std::chrono::steady_clock::now();
	SelectionSort(mas2, n); //Выполняем сортировку Выбором
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "Time SelectionSort in the array (" << n << " - elements in the array): " << elapsed_ms.count() << " McS\n";
	return 0;
}

//Сортировка Шелла
void ShellSort(int* mas, int n)
{
	int step, size = n, i, j, value;
	long double sravn = 0, peresyl = 0;
	step = size / 2; // Выбор шага

	cout << "Changing array in the ShellSort: ";
	cout << "\n";
	while (step > 0)
	{
		for (int i = step; i < size; i++)  // Перечисление элементов, которые сортируются на определённом шаге
		{
			for (j = i - step; j >= 0  ; j = j - step ) // Перестановка элементов внутри массива, пока i-тый не будет отсортирован
			{
				sravn++;
				if (mas[j] < mas[j + step])
				{
					value = mas[j];
					mas[j] = mas[j + step];
					mas[j + step] = value;
					peresyl++;


					for (int y = 0; y < n; y++)
					{
						if (y == (j + step) || y == j)
						{
							SetConsoleTextAttribute(hConsole, (WORD)4);
							cout << mas[y] << " ";
							SetConsoleTextAttribute(hConsole, (WORD)15);
						}
						else
						{
							cout << mas[y] << " ";
						}
					}
					cout << "\n";
				}			
		}
		step = step / 2;
	}
	cout << "\n";
	cout << "The end result of array after ShellSort: ";
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << mas[i] << " ";
	}
	cout << "\n\n";
	cout << "Value of sravn: " << sravn;
	cout << "\n";
	cout << "Value of peresyl: " << peresyl;
	cout << "\n";
}

//Сортировка выбором
void SelectionSort(int* mas, int n)
{
	int max, value, size; // для поиска минимального элемента и для обмена
	size = n;
	long double sravn = 0, peresyl = 0;
	cout << "Changing array in the SelectionSort: ";
	cout << "\n";
	for (int i = 0; i < size - 1; i++)
	{
		max = i; // запоминаем индекс текущего элемента
		// ищем максимальный элемент чтобы поместить на место i-ого
		for (int j = i + 1; j < size; j++) // для остальных элементов после i-ого
		{
			sravn++;
			if (mas[j] > mas[max]) // если элемент больше максимального
			{
				max = j; // запоминаем его индекс в max
			}
		}

		value = mas[i]; // меняем местами i-ый и максимальный элементы
		mas[i] = mas[max];
		mas[max] = value;
		peresyl++;
		
		for (int y = 0; y < n; y++)
		{
			if (y == max || y == i)
			{
				SetConsoleTextAttribute(hConsole, (WORD)4);
				cout << mas[y] << " ";
				SetConsoleTextAttribute(hConsole, (WORD)15);
			}
			else
			{
				if (y < i)
				{
					cout << mas[y] << " ";
				}
				else
				{
					cout << "   ";
				}
			}
		}
		cout << "\n";
		

	}
	cout << "\n";
	cout << "The end result of array after SelectionSort: ";
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << mas[i] << " ";
	}
	cout << "\n\n";
	cout << "Value of sravn: " << sravn;
	cout << "\n";
	cout << "Value of peresyl: " << peresyl;
	cout << "\n";
}

//Генерация случайных массивов
void RandomMas1(int* mas1, int* mas2, int n, int min, int max)
{
	for (int i = 0; i < n; i++)
	{
		mas1[i] = min + rand() % (max - min);
		mas2[i] = mas1[i];
	}
	
} 