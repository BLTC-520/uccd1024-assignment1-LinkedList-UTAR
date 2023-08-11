#ifndef LibStudent_type
#define LibStudent_type

#include    <fstream>
#include    "LibBook.h"

using namespace std;

struct LibStudent
{
	char name[30];
	char id[10];
	char course[3];
	char phone_no[10];
	double total_fine;
	int totalbook;
	LibBook book[15];
	
	LibStudent();
	bool calculateTotalFine();
	bool compareName1(LibStudent); //use >=
	bool compareName2(LibStudent); //use ==
	void print(ostream &);
	
};

#endif
