#include <iostream>
#include "args.h"

using namespace std;

struct Node { //элемент списка
	int x;
	Node *Next, *Prev;

};
 
class List{ //класс для работы со списком
	Node *Head, *Tail;
public:
	List() : Head(NULL), Tail(NULL) {};
	~List();
	void Show();
	void Add(int x);
	int NewHead();
	int NewTail();
};
 
List::~List() { //деструктор
	while (Head) {
		Tail = Head->Next;
		delete Head;
		Head = Tail;
	}
}
 
void List::Add(int n) { //добавляет n коливество элементов списка, сгенерированных случайно
	for (size_t i = 0; i != n; i++) {	
		Node *temp = new Node;
		temp->Next = NULL;
		temp->x = rand();
		
		if (Head != NULL) {
			temp->Prev = Tail;
			Tail->Next = temp;
			Tail = temp;
		} else {
			temp->Prev = NULL;
			Head = Tail = temp;
		}
	}
}
 
void List::Show() { //вывод списка
		Node *temp = Head;
		while (temp != NULL) {
			cout << temp->x << " ";
			temp = temp->Next;
		}

		cout << "\n";
}

int List::NewHead() { //сдвигает начало на один элемент	
	if (Head != NULL) {	
		Node *temp = Head;
		int x = temp->x;
		if (Head != Tail) {		
			temp = temp->Next;		
			delete Head;
			temp->Prev = NULL;
			Head = temp;
			return x;		
		} else {
			delete Head;
			Head = NULL;
			Tail = NULL;
			return x;
		}
	}
	return 0;
}

int List::NewTail() { //сдвигает конец на один элемент
	if (Tail != NULL) {	
		Node *temp = Tail;
		int x = temp->x;
		if (Tail != Head) {
			temp = temp->Prev;
			delete Tail;
			temp->Next = NULL;
			Tail = temp;
			return x;	
		} else {
			delete Head;
			Head = NULL;
			Tail = NULL;
			return x;
		}
	}
	return 0;
}
