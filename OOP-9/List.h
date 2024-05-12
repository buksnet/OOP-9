#pragma once
#include <iostream>
#include "ListExceptions.h"

template <typename T>
struct Node {
	T data;
	Node* next = nullptr;
	Node* prev = nullptr;
};

template <typename T>
class Iter
{
public:
	Node<T>* node;
	Iter();
	Iter(const Iter<T>*);
	~Iter();

	Iter<T>& operator=(const Iter<T>&);
	T& operator*() const;
	Iter& operator+(const int&);
};

template <typename T>
class List {
private:
	int size;
	Node<T>* head;
	Node<T>* tail;
	Iter<T> start;
	Iter<T> end;
public:
	List();
	List(int);
	List(const List<T>&);
	~List();

	Iter<T> first();
	Iter<T> last();

	void push(T);
	void pop();

	List& operator=(const List<T>&);
	T& operator[](int);
	int& operator()();
	List<T> operator*(List<T>&);
};

template <typename T>
List<T>::List() {
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

template <typename T>
List<T>::List(int count) {
	this->size = count;
	Node<T>* new_node = new Node<T>;
	this->head = new_node;
	this->tail = new_node;

	for (int i = 0; i < count; i++) {
		new_node = new Node<T>;
		this->tail->next = new_node;
		new_node->prev = this->tail;
		this->tail = new_node;
	}
	this->start.node = this->head;
	this->end.node = this->tail;
}

template <typename T>
List<T>::List(const List<T>& lst) {
	Node<T>* node = lst.head;
	while (node != nullptr) {
		push(node->data);
		node = node->next;
	}
	this->start.node = this->head;
	this->end.node = this->tail;
	this->size = lst.size;
}

template <typename T>
List<T>::~List() {
	Node<T>* node = this->head;
	while (node != nullptr) {
		this->head = node->next;
		delete node;
		node = this->head;
	}
}

template <typename T>
List<T>& List<T>::operator=(const List& lst) {
	Node<T>* node = lst.head;
	while (node != nullptr) {
		push(node->data);
		node = node->next;
	}
	this->start.node = this->head;
	this->end.node = this->tail;
	this->size = lst.size;
}

template <typename T>
int& List<T>::operator()() {
	return this->size;
}

template <typename T>
T& List<T>::operator[](int index) {
	if ((index >= this->size) || (index < 0)) throw ListIndexException();
	Node<T>* node = this->head;
	for (int i = 0; i < index; i++) {
		node = node->next;
	}
	return node->data;
}

template <typename T>
List<T> List<T>::operator*(List<T>& lst) {
	if (this->size == 0 || lst.size == 0) throw ListEmptyException();
	List<T>* base = *this;
	int new_size = this->size;
	List<T> tmp;
	
	for (int i = 0; i < new_size; i++) {
		tmp.push(base[i] * lst[i]);
	}
	return tmp;
}

template <typename T>
void List<T>::push(T value) {
	Node<T>* new_node = new Node<T>;
	new_node->data = value;
	if (this->size == 0) {
		new_node->next = nullptr;
		new_node->prev = nullptr;
		this->head = new_node;
		this->tail = new_node;
		this->size++;
		this->start.node = head;
		this->end.node = tail;
	}
	else {
		this->tail->next = new_node;
		new_node->prev = this->tail;
		this->tail = new_node;
		this->size++;
		this->end.node = tail;
	}
}

template <typename T>
void List<T>::pop() {
	if (this->size > 0) {
		Node<T>* node = this->tail;
		this->tail = node->prev;
		delete node;
		this->tail->next = nullptr;
		this->size--;
		this->end.node = this->tail;
	}
	else throw ListEmptyException();
}

template <typename T>
Iter<T> List<T>::first() {
	if (this->size <= 0) throw ListEmptyException();
	return this->start;
}

template <typename T>
Iter<T> List<T>::last() {
	if (this->size <= 0) throw ListEmptyException();
	return this.end;
}

template <typename T>
Iter<T>::Iter() {
	this->node = nullptr;
}

template <typename T>
Iter<T>::Iter(const Iter<T>* item) {
	this->node = item->node;
}

template <typename T>
Iter<T>::~Iter() {
	this->node = nullptr;
}

template <typename T>
Iter<T>& Iter<T>::operator=(const Iter<T>& item) {
	this->node = item.node;
	return *this;
}

template <typename T>
T& Iter<T>::operator*() const {
	return this->node->data;
}

template <typename T>
Iter<T>& Iter<T>::operator+(const int& index) {
	for (int i = 0; i < index; i++) {
		this->node = this->node->next;
	}
	return *this;
}
