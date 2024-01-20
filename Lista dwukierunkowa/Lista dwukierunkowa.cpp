// Lista dwukierunkowa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "BiDirectionalList.h"


int main()
{

    //    BiDirectionalList<ListItem<int>>* lista = new BiDirectionalList<ListItem<int>>();
    BiDirectionalList<int>* lista = new BiDirectionalList<int>();
    BiDirectionalList<int>* lista1 = new BiDirectionalList<int>();
    BiDirectionalList<int>* lista2 = new BiDirectionalList<int>();

    lista->insert(7);
    lista->insert(2);
    lista->insert(4);

    ofstream out("test.txt", ios::out | ios::binary);
    lista->serialize(out);
    out.close();


    ifstream in("test.txt", ios::in | ios::binary);
    lista1->deserialize(in);
    in.close();

    *lista2 = *lista;

    auto tmp = lista->find(2);
    lista->remove(tmp);

    tmp.reset();

//    BiDirectionalList<int> lista;

    std::cout << "Hello World!\n";
}

