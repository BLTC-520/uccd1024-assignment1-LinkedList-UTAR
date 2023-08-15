#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	<iomanip>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"			


#define _CRT_SECURE_NO_WARNINGS			
// MUST DO!!!
// Go to Debug Tab, select Debug Properties
// "C/C++" ---> Advanced ---> "Disable Specific Warnings" type 4996

// This is to prevent error while compile

const int SIZE = 256;									
List* type1 = new List;									
List* type2 = new List;									

using namespace std;									

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool SearchStudent(List*, char* id, LibStudent&);
bool InsertBook(string, List*);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

char* whitespace(char*);								
void Convert_Date(char*, Node*, int, bool);				
int JulianDay(int, int, int);						

int main() {

	int choice = 0;										
	List* stu_list = new List;						
	LibBook book;
	LibStudent stu;
	char id[10], callNum[20];

	while (choice != 9) {
		choice = menu();
		if (choice == 1) {	
			cout << "\n\nREAD FILE SELECTED\n\n\n";
			if (ReadFile("student.txt", stu_list));
			else cout << "\n\nWARNING: UNEXPECTED ERROR HAD OCCURED!\n\n";
		}
		if (choice == 2) { 
			string d;
			int z = 0;
			cout << "\n\nDELETE RECORD SELECTED\n\n";
			if (stu_list->size() == 0) {
				cout << "\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\nPlease Enter ID: ";
			cin >> id;
			cout << "\n\nDo you wish to delete the record?\n\n1. YES\n2. NO\nEnter your choice: ";
			cin >> z;
			if (z == 1) {
				if (DeleteRecord(stu_list, id)) cout << "\n\nRecord ID \"" << id << "\" has successfully been deleted.\n\n";
				else cout << "\n\nRecord ID \"" << id << "\" cannot be found in the list.\n\n";
			}
			else if (z == 2) cout << "\n\nDelete record has been cancelled, returning to main menu.\n\n";
			else cout << "\n\nInvalid Input! Please try again.\n\n";
		}
		if (choice == 3) {
			cout << "\n\nSEARCH RECORD SELECTED\n\n";
			if (stu_list->size() == 0) {
				cout << "\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\nPlease Enter ID: ";
			cin >> id;
			if (SearchStudent(stu_list, id, stu)) cout << "\n\nRecord ID \"" << id << "\" has successfully been found.\n\n";
			else cout << "\n\nRecord ID \"" << id << "\" cannot be found in the list.\n\n";
		}
		if (choice == 4) {
			cout << "\n\nINSERT BOOK SELECTED\n";
			if (InsertBook("book.txt", stu_list));
			else cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
		}
		if (choice == 5) {
			int source, detail;
			cout << "\n\nDISPLAY SELECTED\n";
			if (stu_list->size() == 0) {
				cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\n\nOutput Selection\n\n1. Display to file\n2. Display to screen"; 
			cout << "\nPlease Enter Display Option: ";
			cin >> source;
			cout << "\n\nDisplay Details\n\n1. Display Student Info Only\n2. Display Student Info and Book Info"; 
			cout << "\nPlease Enter Details Option: ";
			cin >> detail;
			if (Display(stu_list, source, detail)) cout << "\n\nRecord displayed successfully.\n\n";
			else cout << "\n\nWARNING: UNEXPECTED ERROR HAD OCCURED!\n\n";
		}
		if (choice == 6) { 
			cout << "\n\nDISPLAY STATISTIC SELECTED\n";
			if (computeAndDisplayStatistics(stu_list)) cout << "\n\nStatistic displayed successfully.\n\n";
			else cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
		}
		if (choice == 7) { 
			cout << "\n\nSTUDENT WITH SAME BOOK SELECTED\n\n";
			if (stu_list->size() == 0) {
				cout << "\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\nPlease Enter Book Call Number: ";
			cin >> callNum;
			cout << endl;
			if (printStuWithSameBook(stu_list, callNum)) cout << "\nStatistic displayed successfully.\n\n";
			else cout << "\nNo student have the book with Call Number: \"" << callNum << "\" borrowed.\n\n";
		}
		if (choice == 8) { 
			cout << "\n\nDISPLAY WARNED LIST SELECTED\n";
			if (stu_list->size() == 0) {
				cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			if (displayWarnedStudent(stu_list, type1, type2)) cout << "\nWarned List displayed successfully.\n\n";
			else cout << "\n\nBoth Warned List is empty!\n\n";
		}
		if (choice == 0)cout << "\n\nInvalid Input! Please try again.\n\n";
	}
	cout << "\n\n >.< EXITING THE PROGRAM >.<! \n";
	cout << "\n\n";
	system("pause");
	return 0;
}

int menu()
{
	int x;
	cout << "\nMenu\n\n";
	cout << "1. Read File\n";
	cout << "2. Delete Record\n";
	cout << "3. Search Student\n";
	cout << "4. Insert Book\n";
	cout << "5. Display Output\n";
	cout << "6. Compute and Display Statistics\n";
	cout << "7. Student with Same Book\n";
	cout << "8. Display Warned Student\n";
	cout << "9. Exit\n";
	cout << "Enter your choice: ";
	cin >> x;

	if (x > 9 || x < 1) {
		return 0;
	}

	return x;
}


bool ReadFile(string filename, List* list) {
	ifstream in;
	char temp[256];
	Node* stu_node;
	int count = 0;										
	int duplicate = 0;							

	LibStudent stu_info;				

	in.open(filename);
	if (in.is_open()) {
		while (!in.eof()) {
			bool duplicate = false;			
			for (int i = 0; i < 3; i++) {
				in >> temp;
			}
			in >> stu_info.id;
			for (int i = 0; i < 2; i++) {
				in >> temp;
			}
			in.getline(stu_info.name, 256);
			for (int i = 0; i < 2; i++) {
				in >> temp;
			}
			in >> stu_info.course;
			for (int i = 0; i < 3; i++) {
				in >> temp;
			}
			in >> stu_info.phone_no;
			for (int i = 1; i <= list->size(); i++) {
				stu_node = list->find(i);
				if (strcmp(stu_node->item.id, stu_info.id) == 0) {
					duplicate++;
					cout << "Alert! Student:" << stu_info.name << " - with ID \"" << stu_info.id << "\" has been repeated, student details is not read.\n\n\n";
					duplicate = true;
				}
				if (duplicate == true) break;	
			}
			if (duplicate == false) {
				list->insert(stu_info);
				count++;
			}
		}
		cout << count << " Record(s) has successfully been read.\n\n";
		if (duplicate > 0)cout << "\nWarning! " << duplicate << " Duplicated Record(s) are found.\n\n";
	}
	else {
		cout << "Error! Cannot open " << filename << " file.\n";
		return false;
	}
	in.close();
	return true;
}

bool DeleteRecord(List* list, char* id) {
	Node* node;
	type temp;

	for (int i = 1; i <= list->size(); i++) {
		list->get(i, temp);
		if (strcmp(temp.id, id) == 0) {
			list->remove(i);
			for (int i = 1; i <= type1->size(); i++) {
				node = type1->find(i);
				if (strcmp(node->item.id, id) == 0) {
					type1->remove(i);
				}
			}
			for (int i = 1; i <= type2->size(); i++) {
				node = type2->find(i);
				if (strcmp(node->item.id, id) == 0) {
					type2->remove(i);
				}
			}
			return true;
		}
	}
	return false;
}

bool SearchStudent(List* list, char* id, LibStudent& stu) {
	for (int i = 1; i <= list->size(); i++) {
		list->get(i, stu);
		if (strcmp(stu.id, id) == 0) {	
			cout << "\n\n***************************************************************";
			stu.print(cout);
			cout << "\n***************************************************************\n";
			return true;
		}
	}
	return false;
}

bool Display(List* list, int source, int detail) {
	type temp;
	ofstream out;
	if (detail == 1) {			
		if (source == 1) {		
			out.open("student_info.txt");
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp);
				out << "\nSTUDENT " << i;
				temp.print(out);
				out << "\n***************************************************************\n";
			}
			out.close();
			cout << "\n\nOutput File: \"student_info.txt\" has been created/updated.\n";
			return true;
		}
		else if (source == 2) {		
			cout << "\n***************************************************************\n";
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp);
				cout << "\nSTUDENT " << i;
				temp.print(cout);
				cout << "\n***************************************************************\n";
			}
			return true;
		}
	}
	else if (detail == 2) {		
		if (source == 1) {			
			out.open("student_booklist.txt");
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp);
				out << "\nSTUDENT " << i;
				temp.print(out);
				if (temp.totalbook != 0) {
					out << "\nBOOK LIST:\n";
					for (int x = 0; x < temp.totalbook; x++) {
						out << "\nBook " << x + 1 << endl;
						temp.book[x].print(out);
					}
				}
				else
					out << "\nThis student didn't borrow any book.\n";
				out << "\n***************************************************************\n";
			}
			out.close();
			cout << "\n\nOutput File: \"student_booklist.txt\" has been created/updated.\n";
			return true;
		}
		else if (source == 2) {		
			cout << "\n***************************************************************\n";
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp);
				cout << "\nSTUDENT " << i;
				temp.print(cout);
				if (temp.totalbook != 0) {
					cout << "\nBOOK LIST:\n";
					for (int x = 0; x < temp.totalbook; x++) {
						cout << "\nBook " << x + 1 << endl;
						temp.book[x].print(cout);
					}
				}
				else 
					cout << "\nThis student didn't borrow any book.\n";
				cout << "\n***************************************************************\n";
			}
			return true;
		}
	}
	return false;
}

