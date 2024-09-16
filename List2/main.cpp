#include"List.cpp"

//#define BASE_CHECK
//#define ITERATORS_CHECK

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

	List<std::string>s_list = { "Хорошо","живет","на","свете","НоутБук" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}