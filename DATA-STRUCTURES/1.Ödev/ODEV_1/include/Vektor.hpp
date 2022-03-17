/**
* @file ./b141210019/include/Vektor.hpp
* @description Vektor kütüphanemizinin çalýþtýðý kýsým . Ekleme  deðiþtirme vs yapýlan kýsým.
* @course Veri Yapýlarý /1A
* @assignment 1.ödev
* @date 28.10.2015
* @author Mehmet Mert Yavuz/b141210019
*/
#ifndef Vektor_hpp
#define Vektor_hpp
#include<iostream>
using namespace std;
template<typename Nesne>
class Vektor{
public:
	Nesne*elemanlar;
	int elemansayisi;
	void insert(int i, const Nesne& yeni)
	{
		for (int j = elemansayisi - 1; j >= i; j--)
			elemanlar[j + 1] = elemanlar[j];
		elemanlar[i] = yeni;
		elemansayisi++;
	}
	Vektor()
	{
		elemansayisi = 0;
		elemanlar = new Nesne[10];
	}
	Nesne& at(int i)
	{
		return elemanlar[i];
	}
	int size()
	{
		return elemansayisi;
	}
	static void swap(Vektor<int>*dizi, Vektor<int>*dizi2)//degistirme islemi
	{
		dizi = dizi2;
	}
	~Vektor()
	{
		delete[] elemanlar;
	}
};
#endif
