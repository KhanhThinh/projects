// FactoryMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Header.h"

int main()
{
	int n = 0;
	cout << "Nhap so sach: ";
	cin >> n;
	cin.ignore();
	system("cls");
	cout << "Loai sach: " << endl;
	cout << "1. Truyen tranh" << endl;
	cout << "2. Van hoc" << endl;
	cout << "3. Ngoai Van" << endl;
	BookStore store;
	for (int i = 0; i < n; i++)
	{
		cout << "\nSach thu " << i + 1 << endl;
		cout << "The loai: ";
		int choose;
		cin >> choose;
		while (choose < 1 || choose > 3) {
			cout << "Lua chon khong phu hop. Nhap lai: ";
			cin >> choose;
		}
		cin.ignore();
		string category;
		Book* book = NULL;
		if (choose == 1)
		{
			category = "Truyen Tranh";
			book = new ComicBook;
		}
		else if (choose == 2)
		{
			category = "Van hoc";
			book = new LiteratureBook;
		}
		else if (choose == 3)
		{
			category = "Ngoai van";
			book = new ForeignBook;
		}
		book->setCategory(category);
		book->input();
		store.addBook(book);
	}
	system("cls");
	store.showBooks();
	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
