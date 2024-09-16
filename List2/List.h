#pragma once
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
class - обычный класс
class<type> - шаблонный класс
--------------------------------------------------------
*/

//############################################################################################################################################
//############################################ Обьявление класса (Class declaration) #########################################################
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

//############################################ Обьявление класса (Class declaration) #########################################################
//############################################################################################################################################