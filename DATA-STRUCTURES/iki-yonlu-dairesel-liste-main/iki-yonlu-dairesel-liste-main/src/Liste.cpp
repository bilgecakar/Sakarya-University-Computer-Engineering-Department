
#include "Liste.hpp"
using namespace std;

//OBEB Hesaplama
int Liste::obebHesapla(int x, int y)
{
    if(x == 0 || y == 0)
        return 0;

    while(y != 0)
    {
        int tmp = x;
        x = y;
        y = tmp%y;
    }

    return x;
}

//Mod Hesaplama
int Liste::modHesapla(int x, int y)
{
    if(x == 0 || y == 0)
        return 0;

    if(x > y)
        return x%y;
    return y%x;
}

int Liste::getMax(int x, int y)
{
    if(x > y)
        return x;
    return y;
}
Liste::Liste()
{
    this->head = NULL;
    this->tail = NULL;
    this->enBuyukOBEB = 0;
}

ListeDugumu* Liste::getHead()
{
    return head;
}

void Liste::setHead(ListeDugumu* head)
{
    this->head = head;
}

ListeDugumu* Liste::getTail()
{
    return tail;
}

void Liste::setTail(ListeDugumu* tail)
{
    this->tail = tail;
}

void Liste::insertToBeginning(int number)
{
    ListeDugumu* yeniDugum = new ListeDugumu(number);
    if(head == NULL && tail == NULL)
    {
        head = yeniDugum;
        tail = yeniDugum;
        yeniDugum->setPrev(yeniDugum);
        yeniDugum->setNext(yeniDugum);
    }
    else
    {
        yeniDugum->setNext(head);
        yeniDugum->setPrev(tail);
        head->setPrev(yeniDugum);
        tail->setNext(yeniDugum);
        head = yeniDugum;
    }
}

void Liste::insert(int number)
{
    if(head == NULL) // ilk sayi
    {
        insertToBeginning(number);
        enBuyukOBEB = 0;
        return;
    }

    ListeDugumu* geciciDugum = head;
    
    do
    {
        int geciciNumber = geciciDugum->getData();
        if(obebHesapla(geciciNumber, number) >= enBuyukOBEB || geciciDugum == tail)
        {
            enBuyukOBEB = getMax(enBuyukOBEB, obebHesapla(geciciNumber, number));
            int mod = modHesapla(geciciNumber, number);

            if(head == NULL)
            {
                insertToBeginning(number);
                return;
            }

            if(mod == 0)
            {

                ListeDugumu* yeniDugum = new ListeDugumu(number);
                yeniDugum->setNext(geciciDugum->getNext());
                yeniDugum->setPrev(geciciDugum);
                geciciDugum->getNext()->setPrev(yeniDugum);
                geciciDugum->setNext(yeniDugum);
                if(geciciDugum == tail)
                    tail = yeniDugum;
                return;
            }

            bool toBeginning = false;
            for(int i=0;i<mod;i++)
            {
                if(geciciDugum != head)
                    geciciDugum = geciciDugum->getPrev();
                else
                    toBeginning = true;
            }

            if(toBeginning)
            {
                insertToBeginning(number);
            }
            else
            {
                ListeDugumu* yeniDugum = new ListeDugumu(number);
                yeniDugum->setNext(geciciDugum->getNext());
                yeniDugum->setPrev(geciciDugum);
                geciciDugum->getNext()->setPrev(yeniDugum);
                geciciDugum->setNext(yeniDugum);
                if(geciciDugum == tail)
                    tail = yeniDugum;
            }

            return;
        }
        geciciDugum = geciciDugum->getNext();
    }
    while(geciciDugum != head);
    
}

void Liste::printList()
{
    cout << "SIFRE : ";
    ListeDugumu* geciciDugum = head;
    while(geciciDugum->getNext() != head)
    {
        if(geciciDugum->getData())
            cout << char(geciciDugum->getData());
        else
            cout << ' ';
        geciciDugum = geciciDugum->getNext();
    }
    if(geciciDugum->getData())
           cout << char(geciciDugum->getData()) << endl;
    else
           cout << ' ' << endl;
}

Liste::~Liste()
{
    if(head == NULL)
        return;
    
    ListeDugumu* geciciDugum = head;

    while(geciciDugum != tail)
    {
        ListeDugumu* next = geciciDugum->getNext();
        delete geciciDugum;
        geciciDugum = next;
    }

    delete geciciDugum;
} 