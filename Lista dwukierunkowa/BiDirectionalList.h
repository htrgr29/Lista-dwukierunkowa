#pragma once

#include <iostream>
#include <fstream>
#include "ListItem.h"

using namespace std;

template<typename T>
class BiDirectionalList // : public enable_shared_from_this<BiDirectionalList<T>>
{

public:
	shared_ptr<ListItem<T>> first, last;
	BiDirectionalList();
	BiDirectionalList(const BiDirectionalList<T>& obj);
	BiDirectionalList(BiDirectionalList<T>&& obj);
	~BiDirectionalList();
	BiDirectionalList<T>& operator=(BiDirectionalList<T>&& obj);
	BiDirectionalList<T>& operator=(const BiDirectionalList<T>& obj);
	virtual void insert(T item);
	virtual void append(T item);
	virtual void remove(shared_ptr<ListItem<T>> current);
	virtual shared_ptr<ListItem<T>> find(T key);
	virtual void serialize(ofstream& out);
	virtual void deserialize(ifstream& in);
	virtual void print();
};




template<typename T>
BiDirectionalList<T>::BiDirectionalList()
{
	first = nullptr;
	last = nullptr;
}


template<typename T>
BiDirectionalList<T>::BiDirectionalList(const BiDirectionalList<T>& obj)
{
	first = nullptr;
	last = nullptr;

	auto tmp = obj.first;

	while (tmp) {
		this->append(tmp->data);
		tmp = tmp->next;
	}
}


template<typename T>
BiDirectionalList<T>::BiDirectionalList(BiDirectionalList<T>&& obj)
{
	first = obj.first;
	last = obj.last;
	obj.first = nullptr;
	obj.last = nullptr;
}


template<typename T>
BiDirectionalList<T>& BiDirectionalList<T>::operator=(const BiDirectionalList<T>& obj)
{
	if (this != &obj) {


		while (first) {
			auto tmp = first->next;
			first.reset();
			first = tmp;
		}

		first = nullptr;
		last = nullptr;

		auto tmp = obj.first;

		while (tmp) {
			this->append(tmp->data);
			tmp = tmp->next;
		}
	}
	return *this;
}


template<typename T>
BiDirectionalList<T>& BiDirectionalList<T>::operator=(BiDirectionalList<T>&& obj)
{
	if (this != &obj) {

		while (first) {
			auto tmp = first->next;
			first.reset();
			first = tmp;
		}

		first = obj.first;
		last = obj.last;
		obj.first = nullptr;
		obj.last = nullptr;
	}
	return *this;
}


template<typename T>
BiDirectionalList<T>::~BiDirectionalList<T>()
{
	while (first) {
		auto tmp = first->next;
		first.reset();
		first = tmp;
	}

	first = nullptr;
	last = nullptr;

}


template<typename T>
void BiDirectionalList<T>::insert(T item)
{
	shared_ptr<ListItem<T>> tmp(new ListItem<T>(item));

	tmp->next = first;
	if (first) first->prev = tmp;
	first = tmp;

	if (!last) last = tmp;

}

template<typename T>
void BiDirectionalList<T>::append(T item)
{

	shared_ptr<ListItem<T>> tmp(new ListItem<T>(item));

	tmp->prev = last;
	if (last) last->next = tmp;
	last = tmp;

	if (!first) first = tmp;

}

template<typename T>
void BiDirectionalList<T>::remove(shared_ptr<ListItem<T>> current)
{
	if (current) {
		if (current->next) current->next->prev = current->prev;
		else last = current->prev;
		if (current->prev) current->prev->next = current->next;
		else first = current->next;
		current->prev = nullptr;
		current->next = nullptr;
		current.reset();
	};
}

template<typename T>
shared_ptr<ListItem<T>> BiDirectionalList<T>::find(T key)
{

	auto tmp = first;
	while (tmp) {
		if (tmp->data == key) return tmp;
		tmp = tmp->next;
	};
	return nullptr;
}


template<typename T>
void BiDirectionalList<T>::serialize(ofstream& out)
{

	auto tmp = first;
	while (tmp) {
		out.write((char*)&(tmp->data), sizeof(tmp->data));
		tmp = tmp->next;
	};
}

template<typename T>
void BiDirectionalList<T>::deserialize(ifstream& in)
{

	while (first) {
		auto tmp = first->next;
		first.reset();
		first = tmp;
	}

	first = nullptr;
	last = nullptr;

	T data;
	while (in.read((char*)&data, sizeof(data))) {
		append(data);
	};
}

template<typename T>
inline void BiDirectionalList<T>::print()
{
	//while (first) {
	//	auto tmp = first->next;
	//	cout << first->data << " ";
	//	first.reset();
	//	first = tmp;
	//}

	auto tmp = first;
	while (tmp) {
		cout << tmp->data << " ";
		tmp = tmp->next;
	}


	cout << "\n";
}
