#include <iostream>
#include <windows.h>
#include <chrono>

void OrdArr(float* mas, int n, float min, float max);
void RevOrdArr(float* mas, int n, float min, float max);
void RandArr(float* mas, int n, float min, float max);
void SinArr(float* mas, int n, float min, float max);
void PilArr(float* mas, int n, float min, float max);

const int segment = 4; // количество повторений пилообразной и синусоидальной последовательности
const int p = 5000000;

using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	const float min = 20; // минимальный элемент последовательности
	const float max = 100; // максимальный элемент последовательности
	float* mas1 = new float[p]; //Динамический массив

	cout << "Count of elements in the array:" << p << "\n";

	//Генерация упорядоченного массива
	auto begin = std::chrono::steady_clock::now();
	OrdArr(mas1, p, min, max);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "\nTime ordered array: " << float(elapsed_ms.count()) / 1000000 << " seconds";

	//Генерация обратно упорядоченного массива
	begin = std::chrono::steady_clock::now();
	RevOrdArr(mas1, p, min, max);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "\nTime reverse-ordered array: " << float(elapsed_ms.count()) / 1000000 << " seconds";

	//Генерация случайный массив
	begin = std::chrono::steady_clock::now();
	RandArr(mas1, p, min, max);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "\nTime random array: " << float(elapsed_ms.count()) / 1000000 << " seconds";

	//Генерация синусоиды
	begin = std::chrono::steady_clock::now();
	SinArr(mas1, p, min, max);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "\nTime sin. generation: " << float(elapsed_ms.count()) / 1000000 << " seconds";

	//Генерация пилообразной последовательности
	begin = std::chrono::steady_clock::now();
	PilArr(mas1, p, min, max);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "\nTime pil. generation: " << float(elapsed_ms.count()) / 1000000 << " seconds\n\n";
	//////////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}

//Генерация упорядоченного массива
void OrdArr(float* mas, int n, float min, float max)
{
	mas[0] = min;
	for (int i = 1; i < n; i++)
	{
		mas[i] = mas[i - 1] + float((max - min) / n);
	}
}

//Генерация обратно упорядоченного массива
void RevOrdArr(float* mas, int n, float min, float max)
{
	mas[0] = max;
	for (int i = 1; i < n; i++)
	{
		mas[i] = mas[i - 1] - float((max - min) / n);
	}
}

//Генерация случайный массив
void RandArr(float* mas, int n, float min, float max)
{
	for (int i = 0; i < n; i++)
	{
		mas[i] = min + rand() % int(max - min);
	}
}

//Генерация синусоиды
void SinArr(float* mas, int n, float min, float max)
{

	for (int i = 0; i < n; i++)
	{
		mas[i] = int((max - 2 * min) + (cos(i / ((float(n) / float(min * segment)) * 3.1459)) * 2 * min));////////////////////////////
	}
}

//Генерация пилообразной посл-ти
void PilArr(float* mas, int n, float min, float max)
{
	int segment_size = n / segment;
	mas[0] = min;
	for (int i = 1; i < n; i++)
	{
		if (((mas[i - 1] + float((max - min) / segment_size)) > max) && (i != (n - 1)))
		{
			mas[i] = min;
		}
		else
		{
			mas[i] = mas[i - 1] + float((max - min) / segment_size);
		}

	}
} 
