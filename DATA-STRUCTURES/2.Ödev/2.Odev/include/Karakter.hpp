/**
* @file Dosya adý=Karakter.hpp
* @description Karakter sýnýfýnýn bulunduðu yer
* @course Veri Yapýlarý- Sinan Tuncel 
* @assignment 2.Odev
* @date Kodu oluþturduðunuz 02.12.2015
* @author Mehmet Mert Yavuz(b141210019 -1/a) Eren Songur(b141210087-1/a)
*/
#ifndef Karakter_hpp
#define Karakter_hpp
#include<iostream>
#include<time.h>
#include<cstdlib>
using namespace std;
class Karakter{
public:
	char karakter;
	Karakter()
	{
		char randomChar = 'A';
		 unsigned int number = rand() %24;
		switch (number)
		{
		case 0:
			randomChar = 'A';
		case 1:
			randomChar = 'A';
			break;
		case 2:
			randomChar = 'B';
			break;
		case 3:
			randomChar = 'C';
			break;
		case 4:
			randomChar = 'D';
			break;
		case 5:
			randomChar = 'E';
			break;
		case 6:
			randomChar = 'F';
			break;
		case 7:
			randomChar = 'G';
			break;
		case 8:
			randomChar = 'H';
			break;
		case 9:
			randomChar = 'I';
			break;
		case 10:
			randomChar = 'J';
			break;
		case 11:
			randomChar = 'K';
			break;
		case 12:
			randomChar = 'L';
			break;
		case 13:
			randomChar = 'M';
			break;
		case 14:
			randomChar = 'N';
			break;
		case 15:
			randomChar = 'O';
			break;
		case 16:
			randomChar = 'P';
			break;
		case 17:
			randomChar = 'Q';
			break;
		case 18:
			randomChar = 'R';
			break;
		case 19:
			randomChar = 'S';
			break;
		case 20:
			randomChar = 'T';
			break;
		case 21:
			randomChar = 'U';
			break;
		case 22:
			randomChar = 'V';
			break;
		case 23:
			randomChar = 'Y';
			break;
		case 24:
			randomChar = 'Z';
			break;
		}
		karakter = randomChar;
	}
};
#endif