#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

class Vaccine {
protected:
	string ID;
	string Name;
	int Type;
public:
	Vaccine() {
		Type = 0;
	}	
	virtual void input() {
		cout << "Nhap vao ID vaccine: ";
		getline(cin, ID);
		cout << "Nhap vao ten vaccine: ";
		getline(cin, Name);
	}
	virtual void output() = 0;
	string getID() {
		return ID;
	}
};

class AstraZeneca : public Vaccine {
public:
	AstraZeneca() {
		Type = 1;
	}
	void output() {
		cout << "ID cua vaccine: " << ID << endl;
		cout << "Ten cua vaccine: " << Name << endl;
		cout << "Loai vaccine: AstraZeneca" << endl;
	}
};

class NanoCovax : public Vaccine {
public:
	NanoCovax() {
		Type = 2;
	}
	void output() {
		cout << "ID cua vaccine: " << ID << endl;
		cout << "Ten cua vaccine: " << Name << endl;
		cout << "Loai vaccine: NanoCovax" << endl;
	}
};

class Pfizer_BioNTech : public Vaccine {
public:
	Pfizer_BioNTech() {
		Type = 3;
	}
	void output() {
		cout << "ID cua vaccine: " << ID << endl;
		cout << "Ten cua vaccine: " << Name << endl;
		cout << "Loai vaccine: Pfizer-BioNTech" << endl;
	}
};