#include <iostream> 

using namespace std;

//lista w reprezentacji tablicowej

class ArrayList
{
private:
	int* elems;					//tablica przechowujaca elementy listy
	int first_elem;					//pozycja pierwszego elementu
	int last_elem;    				//pozycja ostatniego elementu
	int list_capacity;				//maksymalny rozmiar tablicy
	int list_size;					//liczba elementów w tablicy

public:
	ArrayList(int c);			                //c - maksymalny rozmiar tablicy, konstruktor
	bool empty();				//zwraca prawdę jeśli lista pusta, fałsz w przeciwnym przypadku
	bool full();				//zwraca prawdę jeśli lista jest pełna, fałsz w przeciwnym przypadku
	int size();				         //zwraca wielkość listy (liczbę elementów w liście)
	int capacity();				//zwraca pojemnośc listy
	int first();  				//zwraca pozycję pierwszego elementu
	int last();   				//zwraca pozycję ostatniego elementu
	int next(int p);			//zwraca pozycję elementu następnego za p
	int prev(int p);			//zwraca pozycję elementu poprzedzającego p
	int retrieve(int p); 			//zwraca element z pozycji p, retrieve - pobierac, odnalezc, odszukac
	int locate(int x);  			//zwraca pozycję pierwszego wystąpienia elementu x, -1 jeśli x nie występuje, wyszukiwanie liniowe, linear search
	void insert(int p, int x); 		//wstawia na pozycję p element x
	void append(int x);			//wstawia x za ostatnim elementem listy
	void del(int p);     		 	//usuwa element z pozycji p
	void clear();				//usuwa całą listę
	void resize();             //zwiększa pojemnosc listy o 1/2 aktualnej pojemnosci
	void delX(int x);         //usuwa pierwsze wystąpienie elementu x
	void delAllX(int x);      //usuwa wszystkie wystapienia elementu x
	bool concat(ArrayList& ll); // dodaje listę l2 na końcu listy, zwraca prawdę jeśli złączenie powiodło się, fałsz jeśli nie jest możliwe(czyli w przypadku braku miejsca w liście)
	friend ostream& operator<<(ostream& out, ArrayList& l); //wypisuje elementy listy
};

ArrayList::ArrayList(int c) 
{
	elems = new int[c];
	first_elem = 0;
	last_elem = -1; //-1 mowi, ze lista jest pusta
	list_capacity = c;
	list_size = 0;
}

bool ArrayList::empty() 
{
	/**if (last_elem == -1) 
	{
		return true;
	}
	else
	{
		return false;
	}**/

	//drugi sposob zapisu

	if (last_elem == -1)
		return true;
	return false;
}

bool ArrayList::full()
{
	/**if (list_size >= list_capacity)
	{
		return true;
	}
	else
	{
		return false;
	}**/

	if (list_size == list_capacity)
		return true;
	return false;
}

int ArrayList::size()
{
	return list_size;
}

int ArrayList::capacity()
{
	return list_capacity;
}

int ArrayList::first()
{
	/**if (empty())
	{
		cout << "Brak elementow w liscie!" << endl;
	}
	else
	{
		return first_elem;
	}**/

	if (!empty())
		return first_elem;
	return NULL;
}

int ArrayList::last()
{
	/**if (empty())
	{
		cout << "Brak elemetow w liscie!" << endl;
	}
	else
	{
		return last_elem;
	}**/

	if (!empty())
		return last_elem;
	return NULL;
}

int ArrayList::next(int p)
{
	/**if (p < list_size - 1)
	{
		return p + 1;
	}
	else
	{
		cout << "Nie ma nastepnego elementu w liscie!" << endl;
	}**/

	if (p < last_elem)
		return p + 1;
	return NULL;
}

int ArrayList::prev(int p)
{
	/**if (p > first_elem)
	{
		return p - 1;
	}
	else
	{
		cout << "Nie ma poprzedniego elementu w liscie!" << endl;
	}**/

	if (p > first_elem)
		return p - 1;
	return NULL;
}

int ArrayList::retrieve(int p)
{
	/**if (p >= first_elem && p <= last_elem)
	{
		return elems[p];
	}
	else
	{
		cout << "Elementu nie ma w liscie!" << endl;
	}**/

	if ((p >= first_elem) && (p <= last_elem))
		return elems[p];
	return NULL;
}

int ArrayList::locate(int x)
{
	for (int i = first_elem; i <= last_elem; i++) //wyszukiwanie liniowe
	{
		if (elems[i] == x)
		{
			return i;
		}
	}
	return -1;
}

