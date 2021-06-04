#include "Header.h"
Book::Book() {
	language = "Viet Nam";
	publishYear = 2001;
	numberOfPages = 0;
}

Book::Book(string newId, string newName, string newAuthor, int newPublishYear, int newNumberOfPages, string newCategory, string newLanguage)
{
	id = newId;
	name = newName;
	author = newAuthor;
	publishYear = newPublishYear;
	numberOfPages = newNumberOfPages;
	category = newCategory;
	language = newLanguage;
}

void Book::input()
{
	cout << "Ma: ";
	getline(cin, id);
	cout << "Ten: ";
	getline(cin, name);
	cout << "Tac gia: ";
	getline(cin, author);
	cout << "Nam xuat ban: ";
	cin >> publishYear;
	cout << "So trang: ";
	cin >> numberOfPages;
	cin.ignore();
	cout << "Ngon ngu: ";
	string lan;
	getline(cin, lan);
}

void Book::showInfo()
{
	cout << "Ma          : " << id << endl;
	cout << "Ten         : " << name << endl;
	cout << "Tac gia     : " << author << endl;
	cout << "Nam xuat ban: " << publishYear << endl;
	cout << "So trang    : " << numberOfPages << endl;
	cout << "Ngon ngu    : " << language << endl;
	cout << "The loai    : " << category << endl;
}

string Book::getId()
{
	return id;
}

string Book::getName() {
	return name;
}

string Book::getAuthor() {
	return author;
}

string Book::getCategory() {
	return category;
}

string Book::getLanguage() {
	return language;
}

void Book::setName(string newName) {
	this->name = newName;
}

void Book::setAuthor(string newAuthor)
{
	author = newAuthor;
}

void Book::setCategory(string newCategory)
{
	category = newCategory;
}

void Book::setLanguage(string newLanguage)
{
	language = newLanguage;
}

int ComicBook::getPart() {
	return part;
}

void ComicBook::input()
{
	Book::input();
	cout << "So phan: ";
	cin >> part;
}

void ComicBook::showInfo()
{
	Book::showInfo();
	cout << "So phan: " << part << endl;
}

int LiteratureBook::getChapter() {
	return chapter;
}

void LiteratureBook::input()
{
	Book::input();
	cout << "So chuong: ";
	cin >> chapter;
}

void LiteratureBook::showInfo()
{
	Book::showInfo();
	cout << "So chuong: " << chapter << endl;
}

int ForeignBook::getChapter() {
	return chapter;
}

void ForeignBook::input()
{
	Book::input();
	cout << "So chuong: ";
	cin >> chapter;
}

void ForeignBook::showInfo()
{
	Book::showInfo();
	cout << "So chuong: " << chapter << endl;
}

Book* BookStore::findBook(string searchId)
{
	for (int i = 0; i < books.size(); i++)
	{
		if (searchId==books[i]->getId())
		{
			return books[i];
		}
	}
	return NULL;
}

void BookStore::showBooks()
{
	if (books.size() == 0)
	{
		cout << "Khong co cuon sach nao";
		return;
	}
	cout << "==== Thong tin sach cua hieu sach ====" << endl;
	for (int i = 0; i < books.size(); i++)
	{
		cout << "-----------" << endl;
		cout << "Cuon sach thu " << i + 1 << endl;
		books[i]->showInfo();
		cout << "-----------" << endl;
	}
}

void BookStore::addBook(Book* newBook) {
	books.push_back(newBook);
}