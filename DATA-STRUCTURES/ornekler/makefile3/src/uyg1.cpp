/* 
 * File:   main.cpp
 * Author: asd
 *
 * Created on September 26, 2018, 5:49 PM
 */
#include <iostream>
#include "islem.hpp"
using namespace std;

int main(int argc,char **argv) {
    int a,b,c;
    a=5;b=9;
    c=topla(a,b);
    cout<<"topla="<<c<<endl;
    c=carp(a,b);
    cout<<"carp="<<c<<endl;
    return 0;
}

