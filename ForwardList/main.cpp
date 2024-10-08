﻿#include<iostream>
using std:: cout;
using std:: cin;
using std:: endl;


#define tab	"\t"

class Element
{
protected:
	int Data;		//значение элемента
	Element* pNext;	//указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "Edestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	//																	Constructors:
	ForwardList()
	{
		Head = nullptr;	//когда список пуст его голова указывает на ноль
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//initializer_list-Это контейнер.
		//Контенер-организует хранение других обьектов в памяти
		//у любого контейнера в обязательном порядке есть как миниум два метода 
		//begin() - возвращает итератор на начало контейнера
		//end() - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		//Initializer list всякий раз неявно создается каждый раз когда мы перечисляем значения через запятую
	}

	ForwardList(const ForwardList& other):ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "lCopyconstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//														operators:

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		revers();
		cout << "lCopyAssignment:" << this << endl;
		return *this;
	}

	//														Adding elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		//2) вкл новый элемент в список
		//3) переводим голову на новый элемент

		Head = new Element(Data, Head);

		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1)доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		////2)создаем нновый элемент
		//Element* New = new Element(Data);
		////3)добавляем элемент в конец
		//Temp->pNext = New;

		Temp->pNext = new Element(Data);

		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0)return push_front(Data);
		//1) Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		////2) Создаем новый элемент
		//Element* New = new Element(Data);
		////3) Включаем элемент в список
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;

		Temp->pNext = new Element(Data, Temp->pNext);

		size++;
	}

	//														Removing elements

	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head;	//1) Запоминаем адресс удаляемого элемента
		Head = Head->pNext;		//2) Смещаем голову на следующий элемент( Исключаем элемент из списка)
		delete erased;			//3) Удаляем элемент из памяти
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr||Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента  спи
		// ска:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		
		//2) Удаляем последний элемент из памяти
		delete Temp->pNext;

		//3) Зануляем указатель на последний элемент
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		//1) доходим до элемента перед удаляемым
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//2) Запоминаем адрес удаляемого элемента
		Element* erased = Temp->pNext;

		//3) исключаем удаляемый элемент из списка
		Temp->pNext = Temp->pNext->pNext;

		//4) Удаляем элемент из памяти
		delete erased;

		size--;
	}
	
	//		methods:
	void revers()
	{
		ForwardList	buffer;
		while (Head)
		{
			buffer.push_front(Head-> Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}

	void print()const
	{
		cout << "Head:/t" << Head << endl;
		/*Element* Temp = Head;	//Temp= это итератор
		//итератор- эьо указатель. при помощи которого можно перебирать элементы структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//переход на следующий элемен
		}*/
		for(Element* Temp =Head;Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
		cout << "общее Количество элементов списка: " << Element::count << endl;
		//cout << "общее Количество элементов списка: " << Head->count << endl;
	}
};

void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i];
	}
	cout << endl;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARREY
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "введите колво элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.print();
	//list.pop_back();
	//list.print();

	int index=0;
	int value;
	cout << "Введите значение нового элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "введите колво элементов: "; cin >> n;


	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	cout << "List filled" << endl;
	//list.print();

	cout << "Making copy" << endl;
	ForwardList list2 = list;// copyConstructor
	//ForwardList list2;
	//list2 = list;
	//list2.print();
	cout << "Copy DONE" << endl;
#endif // PERFORMANCE_CHECK

#ifdef RANGE_BASED_FOR_ARREY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range_base for

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;

	Print(arr);
#endif // RANGE_BASED_FOR_ARREY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

}