void ArrayList::insert(int p, int x)
{
	/**if (!full()) //jesli jest niepelna
	{
		for (int i = last_elem; i >= p; i--) //tak jest szybciej niz jakbysmy zaczeli od first_elem
		{
			elems[i + 1] = elems[i];
		}
		elems[p] = x;
		list_size++;
		last_elem++;
	}
	else
	{
		//modyfikacja metody insert, jesli lista jest pelna to zwiekszamy pojemnosc listy za pomoca metody resize()
		//cout << "Lista jest pelna!" << endl;
		resize();
		for (int i = last_elem; i >= p; i--) //tak jest szybciej niz jakbysmy zaczeli od first_elem
		{
			elems[i + 1] = elems[i];
		}
		elems[p] = x;
		list_size++;
		last_elem++;
	}**/

	if (full())
		resize();

	for (int i = last_elem; i >= p; i--) //tak jest szybciej niz jakbysmy zaczeli od first_elem
	{
		elems[i + 1] = elems[i];
	}

	//sposob
	/**for (int i = p; i <= last_elem; i++)
	{
		elems[i + 1] = elems[i];
	}**/

	elems[p] = x;
	list_size++;
	last_elem++;
}

void ArrayList::append(int x)
{
	/**if (!full())
	{
		elems[last_elem + 1] = x;
		list_size++;
		last_elem++;
	}
	else
	{
		cout << "Lista jest pelna!" << endl;
	}**/

	if (!full())
	{
		elems[last_elem + 1] = x;
		list_size++;
		last_elem++;
	}
	else
	{
		return;
	}
}

void ArrayList::del(int p)
{
	if (!empty()) //jesli lista jest niepusta
	{
		if (p >= first_elem && p <= last_elem)
		{
			for (int i = p; i <= last_elem; i++) 
			{
				elems[i] = elems[i + 1];
			}
			list_size--;
			last_elem--;
		}
		else
		{
			//cout<<"Pozycja nie istnieje!" << endl;
			return;
		}
	}
	else
	{
		//cout << "Lista jest pusta!" << endl;
		return;
	}
}

void ArrayList::clear()
{
	if (!empty()) //jesli lista jest niepusta
	{
		last_elem = -1;
		list_size = 0;
	}
	else
	{
		//cout << "Lista jest pusta!" << endl;
		return;
	}
}

void ArrayList::resize()
{
	list_capacity = int(1.5 * list_capacity); //swiadomie ucinam czesc ulamkowa
}

void ArrayList::delX(int x)
{
	int a;
	a = locate(x); //a-pozycja x w liscie
	if (a != -1)
	{
		del(a);
	}
	else
	{
		//cout << "Elementu nie ma w liście!" << endl;
		return;
	}
}

void ArrayList::delAllX(int x) //usuwa wszystkie wystapienia elementu x
{
	int b;
	b = locate(x);
	while (b != -1)
	{
		del(b);
		b = locate(x);
	}
}

bool ArrayList::concat(ArrayList& ll)
{
	if (full()) //jesli lista jest pelna
	{
		return false;
	}
	else if ((list_capacity - list_size) < ll.list_size) //jesli w liscie jest za malo miejsca
	{
		return false;
	}
	else
	{
		int temp = ll.first_elem;
		//for (int i = (last_elem + 1); i < list_size + ll.list_size; i++)
		//{
		//	elems[i] = ll.elems[temp];
		//	temp++;
		//}
		while (temp != ll.last_elem+1) 
		{
			append(ll.elems[temp]);
			temp++;
		}
		return true;
	}
}

ostream& operator<<(ostream& out, ArrayList& l)
{
	int temp = l.first_elem;
	while (temp != l.last_elem+1)
	{
		cout << l.elems[temp] << " ";
		temp++;
	}
	return out;
}

int main() 
{
	//ArrayList lista=ArrayList(20); //dwie metody sa
	ArrayList lista(20);

	lista.insert(0, 5);
	lista.insert(1, 6);
	lista.insert(2, 7);
	lista.insert(3, 8);
	lista.insert(4, 9);
	lista.insert(5, 10);
	cout << lista << endl;

	lista.append(12);
	cout << lista << endl;

//	lista.delX(6);
//	cout << lista << endl;

//	lista.clear();
//	cout << lista<<endl;

    //tworze druga liste
	ArrayList lista2(15);

	lista2.append(1);
	lista2.append(2);
	lista2.append(3);
	lista2.append(4);
	lista2.append(5);
	cout << lista2 << endl;
	
	lista.concat(lista2);
	cout << lista << endl;


	return 0;
}