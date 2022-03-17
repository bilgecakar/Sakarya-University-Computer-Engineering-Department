

#ifndef LISTE_HPP
#define LISTE_HPP

#include "ListeDugumu.hpp"

class Liste
{
public:
    Liste();
    ~Liste();
    ListeDugumu* getHead();
    void setHead(ListeDugumu* head);
    ListeDugumu* getTail();
    void setTail(ListeDugumu* tail);
    void insertToBeginning(int number);
    void insert(int number);
    void printList();
    static int obebHesapla(int x, int y);
    static int modHesapla(int x, int y);
    static int getMax(int x, int y);

private:
    ListeDugumu* head;
    ListeDugumu* tail;
    int enBuyukOBEB;
};


#endif