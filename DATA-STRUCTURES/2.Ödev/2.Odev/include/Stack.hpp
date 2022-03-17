/**
* @file Dosya adý=Stack.hpp
* @description Stack sýnýfýnýn bulunduðu yer
* @course Veri Yapýlarý- Sinan Tuncel
* @assignment 2.Odev
* @date Kodu oluþturduðunuz 02.12.2015
* @author Mehmet Mert Yavuz(b141210019 -1/a) Eren Songur(b141210087-1/a)
*/
#ifndef Stack_hpp
#define Stack_hpp
#define STACK_MAX 100
#include<iostream>
#include<string>
#include"Karakter.hpp"
#include"Node.hpp"
using namespace std;
class Stack{
	private:
		unsigned int Top;//Yýðýna eklenecek elemanýn hangi indise ekleneceðini tutar.
		char D[STACK_MAX];
	public:
		Stack()
		{
			Top = 0;//Ýlk baþta çuvalda hiç kitap olmadýðý için top=0 ve bu boþ olduðu anlamýnada gelir.
		}
		void Push(Node<Karakter>* Item)
		{
			if (isFull())
			{

			}
			else
			{
				D[Top] =Item->data->karakter;
				Top++;
			}
		}
		bool isFull()
		{
			if (Top == STACK_MAX)
				return true;
			else
				return false;
		}
		char Pop()//Son eklenen elemaný çýkaracaktýr.
		{
			if (!isEmpty())
			{

				//Top biliyoruz ki eklenecek elemanýn indeksini tutuyor o zaman son eleman top-1
				Top--;
				return D[Top];
			}
			else
				return 0;
		}
		bool isEmpty()
		{
			if (Top == 0)
				return true;
			else return false;
		}
		char TopRet()//Son elemaný çýkarmadan kopyasýný alýp bize getirir.
		{
			if (isEmpty()) return 0;
			else{
				char item = D[Top - 1];
				return item;
			}
		}
		void display()
		{
			for (int i = 0; i < Top; i++)
			{
				cout << D[i] << " ";
			}
		}
};
#endif