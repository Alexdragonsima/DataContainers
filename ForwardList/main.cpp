#include<iostream>
using namespace std;

#define tab	"\t"

class Element
{
protected:
	int Data;		//значение элемента
	Element* pNext;	//указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "Edestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;	//когда список пуст его голова указывает на ноль
		cout << "Lconstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Element* New = new Element(Data);

		//2) вкл новый элемент в список
		New->pNext = Head;

		//3) переводим голову на новый элемент
		Head = New;
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

		//2)создаем нновый элемент
		Element* New = new Element(Data);

		//3)добавляем элемент в конец
		Temp->pNext = New;
	}
	
	//		methods:
	void print()const
	{
		cout << "Head:/t" << Head << endl;
		Element* Temp = Head;	//Temp= это итератор
		//итератор- эьо указатель. при помощи которого можно перебирать элементы структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//переход на следующий элемен
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
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
}