bool InsertBook(string filename, List* list) {
	ifstream in;
	char temp[SIZE], temp2[SIZE], temp3[SIZE];	
	char* author = new char[20];					
	char* next_author = NULL;						
	Node* stu_node;						
	char title[SIZE], id[SIZE];			

	List* temp_list = new List;
	Node* temp_node;							
	LibStudent stu_book;						

	int duplicate = 0;								
	int bookcount = 0;							

	int C_Date = JulianDay(29, 3, 2020);			
	int D_Date;									

	int stu_null = 0;							

	in.open(filename);
	if (in.is_open()) {
		while (!in.eof()) {
			bool duping = false;
			in >> temp;							
			strcpy_s(id, sizeof(id), temp);
			if (list->size() == 0) return false;
			bool NotFound = true;						
			for (int i = 1; i <= list->size(); i++) {
				if (in.eof()) break;
				stu_node = list->find(i);
				int totalbook = stu_node->item.totalbook;
				if (strcmp(stu_node->item.id, temp) == 0) {
					temp_list->insert(1, stu_book);
					temp_node = temp_list->find(1);
					in >> temp;
					int x = 0;															
					author = strtok_s(temp, "/", &next_author);								
					while (author != NULL) {												
						temp_node->item.book[totalbook].author[x] = new char[SIZE];
						strcpy_s(temp_node->item.book[totalbook].author[x], SIZE, whitespace(author));
						author = strtok_s(NULL, "/", &next_author);
						x++;
					}
					in >> temp;															
					strcpy_s(stu_book.book[totalbook].title, sizeof(stu_book.book[totalbook].title), whitespace(temp));
					in >> temp;															
					strcpy_s(stu_book.book[totalbook].publisher, sizeof(stu_book.book[totalbook].publisher), whitespace(temp));
					in >> stu_book.book[totalbook].ISBN;								
					in >> stu_book.book[totalbook].yearPublished;						
					in >> stu_book.book[totalbook].callNum;								
					in >> temp;
					strcpy_s(temp2, sizeof(temp2), temp);
					Convert_Date(temp, temp_node, totalbook, 0);						
					in >> temp;
					strcpy_s(temp3, sizeof(temp3), temp);
					Convert_Date(temp, temp_node, totalbook, 1);						

					D_Date = JulianDay(temp_node->item.book[totalbook].due.day, temp_node->item.book[totalbook].due.month, temp_node->item.book[totalbook].due.year);
					if (C_Date - D_Date < 0) stu_book.book[totalbook].fine = 0;			
					else {
						stu_book.book[totalbook].fine = (C_Date - D_Date) * 0.5;			
					}
					NotFound = false;
					if (stu_node->item.totalbook != 0) { 
						for (int i = 0; i < stu_node->item.totalbook; i++) {
							if (strcmp(stu_node->item.book[i].callNum, stu_book.book[totalbook].callNum) == 0) {
								int temp_borrow1 = JulianDay(stu_node->item.book[i].borrow.day, stu_node->item.book[i].borrow.month, stu_node->item.book[i].borrow.year);
								int temp_borrow2 = JulianDay(temp_node->item.book[totalbook].borrow.day, temp_node->item.book[totalbook].borrow.month, temp_node->item.book[totalbook].borrow.year);
								if (temp_borrow1 == temp_borrow2) {
									duplicate++;
									cout << "\n\nAlert! Book: " << stu_book.book[totalbook].title << "- with Call Number \"" << stu_book.book[totalbook].callNum << "\" has been repeated, book details is not inserted.\n";
									duping = true;
								}
							}

						}
					}
					if (duping == false) {	
						for (int i = 0; i < x; i++) {
							stu_node->item.book[totalbook].author[i] = new char[SIZE];
							strcpy_s(stu_node->item.book[totalbook].author[i], SIZE, temp_node->item.book[totalbook].author[i]);
						}
						strcpy_s(stu_node->item.book[totalbook].title, sizeof(stu_node->item.book[totalbook].title), stu_book.book[totalbook].title);
						strcpy_s(stu_node->item.book[totalbook].publisher, sizeof(stu_node->item.book[totalbook].publisher), stu_book.book[totalbook].publisher);
						strcpy_s(stu_node->item.book[totalbook].ISBN, sizeof(stu_node->item.book[totalbook].ISBN), stu_book.book[totalbook].ISBN);
						stu_node->item.book[totalbook].yearPublished = stu_book.book[totalbook].yearPublished;
						strcpy_s(stu_node->item.book[totalbook].callNum, sizeof(stu_node->item.book[totalbook].callNum), stu_book.book[totalbook].callNum);
						Convert_Date(temp2, stu_node, totalbook, 0);
						Convert_Date(temp3, stu_node, totalbook, 1);
						stu_node->item.book[totalbook].fine = stu_book.book[totalbook].fine;
						bookcount++;
						stu_node->item.totalbook++;
					}
					stu_node->item.calculateTotalFine();
					temp_list->remove(1);
					break;
				}
			}if (NotFound == true) {
				stu_null++;
				for (int i = 0; i < 2; i++) 
					in >> temp;
				strcpy_s(title, sizeof(title), whitespace(temp));
				for (int i = 0; i < 6; i++) 
					in >> temp;
			}
		}
		cout << "\n\n" << bookcount << " Book(s) inserted successfully to student list.\n\n";
		if (duplicate > 0) 
			cout << "\nWarning! " << duplicate << " Duplicated Record(s) are found. \n\n";
	}
	else
	{
		cout << "Error! Cannot open " << filename << " file.\n";
		return true;
	}
	in.close();
	return true;
}

