#include <iostream>
#include <iomanip>
#include "LibBook.h"
#include "LibStudent.h"


using namespace std;

LibStudent::LibStudent()
{
	strcpy(name, " ");
	strcpy(id, " ");
	strcpy(course, " ");
	strcpy(phone_no, " ");
	totalbook = 0;
	total_fine = 0.0;
}

bool LibStudent::compareName1(LibStudent p2)
{
	if (strcmp(name, p2.name) >= 0)
		return true;
	return false;
}

bool LibStudent::compareName2(LibStudent p2)
{
	if (strcmp(name, p2.name) == 0)
		return true;
	return false;
}


bool LibStudent::calculateTotalFine()
{
	LibBook b;

	total_fine = 0;

	//traverse the book array to calculate total fine
	for (int i = 0; i < totalbook; i++)
		total_fine = total_fine + book[i].fine;

	return true;
}


void LibStudent::print(ostream &out)
{
	out << "\n\nName: " << name;
	out << "\nId: " << id;
	out << "\nCourse: " << course;
	out << "\nPhone No: " << phone_no;
	out << "\nTotal Fine: RM" << setprecision(2) << fixed << total_fine;
	out << endl;

}
