#ifndef Date_type
#define Date_type

#include    <fstream>

using namespace std;

struct Date
{
	int day;
	int month;
	int year;
	Date();
	void print(ostream &);
	
};



#endif
