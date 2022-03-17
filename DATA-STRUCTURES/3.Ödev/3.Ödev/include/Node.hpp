#ifndef Node_hpp
#define Node_hpp
#include<iostream>
#include"Liste.hpp"

using namespace std;
struct Dugum{
public:
	Liste*px;
	string agacveri;
	string dugumveri;
	Dugum *sol;
	Dugum *sag;
	Dugum(const string& vr, const string& vr2,Liste*py, Dugum *sl = NULL, Dugum *sg = NULL)
	{
		agacveri = vr;
		dugumveri = vr2;
		sol = sl;
		sag = sg;
		px = py;
	}

	
};
#endif Dugum_hpp