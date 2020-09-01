#include <iostream>
#include "args.hpp"

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
	void Show(bool asc);
	void Add(int x);
	Node* New_Head();
	Node* New_Tail();
	friend void* Count_bits(void* args);
	
};
 
List::~List() { //деструктор
	while (Head) {
		Tail = Head->Next;
		delete Head;
		Head = Tail;
	}
}
 
void List::Add(int x) { //добавляет новый элемент списка
	Node *temp = new Node;
	temp->Next = NULL;
	temp->x = x;
 
	if (Head != NULL) {
		temp->Prev = Tail;
		Tail->Next = temp;
		Tail = temp;
	} else {
		temp->Prev = NULL;
		Head = Tail = temp;
	}
}
 
void List::Show(bool asc) { //вывод списка
	//С НАЧАЛА
	if(asc){
		Node *temp = Head;
		while (temp != NULL) {
			cout << temp->x << " ";
			temp = temp->Next;
		}
		cout << "\n";
	} else {
	//С КОНЦА
		Node *temp=Tail;
		while (temp != NULL) {
			cout << temp->x << " ";
			temp = temp->Prev;
		}
		cout << "\n";
	}
}

Node* List::New_Head() { //сдвигает начало на один элемент	
	Node *temp = Head;
	if (temp != NULL && temp->Next != NULL && temp->Next != Tail) {		
		temp = temp->Next;
		delete Head;
		temp->Prev = NULL;
		Head = temp;
		return Head;		
	} else {
		Head != Tail ? Tail->Prev = NULL : Tail = NULL;
		delete Head;
		Head = NULL;
	}
	return NULL;
}

Node* List::New_Tail() { //сдвигает конец на один элемент
	Node *temp = Tail;
	if (temp != NULL && temp->Prev != NULL && temp->Prev != Head) {	
		temp = temp->Prev;
		delete Tail;
		temp->Next = NULL;
		Tail = temp;
		return Tail;	
	} else if (Head != Tail) {
		delete Tail;
	}
	return NULL;
}
