#include<iostream>
#include<fstream>
#include"BST.hpp"
#include"Liste.hpp"
using namespace std;
int main()
{
	fstream dosya;
	BinarySearchTree*bst = new BinarySearchTree();
	string treeName;
	string childname;
	dosya.open("dosya.txt", ios::out | ios::in | ios::app);
	dosya.setf(ios::left);
	for (int i = 0; i < 9; i++)//Burada While(end-of -file) EOF Kullanmak daha mantýklý ama nedense dosyanýn sonunu göremedi.
	{
		dosya >> treeName;
		dosya >> childname;
		bst->Ekle(treeName, childname);
	}
	//
	cout << "******************" << endl;
	cout << "PreOrder Gosterimi" << endl;
	cout << "------------------" << endl;
	bst->Preorder();
	cout << "******************" << endl;
	//
	cout << "******************" << endl;
	cout << "InOrder Gosterimi" << endl;
	cout << "------------------" << endl;
	bst->Inorder();
	cout << "******************" << endl;
	//
	cout << "******************" << endl;
	cout << "PostOrder Gosterimi" << endl;
	cout << "------------------" << endl;
	bst->Postorder();
	cout << "******************" << endl;
	cin.get();
	return 0;
}