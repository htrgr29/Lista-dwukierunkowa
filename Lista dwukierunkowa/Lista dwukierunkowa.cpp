// Lista dwukierunkowa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "BiDirectionalList.h"


int main()
{

    //    BiDirectionalList<ListItem<int>>* lista = new BiDirectionalList<ListItem<int>>();
    BiDirectionalList<int>* lista = new BiDirectionalList<int>();
    BiDirectionalList<int>* lista1 = new BiDirectionalList<int>();
    BiDirectionalList<int>* lista2 = new BiDirectionalList<int>();

    lista->insert(4);
    lista->insert(2);
    lista->append(7);

    ofstream out("test.txt", ios::out | ios::binary);
    lista->serialize(out);
    out.close();


    ifstream in("test.txt", ios::in | ios::binary);
    lista1->deserialize(in);
    in.close();

    *lista2 = *lista;

    cout << "lista: ";
    lista->print();
    cout << "lista1: ";
    lista1->print();
    cout << "lista2: ";
    lista2->print();
  
    
    auto tmp = lista->find(2);
    lista->remove(tmp);

    cout << "lista: ";
    lista->print();
    
    tmp.reset();

  
//    BiDirectionalList<int> lista;

}

