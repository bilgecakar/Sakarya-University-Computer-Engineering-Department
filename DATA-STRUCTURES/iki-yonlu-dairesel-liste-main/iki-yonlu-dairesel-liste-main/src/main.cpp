

#include<iostream>
#include<fstream>
#include<sstream>

#include "Liste.hpp"

using namespace std;

int main()
{   // Dosya Okuma
    ifstream theFile("Sayilar.txt");
    string line;
    int sayi;
    while(getline(theFile, line))
    {
        stringstream stringStream(line);

        Liste* liste = new Liste();

        while(stringStream >> sayi)
        {
            liste->insert(sayi);
        }

        liste->printList();
        delete liste;
    }

    theFile.close();
	getchar();
    return 0;
}