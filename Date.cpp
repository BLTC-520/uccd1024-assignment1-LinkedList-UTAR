#include <iostream>
#include "Date.h"

using namespace std;

Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

void Date::print(ostream& out)
{
	out << day << "/" << month << "/" << year;

}
