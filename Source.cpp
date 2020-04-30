//This source file contains the definition for Date, Time and Appointment classes plus the main program
//You are to make necessary changes to these classes and derive a Session class from Appointment so that
//the program will work like the provided exe file (except it needs to display your name above the menu)
//Also, put your name, class, assignment and date here as comments
//Programmer: Jack A. Kouyoumdjian
//Class: CS_216_26141SP20V
// Assignment 3
// 4/19/2020
#include <iostream>
#include <typeinfo>
#include "Class.h"

using namespace std;



bool conflict(Appointment*, Appointment* [], int, int&); // params: Appt *, Appt *[], array size and index of Appt with conflict
bool conflict_s(Session*, Session* [], int, int&);
int select_appt(Appointment* [], int);

enum classType { appt, session };

int main()
{
	Appointment* ap[100], * temp;
	Session* sp, * tempSesh;
	CourtSession* courtpntr;
	ClientSession* clientpntr;
	classType type[100];
	int menu_choice = 0, choice_utility, selection, count = 0, index, i;
	char id[11], fname[21], lname[21], y_nchoice;
	Date date;
	float charges = 0.0;
	bool found;

	do
	{
		cout << "\n1) Add new Session";
		cout << "\n2) Display all Sessions";
		cout << "\n3) Search for a client";
		cout << "\n4) Display total charges for all clients and the average hours spent";
		cout << "\n5) Quit the menu";
		cout << "\nEnter a choice: ";
		cin >> menu_choice;

		system("cls");

		switch (menu_choice)
		{
		case 1:
			cout << "\nIs this a court session? [y/n]: ";
			cin >> y_nchoice;
			if (y_nchoice == 'y')
			{
				temp = new CourtSession;
				temp->get();
				if (conflict(temp, ap, count, index))
				{

					cout << "\nThis will conflict with: ";
					ap[index]->print();	 
					cout << "\n\nAppointment not entered.";
				}
				else
				{
					courtpntr = reinterpret_cast<CourtSession*>(temp);
					courtpntr->set();
					ap[count] = temp;
					type[count] = appt; 
					count++;
				}
			}
			else
			{
				temp = new ClientSession;
				temp->get();
				if (conflict(temp, ap, count, index))
				{

					cout << "\nThis will conflict with: ";
					ap[index]->print();
					cout << "\n\nAppointment not entered.";
				}
				else
				{
					clientpntr = reinterpret_cast<ClientSession*>(temp);
					clientpntr->set();
					ap[count] = temp;
					type[count] = appt;
					count++;
				}
			}

			break;
		case 2:
			for (i = 0; i < count; i++)
			{
				cout << "\nList of scheduled sessions:" << endl;
				ap[i]->print();
				cout << endl;
			}
			break;
		case 3:
			do
			{
				cout << "\nEnter 1 to search by I.D. or 2 to search by name: ";
				cin >> choice_utility;
				found = false;

				if (choice_utility == 1)
				{
					cout << "\nEnter client I.D.: ";
					cin >> id;

					for (i = 0; i < count; i++)
						if (type[i] == session)
						{
							sp = (Session*)(ap[i]);
							if (!strcmp(id, sp->get_id())) // we have to look at Sessions only
							{
								sp->print();
								found = true;		 // because Appts don't have get_id() 
							}
						}

					if (!found)
						cout << "\nClient not found. ";
				}
				else if (choice_utility == 2)
				{
					cout << "\nEnter client last name: ";
					cin >> lname;

					cout << "\nEnter client first name: ";
					cin >> fname;

					for (i = 0; i < count; i++)
						if (type[i] == session)
						{
							sp = (Session*)(ap[i]);
							if (!strcmp(lname, sp->get_lname()) && !strcmp(fname, sp->get_fname()))
							{
								sp->print();
								found = true;
							}
						}

					if (!found)
						cout << "\nClient not found. ";
				}
				else
					cout << "\nPlease, enter either 1 or 2: ";

			} while (choice_utility < 1 || choice_utility > 2);

			break;
		case 4:
			charges = 0.0;

			for (i = 0; i < count; i++)
				if (type[i] == session)
				{
					sp = (Session*)(ap[i]);
					charges += sp->get_charge();
				}

			cout << "\nTotal charges for all clients is " << charges;

			charges = 0.0;
			break;
		case 5:		
			return 0;

		default:	cout << "\nInvalid entry - please, enter a number between 1 and 10.";
		}

	} while (1);
}

bool conflict(Appointment* p, Appointment* ap[], int size, int& i) // i is the index of the array element with conflict
{																   // the function modifies i so the caller can get it
	Date date = p->get_date();
	Time start = p->get_start_time();
	Time end = p->get_end_time();

	for (i = 0; i < size; i++)
		if (date == ap[i]->get_date())
			if ((start == ap[i]->get_start_time()) ||
				(start < ap[i]->get_start_time()) && (end > ap[i]->get_start_time()) ||
				(start > ap[i]->get_start_time()) && (start < ap[i]->get_end_time()))
				return true;
	return false;
}
bool conflict_s(Session* p, Session* ap[], int size, int& i) // i is the index of the array element with conflict
{																   // the function modifies i so the caller can get it
	Date date = p->get_date();
	Time start = p->get_start_time();
	Time end = p->get_end_time();

	for (i = 0; i < size; i++)
		if (date == ap[i]->get_date())
			if ((start == ap[i]->get_start_time()) ||
				(start < ap[i]->get_start_time()) && (end > ap[i]->get_start_time()) ||
				(start > ap[i]->get_start_time()) && (start < ap[i]->get_end_time()))
				return true;
	return false;
}
int select_appt(Appointment* ap[], int size) // returns the index of the array element if found and -1 if not found
{
	Date date;
	int choice, int_array[10], j = 0;

	cout << "\nEnter appointment or session date: ";
	date.get();

	for (int i = 0, j = 0; i < size; i++) // search for given date
		if (date == ap[i]->get_date())
		{
			int_array[j++] = i; // Store i in int_array when date matches
			cout << "\n----------- " << j << " ----------";
			ap[i]->print();
			cout << endl;
		}

	if (j == 0) // if Appt or Session not found
		return -1;

	else // Appt or Session found
	{
		do
		{
			cout << "\nSelect the appointment by entering its number: [1 - " << j << "]: ";
			cin >> choice;
		} while (choice < 1 || choice > j);

		return int_array[choice - 1];
	}
	
}
