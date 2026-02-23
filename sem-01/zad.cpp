#include <iostream>
namespace constants 
{
	const size_t TITLE_LENGTH = 64;
	const size_t NAME_LENGTH = 32;
	const size_t MAX_BOOKS = 10;
}
enum Status 
{
	Available,
	Borrowed,
	Reserved
};
class Book 
{
public:
	const char* title ;
	const char* author ;
	unsigned publication;
	Status bookStatus;
};
class Library
{
public:
	char name[constants::NAME_LENGTH];
	Book books[constants::MAX_BOOKS];
	int bookCount;
};
bool addBook(Library& libr, const char* name, const char* title, unsigned year)
{
	if (libr.bookCount >= constants::MAX_BOOKS)
		return 0;

	Book temp = { title, name, year,  Available};
	libr.books[libr.bookCount] = temp;
	libr.bookCount++;

	return 1;
}
void borrowBook(Book& book)
{
	book.bookStatus = Borrowed;
}
void reserveBook(Book& book)
{
	book.bookStatus = Reserved;
}
void printLibrary(const Library& libr)
{
	int limit = libr.bookCount;
	for (int i = 0; i < limit; ++i)
		std::cout << libr.books[i].title << " " << libr.books[i].bookStatus << std::endl;
}
bool compareBooks(const Book book1, const Book book2)
{
	int i = 0;
	while (book1.title[i] || book2.title[i])
	{
		if (book1.title[i] < book2.title[i])
			return 1;
		if (book1.title[i] > book2.title[i])
			return 0;
		i++;
	}

	return 0;
}
void swapBooks(Book& book1, Book& book2)
{
	Book temp = { book1.title, book1.author, book1.publication, book1.bookStatus };
	book1 = { book2.title, book2.author, book2.publication, book2.bookStatus };
	book2 = { temp.title, temp.author, temp.publication, temp.bookStatus };
}
void printLibraryAlphabetically(const Library& libr)
{
	int limit = libr.bookCount;
	Book temp[10];

	for (int i = 0; i < limit; ++i)
		temp[i] = libr.books[i];

	for (int i = 0; i < limit; ++i)
		for (int j = 0; j < i; ++j)
		{
			if (compareBooks(temp[i], temp[j]))
				swapBooks(temp[i], temp[j]);
		}

	for(int i=0;i<limit;++i)
		std::cout << temp[i].title << " " << temp[i].bookStatus << std::endl;
}
int main()
{
	Book book1 = { "abcd", "abcd", 2000, Available };
	Book book2 = { "abcde", "abcd", 2000, Available };
	Book book3 = { "dabcd", "abcd", 2000, Available };

	Library libr = { "abd", {book3,book1}, 2 };
	addBook(libr, book2.author, book2.title, book2.publication);
	borrowBook(libr.books[2]);
	reserveBook(libr.books[1]);

	printLibrary(libr);
	std::cout << std::endl;
	printLibraryAlphabetically(libr);
}