bool computeAndDisplayStatistics(List* list) {
	Node* stu_node;
	string course[5] = { "CS","IA","IB","CN","CT" };					
	int StuNo[5] = { 0 }, BookBorrowed[5] = { 0 }, BookDue[5] = { 0 };	
	double TotalDueFine[5] = { 0 };										
	int tuple = 0;														
	char temp[SIZE];

	if (list->size() == 0) 
		return false;
	for (int i = 1; i <= list->size(); i++) {
		stu_node = list->find(i);
		strcpy_s(temp, SIZE, stu_node->item.course);	
		if (strcmp(temp, "CS") == 0) 
			tuple = 0;				
		else if (strcmp(temp, "IA") == 0) 
			tuple = 1;
		else if (strcmp(temp, "IB") == 0) 
			tuple = 2;
		else if (strcmp(temp, "CN") == 0) 
			tuple = 3;
		else if (strcmp(temp, "CT") == 0) 
			tuple = 4;
		StuNo[tuple]++;
		BookBorrowed[tuple] += stu_node->item.totalbook;
		TotalDueFine[tuple] += stu_node->item.total_fine;
		for (int i = 1; i <= stu_node->item.totalbook; i++) {
			if (stu_node->item.book[i - 1].fine > 0) {	
				BookDue[tuple]++;
			}
			else continue;
		}
	}
	cout << "\n\n--------------------------------------------------------------------------------------------------------";
	cout << "\n\nCourse\tNumber of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine(RM)\n";
	cout << "\n--------------------------------------------------------------------------------------------------------\n\n";
	for (tuple = 0; tuple < 5; tuple++) {
		cout << course[tuple] << "\t" << StuNo[tuple] << "\t\t\t";
		cout << BookBorrowed[tuple] << "\t\t\t" << BookDue[tuple] << "\t\t\t";
		cout << setprecision(2) << fixed << TotalDueFine[tuple] << endl;
	}
	cout << "\n--------------------------------------------------------------------------------------------------------\n";
	return true;
}

