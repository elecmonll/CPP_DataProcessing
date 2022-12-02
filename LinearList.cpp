#include <iostream>

int Choice(int* ptr); //выбор номера задания
void FirstList(); //создание первого элемента в списке
void CreateList(int* ptr); //создание списка
void MaxElement(); //нахождение и вывод макс. элемента в списке
void NewElement(int* ptr); //заменяем один элемент на другой в начале списка
void DeleteElement(int* ptr); //удаляем первый элемент в списке
void DeleteList(); //удаление списка
void PrintList(); //вывод списка
void New_Element(int* ptr);
struct elem* MaxFound(); //нахождение макс. элемента в списке

using namespace std;
int main()
{
	int n; //задаем кол-вл элементов в списке
	cout << "Elements in the list: ";
	cin >> n;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n";
	int a = -1;
	int* ptr = &n;
	while (a != 0)
	{
		a = Choice(ptr); //выбираем номер задания
	}

	return 0;
}

struct elem
{
	char data;
	elem* next;
	elem* pred;
};
elem* header;

int Choice(int* ptr)
{
	//Указатель на количество элментов в списке
	long a;
	cout << "Press 1. Create list.\nPress 2. Max. element in the list.\nPress 3. Add a new element in the start of list.\nPress 4. Delete first element of the first list.\nPress 5. Delete list.\nPress 6. Add a new element in the list.\nPress 0. End the program.\n";
	cout << "Select number, please: ";
	cin >> a;
	if (a == 0) //конец программы
	{
		cout << "\nEnd of the program!\n";
		return a;
	}
	else
	{
		if (a == 1) //создание списка и его вывод
		{
			cout << "\nNUMBER 1:\n";
			FirstList();
			CreateList(ptr);
			PrintList();
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		if (a == 2) //нахождение максимального значения в списке
		{
			cout << "\nNUMBER 2:\n";
			MaxElement();
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		if (a == 3) //запись нового элемента в начало списка
		{
			cout << "\nNUMBER 3:\n";
			NewElement(ptr);
			PrintList();
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		if (a == 4) //удаление элемента в начале списка
		{
			cout << "\nNUMBER 4:\n";

			DeleteElement(ptr);
			PrintList();
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		if (a == 5) //удаление списка
		{
			cout << "\nNUMBER 5:\n";
			DeleteList();

			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		if (a == 6) //удаление списка
		{
			cout << "\nNUMBER 6:\n";
			New_Element(ptr);
			PrintList();
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
	}
	return a;
}

////////_1_////////
void FirstList() //создание первого элемента в списке
{
	elem* value;
	value = new elem;
	value->data = char('A' + rand() % ('Z' - 'A'));
	value->next = NULL; //установка указатель на next
	value->pred = NULL; //установка указатель на pred
	header = value; //определяется начало списка
}

void CreateList(int* ptr) //создание списка
{
	elem* first;
	elem* value;
	first = header; //устанавливаем начальное значение списка
	int i = 1;
	int n = *ptr;
	while (i <= n)
	{
		value = new elem;
		value->data = char('A' + rand() % ('Z' - 'A')); //запоминаем рандомный элемент в список
		value->pred = first;
		first->next = value;
		first = value;
		i++;
	}
	first->next = NULL;
}

////////_2_////////
void MaxElement() //максимальный элемент в списке и его позиция в списке
{


	elem* value;
	value = header; //устанавливаем начальное значение списка
	elem* value1;
	int i = 1;
	while (value->next != NULL)
	{
		if (value->data == MaxFound()->data)
		{
			value1 = value;
			cout << "Max. element in the list: " << value1->data;
			cout << "\nMax. element index in the list: " << i;
			cout << "\n";
			return;
		}
		value = value->next;
		i++;
	}
}

////////_3_////////
void NewElement(int* ptr) //новый элемент в начале списка
{
	elem* value;
	elem* first;
	value = new elem;
	first = header;
	value->data = char('A' + rand() % ('Z' - 'A'));
	value->next = first;
	value->pred = NULL;
	header->pred = value;
	header = value;
	(*ptr)++;

}

////////_4_////////
void DeleteElement(int* ptr) //удаление элемента в начале списка
{
	elem* value;
	value = header;
	if (header->next == NULL)
	{
		cout << "\nThe list is a empty!\n";
		return;
	}
	header = header->next;
	header->pred = NULL;
	delete value;
	(*ptr)--;
}

////////_5_////////
void DeleteList() //удаление списка
{
	elem* value;
	while (true)
	{
		if (header == NULL)
		{
			cout << "\nThe list was deleted!\n";
			return;
		}
		else
		{
			value = header->next;
			delete header;
			header = value;
		}
	}
}

///////////////////
void PrintList() //вывод списка
{
	elem* value;
	value = header; //устанавливаем начальное значение списка
	if (header == NULL)
	{
		cout << "\nThe list is a empty!\n";
		return;
	}
	else
	{

		int i = 1;
		cout << "~~~~~~~~~~LIST~~~~~~~~~~\n";

		while (value->next != NULL)
		{
			cout << "list[" << i << "]=" << value->data << "\n";
			value = value->next;
			i++;
		}
	}
}

struct elem* MaxFound() //нахождения максимума в списке
{
	elem* value;
	elem* value1;
	value = header; //устанавливаем начальное значение списка
	value1 = header; //устанавливаем начальное значение списка
	if (header == NULL)
	{
		return NULL; //The list is a empty!
	}
	else
	{

		while (value->next != NULL)
		{
			if (value->data > value1->data)
			{
				value1 = value;
				value = value->next;
			}
			else
			{
				value = value->next;
			}

		}
		return  value1;
	}
}


void New_Element(int* ptr)
{

	int pos = -1;
	//Ввод позиции элемента
	cout << "Position of new element:\n";
	while ((pos > (*ptr) + 1) || (pos <= 0))
	{
		cin >> pos;
		if (((pos > (*ptr) + 1) || (pos <= 0))) cout << "Error, try again:\n";
	}


	if (pos == 1)
	{
		NewElement(ptr);
	}
	else
	{
		elem* value;
		elem* neww;
		value = header;

		//Доходим до нужного элемента
		for (int i = 1; i < pos; i++)
		{
			value = value->next;
		}
		neww = new elem;
		neww->data = char('A' + rand() % ('Z' - 'A'));

		neww->pred = value->pred;
		value->pred->next = neww;


		//
		if (pos != (*ptr) + 1)
		{
			neww->next = value;
			value->pred = neww;
		}
		else
		{
			neww->next = NULL;
		}
		(*ptr)++;
	}
}
