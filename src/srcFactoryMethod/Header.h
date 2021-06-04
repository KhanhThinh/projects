#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Book {
protected:
	string id;
	string name;
	string author;
	int publishYear;
	int numberOfPages;
	string category;
	string language;
public:
	Book();
	Book(string newId, string newName, string newAuthor,int newPublishYear,int newNumberOfPages,string newCategory,string newLanguage);
	virtual void input();
	virtual void showInfo();
	string getId();
	string getName();
	string getAuthor();
	string getCategory();
	string getLanguage();
	void setName(string newName);
	void setAuthor(string newAuthor);
	void setCategory(string newCategory);
	void setLanguage(string newLanguage);
};

class ComicBook:public Book {
private:
	int part;
public:
	int getPart();
	void input();
	void showInfo();
};

class LiteratureBook:public Book {
private:
	int chapter;
public:
	int getChapter();
	void input();
	void showInfo();
};

class ForeignBook:public Book {
private:
	int chapter;
public:
	int getChapter();
	void input();
	void showInfo();
};

class BookStore {
private:
	vector<Book*> books;
public:
	Book* findBook(string searchId);
	void showBooks();
	void addBook(Book* newBook);
};