bool printStuWithSameBook(List* list, char* callNum) {
	Node* stu_node;
	LibBook stu_book;
	int same = 0;									
	strcpy_s(stu_book.callNum, 20, callNum);	

	for (int i = 1; i <= list->size(); i++) {		
		stu_node = list->find(i);
		for (int totalbook = 0; totalbook < stu_node->item.totalbook; totalbook++) {
			if ((stu_book.compareCallNum(stu_node->item.book[totalbook]) == 1))  
				same++;
		}
	}
	if (same == 0) 
		return false;
	cout << "\nThere are " << same << " students that borrow the book with call number \"" << callNum << "\" as shown below :\n\n";
	for (int i = 1; i <= list->size(); i++) {		
		stu_node = list->find(i);
		for (int totalbook = 0; totalbook < stu_node->item.totalbook; totalbook++) {	
			if ((stu_book.compareCallNum(stu_node->item.book[totalbook]) == 1)) {	
				cout << "Id: " << stu_node->item.id << endl;
				cout << "Name:" << stu_node->item.name << endl;
				cout << "Course: " << stu_node->item.course << endl;
				cout << "Phone No: " << stu_node->item.phone_no << endl;
				cout << "Borrow Date: ";
				stu_node->item.book[totalbook].borrow.print(cout);
				cout << endl;
				cout << "Due Date: ";
				stu_node->item.book[totalbook].due.print(cout);
				cout << endl << endl;
			}
		}
	}
	return true;
}

