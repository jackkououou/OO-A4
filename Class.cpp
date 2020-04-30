#include "Class.h"
#include <iostream>
#include <typeinfo>
using namespace std;

Date::Date(int d, int m, int y)
{
	set(d, m, y);
}

void Date::set(int d, int m, int y)
{
	if (d >= 1 && d <= 31)
		day = d;
	else
	{
		cout << "\ninvalid day";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
	if (m >= 1 && m <= 12)
		month = m;
	else
	{
		cout << "\ninvalid month";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
	if (y >= 1900 && y <= 3000)
		year = y;
	else
	{
		cout << "\ninvalid year";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
}

void Date::get()
{
	char ch;

	cout << "Enter date in mm/dd/yyyy format: ";
	cin >> month >> ch >> day >> ch >> year;

	while (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 3000)
	{
		cout << "\nInvalid date entered" << endl;
		cout << "\nEnter date in mm/dd/yyyy format: ";
		cin >> day >> ch >> month >> ch >> year;
	}
}

void Date::print() const
{
	cout << day << "/" << month << "/" << year;
}

bool Date::operator==(const Date& d) const
{
	return day == d.day && month == d.month && year == d.year;
}

Time::Time(int h, int m)
{
	set(h, m);
}

void Time::set(int h, int m)
{
	if (h >= 0 && h <= 24)
		hour = h;
	else
	{
		cout << "\nInvalid hour";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}

	if (m >= 0 && m <= 60)
		minute = m;
	else
	{
		cout << "\nInvalid minute";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
}

void Time::get()
{
	char ch;

	cout << "Enter time in military [hour:minute] format: ";
	cin >> hour >> ch >> minute;

	while (hour < 0 || hour > 24 || minute < 0 || minute > 60)
	{
		cout << "\nInvalid time entered";
		cout << "\nEnter time in military [hour:minute] format: ";
		cin >> hour >> ch >> minute;
	}
}

void Time::print() const
{
	cout << hour << ":" << minute;
}

int Time::get_hour() const
{
	return hour;
}

int Time::get_minute() const
{
	return minute;
}

Time Time::operator-(const Time& t) const
{
	if (minute >= t.minute)   // check minutes before creating the temp object
		return Time(hour - t.hour, minute - t.minute);
	else
		return Time(hour - t.hour - 1, minute + 60 - t.minute);
}

bool Time::operator==(const Time& t) const
{
	return hour == t.hour && minute == t.minute;
}

bool Time::operator<(const Time& t) const
{
	if (hour < t.hour)
		return true;
	else if ((hour == t.hour) && (minute < t.minute))
		return true;
	else
		return false;
}

bool Time::operator>(const Time& t) const
{
	return !(*this == t) && !(*this < t); // if not equal and not less, it must be greater
}

float Time::time_dec() 
{
	float product = 0;
	product += (minute / 60);
	product += hour;
	return product;
}

Appointment::Appointment() : date(), start_time(), end_time()
{
	strcpy_s(description, "");
	strcpy_s(location, "");
}

void Appointment::get()
{
	char c;

	date.get();

	do
	{
		cout << "Start time - ";
		start_time.get();

		cin.ignore(20, '\n');

		cout << "End time - ";
		end_time.get();

		cin.ignore(20, '\n');

		if (start_time.get_hour() > end_time.get_hour())
			cout << "\nEnd time cannot be earlier than start time" << endl;

	} while (start_time.get_hour() > end_time.get_hour());

	cout << "Enter description: ";
	int i = 0;
	cin.get(c);
	while (c != '\n')
	{
		description[i++] = c;
		cin.get(c);
	}
	description[i] = '\0';

	cout << "Enter location: ";
	i = 0;
	cin.get(c);
	while (c != '\n')
	{
		location[i++] = c;
		cin.get(c);
	}
	location[i] = '\0';
}

void Appointment::print() const
{
	cout << "\nAppointment Date: ";
	date.print();
	cout << "\nStart time: ";
	start_time.print();
	cout << "\nEnd time: ";
	end_time.print();
	cout << "\nDescription: " << description;
	cout << "\nLocation: " << location;
}

Date Appointment::get_date() const
{
	return date;
}

Time Appointment::get_start_time() const
{
	return start_time;
}

Time Appointment::get_end_time() const
{
	return end_time;
}

Session::Session()
{
	this->client_id[0] = '~';
	this->fname[0] = '~';
	this->lname[0] = '~';
	this->hourly_charge = 0;
}
Session::~Session()
{
	delete this;
}
void Session::set()
{
	cout << "\nEnter ID: ";
	cin.getline(this->client_id, 11, '\n');
	cout << "\nEnter first name: ";
	cin.getline(this->fname, 21, '\n');
	cout << "\nEnter last name:";
	cin.getline(this->lname, 21, '\n');
}
void Session::read()
{
	
	cout << "\nEnter client ID (5 characters) :";
	cin.getline(this->client_id, 5, '\n');
	cout << "\nEnter client First name (20 characters) :";
	cin.getline(this->fname, 20, '\n');
	cout << "\nEnter client Last name (20 characters) :";
	cin.getline(this->lname, 20, '\n');
}
void Session::print() const
{

	cout << "\nSession Date: ";
	date.print();
	cout << "\nStart time: ";
	start_time.print();
	cout << "\nEnd time: ";
	end_time.print();
	cout << "\nDescription: " << description;
	cout << "\nLocation: " << location;
	cout << "\nFirst name: " << fname;
	cout << "\nLast name: " << lname;
	cout << "\Client ID: " << client_id;
}
float Session::get_charge()
{
	Time temp;
	float dec_t;
	temp = end_time - start_time;
	dec_t = temp.time_dec();
	return (hourly_charge * dec_t);

}

const char* Session::get_id()
{
	return client_id;
}
const char* Session::get_lname()
{
	return lname;
}
const char* Session::get_fname()
{
	return fname;
}

ClientSession::ClientSession()
{
	this->client_id[0] = '~';
	this->fname[0] = '~';
	this->lname[0] = '~';
	this->hourly_charge = 0;
}

ClientSession::~ClientSession()	{	delete this;	}

CourtSession::CourtSession() 
{
	this->client_id[0] = '~';
	this->fname[0] = '~';
	this->lname[0] = '~';
	this->hourly_charge = 0;
	this->courtName[0] = '~';
	this->location[0] = '~';
}

CourtSession::~CourtSession()	{	delete this;	}

void CourtSession::set()
{
	cout << "\nEnter ID: ";
	cin.getline(this->client_id, 11, '\n');
	cout << "\nEnter first name: ";
	cin.getline(this->fname, 21, '\n');
	cout << "\nEnter last name:";
	cin.getline(this->lname, 21, '\n');
	cout << "\nEnter name of court: ";
	cin.getline(this->courtName, 20, '\n');
	cout << "\nEnter location of court: ";
	cin.getline(this->location, 20, '\n');
}

void CourtSession::print() const
{
	cout << "\nSession Date: ";
	date.print();
	cout << "\nStart time: ";
	start_time.print();
	cout << "\nEnd time: ";
	end_time.print();
	cout << "\nDescription: " << description;
	cout << "\nLocation: " << location;
	cout << "\nFirst name: " << fname;
	cout << "\nLast name: " << lname;
	cout << "\Client ID: " << client_id;
	cout << "\nCourt name: " << courtName;
	cout << "\nLocation: " << location;
}
