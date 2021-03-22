#include <iostream>

using namespace std;

typedef char Tinfo;

struct Tnode {
	Tinfo info;
	Tnode* next;
};

//предусловие: список L не пуст, p >= 0, p <= количества узлов
//постусловие: получение указателя на узел в позиции p
Tnode* findeNode(Tnode* L, int p) {
	int i = 0;
	Tnode* q = L;
	while (q != NULL && i < p - 1)
	{
		i++;
		q = q->next;
	}
	return q;
}

//предусловие: списки L1 и L2 не пусты
//постусловие: проверка списков L1 и L2 на полную эквивалентность
void equalityTest(Tnode*& L1, Tnode*& L2) {
	Tnode* l1 = L1;
	Tnode* l2 = L2;
	if (sizeof(L1) != sizeof(L2))
	{
		cout << "the lists don't match" << endl;
	}
	else
	{
		while (l1 != NULL && l2 != NULL)
		{
			if (l1->info == l2->info)
			{
				l1 = l1->next;
				l2 = l2->next;
			}
			else
			{
				cout << "the lists don't match" << endl;
				break;
			}
			if (l1 == NULL && l2 == NULL)
			{
				cout << "the lists match" << endl;
			}
		}
	}
}

//предусловие: список L не пуст
//постусловие: включает узел перед первым узлом
void insertBeforeFirstNode(Tnode*& L, Tinfo d) {

	Tnode* q = new Tnode;
	q->next = L;
	L = q;
	q->info = d;
}

//предусловие: списки L1 и L2 не пусты, p >= 0, p <= количества узлов
//постусловие: вставляет последний узел списка L2  в позицию p списка L1
void insertingLastItem(Tnode*& L1, Tnode*& L2, int p) {
	if (L1 == NULL || L2 == NULL)
	{
		return;
	}

	Tnode* q1 = L2;
	while (q1->next != NULL)
	{
		q1 = q1->next;
	}

	Tnode* q = new Tnode;
	q->info = q1->info;
	q->next = NULL;

	if (p != 0)
	{
		q1 = findeNode(L1, p);

		if (q1->next != NULL)
		{
			q->next = q1->next;
			q1->next = q;
		}
		else
		{
			q1->next = q;
		}
	}
	else
	{
		insertBeforeFirstNode(L1, q->info);
	}
}

//предусловие: список L2 не пуст
//постусловие: удаляет все узлы, содержащие цифры
void deletingDigitalNodes(Tnode*& L2) {
	Tnode* q = L2;
	Tnode* q1;
	while (q->next != NULL)
	{
		if (q == L2 && (int)q->info > 47 && (int)q->info < 58)
		{
			Tnode* q1 = L2;
			L2 = L2->next;
			delete q1;
			q = L2;
		}
		else if ((int)q->info > 47 && (int)q->info < 58)
		{
			q1 = q->next;
			q->info = q1->info;
			q->next = q1->next;
			delete q1;
		}
		else if ((int)q->next->info > 47 && (int)q->next->info < 58 && q->next->next == NULL)
		{
			q->next = NULL;
		}
		else
		{
			q = q->next;
		}
	}
	if ((int)L2->info > 47 && (int)L2->info < 58)
	{
		L2 = NULL;
	}
}

//предусловие: список L пуст
//постусловие: создает список из n элементов, включая узлы перед первым элементом
void createList(Tnode*& L, int n) {
	Tnode* q;
	for (int i = 0; i < n; i++)
	{
		if (L == NULL)
		{
			q = new Tnode;
			cin >> q->info;
			q->next = NULL;
			L = q;

		}
		else
		{
			Tinfo d;
			cin >> d;
			insertBeforeFirstNode(L, d);
		}
	}
}

//предусловие: список L не пуст
//постусловие: вывод всех элементов списка
void outList(Tnode* L) {
	Tnode* node = L;
	cout << "current list: ";
	while (node != NULL)
	{
		cout << node->info << " ";
		node = node->next;
	}
	cout << endl;
}

int main()
{
	Tnode* L1 = NULL;
	int n;
	cout << "enter the size of the first list: ";
	cin >> n;
	createList(L1, n);
	outList(L1);

	cout << "enter the size of the second list: ";
	cin >> n;
	Tnode* L2 = NULL;
	createList(L2, n);
	outList(L2);

	equalityTest(L1, L2);

	cout << "enter the position number to which you want to insert the element: ";
	cin >> n;
	insertingLastItem(L1, L2, n);
	outList(L1);

	deletingDigitalNodes(L2);
	outList(L2);
}