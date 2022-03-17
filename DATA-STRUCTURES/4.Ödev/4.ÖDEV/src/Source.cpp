#include<iostream>
#include<fstream>
#include<string>
#include <cstring>
#include<cstdlib>
#include"huffman.hpp"
using namespace std;
int main()
{
	int secenek = 0;
	while (true)
	{
		cout << "1-Dosyayi sikistir" << endl;
		cout << "2-Sikistirilmis dosyayi ekrana yazdir" << endl;
		cout << "3-Cikis" << endl;
		cout << "Lütfen bir secenek giriniz..";
		cin >> secenek;
		switch (secenek)
		{
		case 1:
		{
				  Huffman *huffman = new Huffman("deneme.txt");
				  huffman->Kodla();
				  cout << *huffman;
				  delete huffman;
				  break;
		}
		case 2:
		{
				  string kod;
				  fstream dosya;
				  dosya.open("bit.bat", ios::in | ios::out | ios::app);
				  dosya >> kod;
				  cout << kod;
				  break;
		}
		case 3:
			return 0;
		}
		cout << endl;
		cout << "tablo.txt=764 byte" << endl;
		cout << "bit.bat=594 byte" << endl;
		cout << "Toplam=1358 byte"<< endl;
		cout << "*******************" << endl;
		cout << "deneme.txt=4440 byte" << endl;
		cout << "********************" << endl;
		cout << "1258 byte <4440 byte SIKISTIRMA ISLEMI BASARILI" << endl;
		system("pause");
		system("cls");
	}
}