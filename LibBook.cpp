#include <iostream>
#include <string>
#include <iomanip>
#include "LibBook.h"


using namespace std;

LibBook::LibBook()
{
	strcpy(title, " ");
	strcpy(publisher, " ");
	strcpy(ISBN, " ");
	yearPublished = 0;

	for (int i = 0; i < 10; i++)
		author[i] = NULL;

	strcpy(callNum, " ");
	fine = 0.0;
}

bool LibBook::compareTitle(LibBook b2) {
	if (strcmp(title, b2.title) >= 0)
		return true;
	return false;
}

bool LibBook::compareCallNum(LibBook b2) {
	if (strcmp(callNum, b2.callNum) == 0)
		return true;
	return false;
}

void LibBook::print(ostream& out)
{
	out << "\nTitle: " << title;
	out << "\nAuthor: ";
	for (int i = 0; author[i] != NULL; i++)
		out << author[i] << '\t';
	out << "\nPublisher: " << publisher;
	out << "\nYear Published: " << yearPublished;
	out << "\nISBN: " << ISBN;

	out << "\nCall Number: " << callNum;
	out << "\nBorrow Date: ";
	borrow.print(out);
	out << "\nDue Date: ";
	due.print(out);
	out << "\nFine: RM" << setprecision(2) << fixed << fine;
	out << endl;

}