bool displayWarnedStudent(List* list, List* type1, List* type2) {
	LibStudent stu_info;
	Node* stu_node;
	Node* stu;
	int totalbook;							
	int C_Date = JulianDay(29, 3, 2020);		

	for (int i = 1; i <= list->size(); i++) {
		list->get(i, stu_info);
		bool matcht1 = 0;///////////////////////////////////////////////
		bool matcht2 = 0;
		int type1due = 0;					
		int type2due = 0;					
		for (totalbook = 0; totalbook < stu_info.totalbook; totalbook++) {
			int D_Date = JulianDay(stu_info.book[totalbook].due.day, stu_info.book[totalbook].due.month, stu_info.book[totalbook].due.year);
			if (C_Date - D_Date >= 10) 
				type1due++;
			if (C_Date - D_Date > 0)
				type2due++;
			else continue;
		}
		for (int i = 1; i <= type1->size(); i++) {
			stu = type1->find(i);
			if (strcmp(stu->item.id, stu_info.id) == 0) 
				matcht1 = 1;
		}
		for (int i = 1; i <= type2->size(); i++) {
			stu = type2->find(i);
			if (strcmp(stu->item.id, stu_info.id) == 0) 
				matcht2 = 1;
		}
		if (matcht1 != 1) {
			if (type1due > 2) 
				type1->insert(stu_info);
		}
		if (matcht2 != 1) {
			if (stu_info.totalbook == type2due && stu_info.total_fine > 50) 
				type2->insert(stu_info);
		}
	}
	if (type1->size() == 0 && type2->size() == 0)
		return false;			
	cout << "\n\n***************************************************************\n\n";
	cout << "\nType 1 Warned List:\n**Student has more than 2 books that are overdue for >= 10 days. ";		
	if (type1->size() != 0) {
		for (int i = 1; i <= type1->size(); i++) {
			stu_node = type1->find(i);
			stu_node->item.print(cout);
			cout << "\nBOOK LIST:\n";
			for (int x = 0; x < stu_node->item.totalbook; x++) {
				cout << "\nBook " << x + 1 << endl;
				stu_node->item.book[x].print(cout);
			}
			if (i != type1->size())
				cout << "\n===============================================================";
		}
	}
	else 
		cout << "\n\nType 1 Warned List is empty!";
	cout << "\n\n***************************************************************\n\n";
	cout << "\nType 2 Warned List:\n**Total fine for a student is more than RM50.00 and every book in the students book list are overdue. ";	
	if (type2->size() != 0) {
		for (int i = 1; i <= type2->size(); i++) {
			stu_node = type2->find(i);
			stu_node->item.print(cout);
			cout << "\nBOOK LIST:\n";
			for (int x = 0; x < stu_node->item.totalbook; x++) {
				cout << "\nBook " << x + 1 << endl;
				stu_node->item.book[x].print(cout);
			}
			if (i != type2->size())
				cout << "\n===============================================================";
		}
	}
	else 
		cout << "\n\nType 2 Warned List is empty!";
	cout << "\n\n***************************************************************\n";
	cout << endl;
	return true;
}

