#ifndef Liste_hpp
#define Liste_hpp
#include<string>
#include<iostream>
using namespace std;
class Liste{
private:
	Liste*head;
	Liste*finish;
public:
	string data;
	Liste*next;
	Liste*Prev;
	Liste()
	{
		head = NULL;
		finish = NULL;
		next = NULL;
		Prev = NULL;
	}
	void Push(string newData)
	{
		Liste*newNode = new Liste();
		if (isEmpty())//Eðer boþsa halay baþý olmak istiyoruzdur.
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
		cout << "    ";
		Liste*temp = head;
		while (temp != NULL)
		{
			cout << temp->data<<" ";
			temp = temp->next;
		}
		cout << endl;
	}
	string&Pop()
	{
		if (isFull())
		{

			if (head != finish)
			{
				finish = finish->Prev;
				finish->next = NULL;
				return finish->data;
			}
			else
			{
				Liste*gecici = head;
				head = gecici->next;
				return gecici->data;
			}
		}
		else
		{
			string hata = "sadsadsa";
			return hata;
		}
	}
	bool isFull()
	{
		if (head != NULL)return true;
		else return false;
	}
	
};
#endif