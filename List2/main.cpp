#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;
public:
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
			cout << "ItDectructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator --()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		//								comperisson operators:
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		
		//								deference operators:
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverceIterator
	{
		Element* Temp;
	public:
		ReverceIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "RItConstructot:\t" << this << endl;
		}
		~ReverceIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}
		//					increment//decrement
		ReverceIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverceIterator operator++(int)
		{
			ReverceIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverceIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverceIterator operator--(int)
		{
			ReverceIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		//							comparisson operators

		bool operator==(const ReverceIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverceIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//					dereferencre operator
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ReverceIterator rbegin()
	{
		return Tail;
	}
	ReverceIterator rend()
	{
		return nullptr;
	}
	//														constructors:

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;

	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDectructor:\t" << this << endl;
	}

	//												adding elements
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//Element* New = new Element(Data);	//1)создаем новый элемент
			//New->pNext = Head;
			//Head->pPrev = New;
			//Head = New;
			
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//Element* New = new Element(Data);
			//New->pPrev = Tail;
			//Tail->pNext = New;
			//Tail = New;

			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);

		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);

		size++;
	}
	//										remove elements

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		if (Index == size - 1)pop_back();

		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}

		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;

		delete Temp;

		size--;
	}

	//										methods

	void print()const
	{
		cout << delimiter << endl;
		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout
				<< Temp->pPrev << tab
				<< Temp << tab
				<< Temp->Data << tab
				<< Temp->pNext << endl;

			cout << "Tail:\t" << Tail << endl;
			cout << "Колличество элементов списка: " << size << endl;
			cout << delimiter << endl;
	}
	void reverce_print()const
	{
		cout << delimiter << endl;
		cout << "Tail:\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;

		cout << "Head:\t" << Head << endl;
		cout << "Колличество элементов списка: " << size << endl;
		cout << delimiter << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
	
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.reverce_print();
	//for (int i = 0; i < 100; i++)list.pop_back();
	//list.reverce_print();

	int index;
	int value;
	cout << "Введите индекс добовляемого элемента: "; cin >> index;
	cout << "Введите значение добовляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverce_print();
	for (int i : list)cout << i << tab; cout << endl;
	for (List::ReverceIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}