char* whitespace(char* temp) {
	int i = 0;
	while (temp[i] != '\0') {
		if (temp[i] == '_') {
			temp[i] = ' ';
		}
		i++;
	}
	return temp;
}

void Convert_Date(char* temp, Node* node, int i, bool bd) {
	char* item = new char[SIZE];
	char* next_item = NULL;
	if (bd == 0) {									
		int x = 1;
		item = strtok_s(temp, "/", &next_item);							
		while (item != NULL) {
			if (x == 1)
				node->item.book[i].borrow.day = stoi(item);
			else if (x == 2)
				node->item.book[i].borrow.month = stoi(item);
			else if (x == 3)
				node->item.book[i].borrow.year = stoi(item);
			item = strtok_s(NULL, "/", &next_item);
			x++;
		}
	}
	else if (bd == 1) {								
		int x = 1;
		item = strtok_s(temp, "/", &next_item);								
		while (item != NULL) {
			if (x == 1)
				node->item.book[i].due.day = stoi(item);
			else if (x == 2)
				node->item.book[i].due.month = stoi(item);
			else if (x == 3)
				node->item.book[i].due.year = stoi(item);
			item = strtok_s(NULL, "/", &next_item);
			x++;
		}
	}
}

int JulianDay(int D, int M, int Y) {
	int JDN = (1461 * (Y + 4800 + (M - 14) / 12)) / 4 + (367 * (M - 2 - 12 * ((M - 14) / 12))) / 12 - (3 * ((Y + 4900 + (M - 14) / 12) / 100)) / 4 + D - 32075;
	return JDN;
}
