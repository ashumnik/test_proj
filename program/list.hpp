#include <iostream>
#include <unistd.h>
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
	if (temp->Next == Tail) {return 0;} //костыль (не знаю как по-другому) (чтобы разные потоки не обрабатывали один элемент)
	if (temp != NULL && temp->Next != NULL) {
		temp = temp->Next;
		delete Head;
		temp->Prev = NULL;
		Head = temp;
		return temp;
	} else if (Tail == Head) {
		this->~List();			
	}
	return 0;
}

Node* List::New_Tail() { //сдвигает конец на один элемент
	Node *temp = Tail;
	if (temp->Prev == Head || temp == Head || temp->Prev->Prev == Head) {return 0;} //костыль
	if (temp != NULL && temp->Prev != NULL) {
		temp = temp->Prev;
        sleep(1);
		delete Tail;
		temp->Next = NULL;
		Tail = temp;
		return temp;
	} else if (Tail == Head) {
		return 0;	
	}
	return 0;
}
