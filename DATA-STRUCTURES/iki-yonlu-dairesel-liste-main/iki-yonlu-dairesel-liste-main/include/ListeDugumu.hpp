

#ifndef LISTEDUGUMU_HPP
#define LISTEDUGUMU_HPP

#include <iostream>

class ListeDugumu
{
private:
    int data;
    ListeDugumu* prev;
    ListeDugumu* next;
    
public:
    ListeDugumu(int data);
    int getData();
    void setData(int data);
    ListeDugumu* getPrev();
    void setPrev(ListeDugumu* prev);
    ListeDugumu* getNext();
    void setNext(ListeDugumu* next);
};

#endif