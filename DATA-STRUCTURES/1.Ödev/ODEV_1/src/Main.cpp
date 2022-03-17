/**
* @file ./b141210019/src/Main.cpp
* @description Ana fonksiyonumuzun çalýþtýðý programýn iþlem yaptýðý kýsým.
* @course Veri Yapýlarý /1A
* @assignment 1.ödev
* @date 28.10.2015
* @author Mehmet Mert Yavuz/b141210019
*/
#include"Vektor.hpp"
#include"Yolcu.hpp"
#include"Otobus.hpp"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	Otobus mert;
	mert.YolcuAta();
	mert.YolcuSirala();
	Vektor<Yolcu>*yolcux = new Vektor<Yolcu>();
	Vektor<Yolcu>*yolcuy = new Vektor<Yolcu>();
	for (int i = 0; i < 10; i++)
	{
		yolcux->insert(i, mert.yolcular1[i]);
		yolcuy->insert(i, mert.yolcular2[i]);
	}
	cout << "---------------SWAP ONCESI-------------" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << yolcux->at(i).yolcuAd << " " << yolcux->at(i).koltukNo << " " << &yolcux->at(i) << endl;
	}
	cout << "----------------------------------" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << yolcuy->at(i).yolcuAd << " " << yolcuy->at(i).koltukNo << " " << &yolcuy->at(i) << endl;
	}
	cout << "-------------SWAP SONRASI" << endl;
	swap(yolcux, yolcuy);
	for (int i = 0; i < 10; i++)
	{
		cout << yolcux->at(i).yolcuAd << " " << yolcux->at(i).koltukNo << " " << &yolcux->at(i) << endl;
	}
	cout << "----------------------------------" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << yolcuy->at(i).yolcuAd << " " << yolcuy->at(i).koltukNo << " " << &yolcuy->at(i) << endl;
	}
	cin.get();
	return 0;
}