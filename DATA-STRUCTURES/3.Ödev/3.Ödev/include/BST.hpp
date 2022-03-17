#ifndef BST_hpp
#define BST_hpp
#include<iostream>
#include<string>
#include"Node.hpp"
#include"Liste.hpp"
class BinarySearchTree{
private:
	Dugum*root;
	void AraveEkle(Dugum*&alt_Dugum, const string& agacverix, const string& dugumverix)
	{
		if (alt_Dugum == NULL)
		{
			Liste*py = new Liste();
			alt_Dugum = new Dugum(agacverix, dugumverix,py);
			alt_Dugum->px->Push(dugumverix);
			
		}
		else if (agacverix < alt_Dugum->agacveri)
		{
			AraveEkle(alt_Dugum->sol,agacverix, dugumverix);
			
		}
		else if (agacverix > alt_Dugum->agacveri)
		{
			AraveEkle(alt_Dugum->sag,agacverix, dugumverix);
			
		}
		else
		{
			//Eðer ayný elemandan varsa.
			alt_Dugum->px->Push(dugumverix);
		}
	}

	void Inorder(Dugum *alt_Dugum, bool kontrol = true) const{
		if (alt_Dugum != NULL){
			//LÝSTEYÝ KENDÝ ÝÇÝNDE SIRALAMAMIZ GEREKÝYOR.
			Inorder(alt_Dugum->sol);
			//
			cout << alt_Dugum->agacveri << endl;
			alt_Dugum->px->display();
			//
			Inorder(alt_Dugum->sag);
		}
	}
	void Preorder(Dugum *alt_Dugum) const{
		if (alt_Dugum != NULL){
			//
			cout<<alt_Dugum->agacveri<<endl;
			//alt_Dugum->px->display();
			BinarySearchTree*bk = new BinarySearchTree();
			alt_Dugum->px->display();
			Preorder(alt_Dugum->sol);
			Preorder(alt_Dugum->sag);
		}
	}
	void Postorder(Dugum *alt_Dugum) const
	{
		if (alt_Dugum != NULL){
			Postorder(alt_Dugum->sol);
			Postorder(alt_Dugum->sag);
			//
			cout << alt_Dugum->agacveri << endl;
			alt_Dugum->px->display();
			//
		}
	}
public:
	BinarySearchTree(){
		root = NULL;
	}
	bool Bosmu() const{
		return root == NULL;
	}
	void Ekle(string&yeni, string&yeni2)
	{
		Liste*px=new Liste();
		AraveEkle(root, yeni, yeni2);
	}
	void Inorder() const{
		Inorder(root);
	}
	void Preorder() const{
		Preorder(root);
	}
	void Postorder() const{
		Postorder(root);
	}
};

#endif
