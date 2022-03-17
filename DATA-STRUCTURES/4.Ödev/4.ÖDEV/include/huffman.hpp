/**
* @file Source.cpp
* @description Huffman kütüphanesi
* @course Veriyapýlarý A grubu
* @assignment 4.Ödev
* @date Kodu 28.12.2015
* @author Mehmet Mert Yavuz(b141210019@sakarya.edu.tr), Eren Songur(b141210087@sakarya.edu.tr)
*/
#ifndef huffman_hpp
#define huffman_hpp
#include<iostream>
#include<fstream>
#include<string>
#include <cstring>
#include<cstdlib>
#include"Node.hpp"
using namespace std;
class Huffman{
private:
	int harfler;  			// harflerin ASCII karþýlýklarý
	string girdi;			// dosyadan okunan girdi
	Dugum *root;
public:
	Dugum* AgacOlustur(int frek[]){
		// dosyada var olan karakterler için düðüm oluþtur.
		Dugum** dugumler = new Dugum*[harfler];
		for (int i = 0; i<harfler; i++){
			if (frek[i]>0){
				dugumler[i] = new Dugum((char)i, frek[i]);
			}
			else{
				dugumler[i] = NULL;
			}
		}
		while (true){
			int ilkIndeks = MinDugumIndeks(dugumler);
			Dugum *min1 = dugumler[ilkIndeks];
			dugumler[ilkIndeks] = NULL;
			int ikinciIndeks = MinDugumIndeks(dugumler);
			if (ikinciIndeks == -1){
				return min1;
			}
			Dugum *min2 = dugumler[ikinciIndeks];
			dugumler[ikinciIndeks] = NULL;
			dugumler[ilkIndeks] = new Dugum(0, min1->frekans + min2->frekans, min1, min2);
		}

	}
	void KodOlustur(Dugum* alt_dugum, string kod){
		if (!alt_dugum->Yaprakmi()){
			KodOlustur(alt_dugum->sol, kod + '0');
			KodOlustur(alt_dugum->sag, kod + '1');
		}
		else{
			fstream dosya2;
			fstream dosya;
			dosya.open("bit.bat", ios::in | ios::out | ios::app);
			dosya2.open("tablo.txt", ios::in | ios::out | ios::app);
			dosya2 << alt_dugum->karakter << "  " << kod << endl;
			alt_dugum->kod = kod;
			dosya << kod;
			dosya.close();
			dosya2.close();
		}
	}
	int MinDugumIndeks(Dugum* dugumler[]){
		Dugum* min;
		int minIndeks = -1;

		// ilk null olmayan düðümü min al
		for (int i = 0; i<harfler; i++){
			if (dugumler[i] != NULL){
				min = dugumler[i];
				minIndeks = i;
				break;
			}
		}

		//for (int i = 0; i<harfler; i++)
		//{
		//	if (dugumler[i] == NULL) continue;

		//	if (min > (dugumler[i])) {
		//		min = dugumler[i];
		//		minIndeks = i;
		//	}
		//}
		return minIndeks;
	}
	void DosyaOku(string dosyaYolu){
		string satir;
		ifstream dosya(dosyaYolu.c_str());
		if (dosya.is_open())
		{
			while (getline(dosya, satir))
			{
				int i = 0;
				int k = satir.size();
				while (i<k)
				{
					if (satir[i] == ' ')
						satir[i] = '@';
					i++;
				}
				girdi += satir;
				girdi += '>';
			}
			dosya.close();
		}
		else throw "Dosya acilamadi";
	}
	Dugum* Kok(){
		return root;
	}
	void inorder(Dugum* alt_dugum){
		if (alt_dugum != NULL){
			inorder(alt_dugum->sol);
			if (alt_dugum->Yaprakmi()) cout << alt_dugum->karakter << ":" << alt_dugum->kod << endl;
			inorder(alt_dugum->sag);
		}
	}
	void SilDugum(Dugum* alt_dugum){
		if (alt_dugum == NULL) return;
		SilDugum(alt_dugum->sol);
		SilDugum(alt_dugum->sag);
		delete alt_dugum;
		alt_dugum = NULL;
	}
	Huffman(string dosyaYolu){
		harfler = 256;
		girdi = "";
		DosyaOku(dosyaYolu);

		root = NULL;
	}
	void Kodla(){
		int k = girdi.size();
		char*karakterler = new char[k - 1];
		strcpy(karakterler, girdi.c_str());
		//Frekanslarý say
		int*frek = new int[harfler];
		// frekanslarý sýfýrla
		for (int i = 0; i<harfler; i++)frek[i] = 0;

		for (int i = 0; i < girdi.size() - 1; i++)
			frek[karakterler[i]]++;

		// Huffman aðacýný oluþtur
		root = AgacOlustur(frek);

		// 01 kodlar oluþturuluyor
		KodOlustur(root, "");
	}
	friend ostream& operator<<(ostream& ekran, Huffman& sag){
		ekran << "Huffman Agacindaki Karakterler ve Kodlari:" << endl;
		sag.inorder(sag.Kok());
		return ekran;
	}
	~Huffman(){
		SilDugum(root);
	}
};

#endif