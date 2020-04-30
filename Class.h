#ifndef Class_h

#define Class_h


#include <string>
using namespace std;
class Date
{
private:
	int day, month, year;
public:
	Date(int = 1, int = 1, int = 1900);
	void set(int = 1, int = 1, int = 1900);
	void get();
	void print() const;
	bool operator==(const Date&) const;
};

class Time
{
private:
	int hour, minute;
public:
	Time(int = 0, int = 0);
	void set(int = 0, int = 0);
	void get();
	void print() const;
	int get_hour() const;
	int get_minute() const;
	Time operator-(const Time&) const; // returns the difference of two Time objects
	bool operator==(const Time&) const; // compares two Time objects and returns True if first < second
	bool operator<(const Time&) const; // compares two Time objects and returns True if first < second
	bool operator>(const Time&) const; // compares two Time objects and returns True if first > second
	float time_dec ();
};

class Appointment
{
protected:
	Date date;
	Time start_time, end_time;
	char description[40], location[40];
public:
	Appointment();
	virtual void get();
	virtual void print() const;
	Date get_date() const;
	Time get_start_time() const;
	Time get_end_time() const;
};

class Session : public Appointment
{
protected:
	char client_id[10], fname[20], lname[20];
	float hourly_charge;
public:
	using Appointment::Appointment;
	Session();
	~Session();
	using Appointment::get;
	using Appointment::print;
	using Appointment::get_date;
	using Appointment::get_start_time;
	using Appointment::get_end_time;
	void virtual set();
	void read();
	virtual void print() const;
	float get_charge();
	const char* get_id();
	const char* get_lname();
	const char * get_fname();
};

class ClientSession : public Session
{
public:
	ClientSession();
	~ClientSession();
};

class CourtSession : public Session
{
protected:
	char courtName[20], location[20];
public:
	CourtSession();
	~CourtSession();
	void set() override;
	void print() const override; 
};
#endif !Class_h