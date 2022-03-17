/**
* @file ./b141210019/include/Otobus.hpp
* @description Otobus kütüphanesini oluþturduðumuz kýsým Yolcu iþlemlerini gerçekleþtirir.
* @course Veri Yapýlarý /1A
* @assignment 1.ödev
* @date 28.10.2015
* @author Mehmet Mert Yavuz/b141210019
*/
#ifndef Otobus_hpp
#define Otobus_hpp
#include "Yolcu.hpp"
#include<fstream>
#include<string>
class Otobus :public Yolcu
{
public:
	Yolcu yolcular1[10];
	Yolcu yolcular2[10];
	fstream dosya;
	Otobus()
	{
		dosya.open("Yolcular.txt", ios::out | ios::in | ios::app);
		dosya.setf(ios::left);
	}
	void YolcuAta()
	{
		for (int i = 0; i < 10; i++)
		{
			dosya >> yolcular1[i].yolcuAd;
			dosya >> yolcular1[i].koltukNo;

		}
		for (int j = 0; j < 10; j++)
		{
			dosya >> yolcular2[j].yolcuAd;
			dosya >> yolcular2[j].koltukNo;

		}
	}
	void YolcuSirala()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (yolcular1[j].koltukNo > yolcular1[i].koltukNo)
				{
					Yolcu temp;
					temp = yolcular1[i];
					yolcular1[i] = yolcular1[j];
					yolcular1[j] = temp;
				}
			}
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (yolcular2[j].koltukNo > yolcular2[i].koltukNo)
				{
					Yolcu temp;
					temp = yolcular2[i];
					yolcular2[i] = yolcular2[j];
					yolcular2[j] = temp;
				}
			}
		}
	}
};
#endif Otobus_hpp