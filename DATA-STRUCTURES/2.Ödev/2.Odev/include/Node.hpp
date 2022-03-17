/**
* @file Dosya adý=Node.hpp
* @description Düðüm sýnýfýnýn bulunduðu yer
* @course Veri Yapýlarý- Sinan Tuncel
* @assignment 2.Odev
* @date Kodu oluþturduðunuz 02.12.2015
* @author Mehmet Mert Yavuz(b141210019 -1/a) Eren Songur(b141210087-1/a)
*/
#ifndef Node_hpp
#define Node_hpp
#include<iostream>
#include<string>
#include"Karakter.hpp"
using namespace std;
template<typename Nesne>
class Node{
private:
	Node<Nesne>*head;
	Node<Nesne>*finish;
public:
	Karakter* data;
	Node<Nesne>*next;
	Node<Nesne>*Prev;
	Node()
	{
		head = NULL;
		finish = NULL;
		next = NULL;
		Prev = NULL;
	}
	void Push(Nesne* newData)
	{
		Node*newNode = new Node();
		if (isEmpty())
		{
			head = newNode;
			finish = newNode;
			head->Prev = NULL;
			finish->next = NULL;
			newNode->data = newData;
		}
		else
		{
			//Burada son eleman biz olacaðýz.
			newNode->data = newData;
			newNode->Prev = finish;//Bizden önceki eski finish
			finish->next = newNode;//Artýk finish biziz.
			finish = newNode;
			finish->next = NULL;
			head->Prev = NULL;

		}
	}
	bool isEmpty()
	{
		if (head == NULL)
			return true;
		else
			return false;
	}
	void display()
	{
		Node<Nesne>*temp = head;
		while (temp != NULL)
		{
			cout << temp->data->karakter<<" ";
			temp = temp->next;
		}
	}
	Node*Pop()
	{
		if (isFull())
		{

			if (head != finish)
			{
				finish = finish->Prev;
				Node<Nesne>*temp = finish->next;
				finish->next = NULL;
				return temp;
			}
			else
			{
				Node*gecici = head;
				head = gecici->next;
				return gecici;
			}
		}
		else
			return 0;
	}
	Node*BastanCikar()
	{
		Node*gecici = head;
		head = gecici->next;
		return gecici;
	}
	bool isFull()
	{
		if (head != NULL)return true;
		else return false;
	}
};
#endif