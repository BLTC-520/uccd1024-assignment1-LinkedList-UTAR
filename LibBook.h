#ifndef LibBook_type
#define LibBook_type

#include    <fstream>
#include    "Date.h"

using namespace std;

//represent a book in library
struct LibBook
{

	char title[250];
	char *author[10]; //can be more than one author
	char publisher[30];
	char ISBN[11]; //10 digits isbn
	int yearPublished;

	Date borrow;
	Date due;
	char callNum[20];
	double fine;

	LibBook();
	bool compareTitle(LibBook); //use >=
	bool compareCallNum(LibBook); //use ==
	void print(ostream &);
};




#endif
