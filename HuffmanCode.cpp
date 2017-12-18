#include "stdafx.h"
#include"HuffmanCompress.h"
#include<iostream>
using namespace std;

int main()
{
	HuffmanCompress fl;
	while (true)
	{
		cout << "1. Compress" << endl << "2. DeCompress" << endl << "3. Quit" << endl
			<< "Please Select:";
		int f = 0;
		cin >> f;
		switch (f)
		{
		case 1: fl.Compress(); cout << "Processing....." << endl;  break;
		case 2: fl.DeCompress(); cout << "Processing....." << endl; break;
		case 3: exit(0); break;
		default: cout << "Error!Select again!" << endl; break;
		}
	}
	return 0;
}

