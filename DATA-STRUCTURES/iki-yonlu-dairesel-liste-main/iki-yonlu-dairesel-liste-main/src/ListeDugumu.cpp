
#include "ListeDugumu.hpp"

ListeDugumu::ListeDugumu(int data)
{
    this->data = data;
    this->prev = NULL;
    this->next = NULL;
}

int ListeDugumu::getData()
{
    return data;
}

void ListeDugumu::setData(int data)
{
    this->data = data;
}

ListeDugumu* ListeDugumu::getPrev()
{
    return prev;
}

void ListeDugumu::setPrev(ListeDugumu* prev)
{
    this->prev = prev;
}

ListeDugumu* ListeDugumu::getNext()
{
    return next;
}

void ListeDugumu::setNext(ListeDugumu* next)
{
    this->next = next;
}