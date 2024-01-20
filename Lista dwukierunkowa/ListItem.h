#pragma once

#include <iostream>

#include "BiDirectionalList.h"

using namespace std;

template<typename T>
class ListItem : public enable_shared_from_this<ListItem<T>>
{
public:
	shared_ptr<ListItem<T>> prev, next;
	T data;
	ListItem();
	ListItem(T in);
	~ListItem();
    virtual shared_ptr<ListItem<T>> first();
    virtual shared_ptr<ListItem<T>> last();
    virtual void insert(shared_ptr<ListItem<T>> item);
    virtual void append(shared_ptr<ListItem<T>> item);
    //virtual void remove();
    virtual shared_ptr<ListItem<T>> find(T key);
};



template<typename T>
ListItem<T>::ListItem()
{
	prev = nullptr;
	next = nullptr;
}

template<typename T>
inline ListItem<T>::ListItem(T in)
{
	prev = nullptr;
	next = nullptr;
	data = in;
}

template<typename T>
ListItem<T>::~ListItem()
{
	if (prev) prev->next = next;
	if (next) next->prev = prev;
}

template<typename T>
shared_ptr<ListItem<T>> ListItem<T>::first()
{
	shared_ptr<ListItem<T>> tmp = this->shared_from_this();
	while (tmp->prev) { tmp = tmp->prev; };
	return tmp;
}

template<typename T>
shared_ptr<ListItem<T>> ListItem<T>::last()
{
	shared_ptr<ListItem<T>> tmp = this->shared_from_this();
	while (tmp->next) { tmp = tmp->next; };
	return tmp;
}


template<typename T>
void ListItem<T>::insert(shared_ptr<ListItem<T>> item)
{
	shared_ptr<ListItem<T>> firstItem = item->first();
	shared_ptr<ListItem<T>> lastItem = item->last();
	lastItem->next = this->shared_from_this();
	firstItem->prev = prev;
	if (prev) prev->next = firstItem;
	prev = lastItem;
}

template<typename T>
void ListItem<T>::append(shared_ptr<ListItem<T>> item)
{
	shared_ptr<ListItem<T>> firstItem = item->first();
	shared_ptr<ListItem<T>> lastItem = item->last();
	firstItem->prev = this->shared_from_this();
	lastItem->next = next;
	if (next) next->prev = lastItem;
	next = firstItem;
}

//template<typename T>
//void ListItem<T>::remove()
//{
//	delete this;
//}

template<typename T>
shared_ptr<ListItem<T>> ListItem<T>::find(T key)
{
	shared_ptr<ListItem> tmp = first();
	while (tmp->next) {
		if (tmp->data == key) return tmp;
		tmp = tmp->next;
	};
	return nullptr;
}



