#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n"

/*
--------------------------------------------------------
class - ������� �����
class<type> - ��������� �����
--------------------------------------------------------
*/

//############################################################################################################################################
//############################################ ���������� ������ (Class declaration) #########################################################
//############################################################################################################################################

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;

#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;

#endif // DEBUG
		}
		friend class List;
	}*Head, * Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		//								comperisson operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		//								deference operators:
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		//							incremento/decremento
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);

	};
	class ConstReverceIterator :public ConstBaseIterator
	{
	public:
		ConstReverceIterator(Element* Temp = nullptr);
		~ConstReverceIterator();
		//					increment//decrement
		ConstReverceIterator& operator++();
		ConstReverceIterator operator++(int);
		ConstReverceIterator& operator--();
		ConstReverceIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverceIterator :public ConstReverceIterator
	{
	public:
		ReverceIterator(Element* Temp = nullptr) :ConstReverceIterator(Temp) {}
		~ReverceIterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	ConstIterator begin()const;
	ConstIterator end()const;

	Iterator begin();
	Iterator end();

	ConstReverceIterator rbegin()const;
	ConstReverceIterator rend()const;

	ReverceIterator rbegin();
	ReverceIterator rend();

	//														constructors:

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//														operators:

	List<T>& operator=(const List<T>& other);

	//														adding elements:

	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//														remove elements:

	void pop_front();
	void pop_back();
	void erase(int Index);

	//														methods:

	void print()const;
	void reverce_print()const;
};

//############################################ ���������� ������ (Class declaration) #########################################################
//############################################################################################################################################
//  
//############################################################################################################################################
//############################################               ����������� ������      #########################################################

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////                const base iterator				///////////////////////////


//								comperisson operators:
template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

//								deference operators:
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

// /////////////////////////////////////                const iterator				///////////////////////////


template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDectructor:\t" << this << endl;
#endif // DEBUG
}
//							incremento/decremento
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>:: ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//////////////////////////						constReverceIterator

template<typename T>List<T>::ConstReverceIterator::ConstReverceIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructot:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstReverceIterator::~ConstReverceIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}
//					increment//decrement
template<typename T>typename List<T>::ConstReverceIterator& List<T>::ConstReverceIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverceIterator List<T>::ConstReverceIterator::operator++(int)
{
	ConstReverceIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverceIterator& List<T>::ConstReverceIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverceIterator List<T>::ConstReverceIterator::operator--(int)
{
	ConstReverceIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}


// /////////////////////////////////////                const iterator				///////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                  List members                ///////////////////////////

template<typename T>typename List<T>:: ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template<typename T>typename List<T>::ConstReverceIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverceIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>typename List<T>::ReverceIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverceIterator List<T>::rend()
{
	return nullptr;
}
//														constructors:

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;

}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}
template<typename T> List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "CopyConstructor:" << this << endl;
}
template<typename T> List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDectructor:\t" << this << endl;
}

//														operators:
template<typename T> List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_back();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

//														adding elements:
template<typename T> void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		//Element* New = new Element(Data);	//1)������� ����� �������
		//New->pNext = Head;
		//Head->pPrev = New;
		//Head = New;

		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template<typename T>void List<T>:: push_back(T Data)
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
template<typename T>void List<T>::insert(T Data, int Index)
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
//														remove elements:

template<typename T>void List<T>::pop_front()
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
template<typename T>void List<T>::pop_back()
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
template<typename T>void List<T>::erase(int Index)
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

//														methods:

template<typename T>void List<T>::print()const
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
	cout << "����������� ��������� ������: " << size << endl;
	cout << delimiter << endl;
}
template<typename T>void List<T>::reverce_print()const
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
	cout << "����������� ��������� ������: " << size << endl;
	cout << delimiter << endl;
}
//////////////////////////////////////                  List members                //////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;	//CopyConstructor
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
template<typename T>void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}

//############################################ ����� ����������� ������				 #########################################################
//############################################################################################################################################
//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
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
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverce_print();
	for (int i : list)cout << i << tab; cout << endl;
	for (List::ReverceIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	//list3.print();
	//list3.reverce_print();

	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list = { 2.7,3.14,5.4,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string>s_list = { "������","�����","��","�����","�������" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}