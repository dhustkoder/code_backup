#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>


struct Date
{
	int day, hours, minutes, seconds;
	Date operator-(Date& other);
	friend std::ostream& operator<<(std::ostream&, Date&);
};

static Date from;
static Date to;

int setDate(Date& date);


int main()
{

	if (!setDate(from))
		return -1;
	else if (!setDate(to))
		return -1;

	Date duration = to - from ;
	std::cout << duration;
}


int setDate(Date& date)
{
	static std::string strDay, strTime;
	std::getline(std::cin, strDay);
	std::getline(std::cin, strTime);

	auto isDigit = [](char x) {return std::isdigit(x); };

	//search day
	date.day = std::atoi(std::string(std::find_if(strDay.begin(), strDay.end(), isDigit), strDay.end()).c_str());


	// search hours
	auto itr1 = std::find_if(strTime.begin(), strTime.end(), isDigit);
	auto itr2 = std::find_if_not(itr1, strTime.end(), isDigit);
	if (itr1 == strTime.end() || itr2 == strTime.end()) return 0;
	date.hours = std::atoi(std::string(itr1, itr2).c_str());

	// search minutes
	itr1 = std::find_if(itr2, strTime.end(), isDigit);
	itr2 = std::find_if_not(itr1, strTime.end(), isDigit);
	if (itr1 == strTime.end() || itr2 == strTime.end()) return 0;
	date.minutes = std::atoi(std::string(itr1, itr2).c_str());

	// search seconds
	itr1 = std::find_if(itr2, strTime.end(), isDigit);
	date.seconds = std::atoi(std::string(itr1, strTime.end()).c_str());

	// check values
	if (date.day < 30
		&& date.hours < 24
		&& date.minutes < 60
		&& date.seconds < 60)
		return 1;

	return 0;
}


Date Date::operator-(Date& other)
{
	Date result;

	result.day = this->day - other.day;
	

	result.hours = this->hours - other.hours;
	result.minutes = this->minutes - other.minutes;
	result.seconds = this->seconds - other.seconds;

	if (result.hours < 0) {
		result.hours += 24;
		--result.day;
	}

	if (result.minutes < 0) {
		result.minutes += 60;
		--result.hours;
	}

	if (result.seconds < 0) {
		result.seconds += 60;
		--result.minutes;
	}




	return result;

}


std::ostream& operator<<(std::ostream& os, Date& date) 
{
	os << date.day      << " dia(s)"     << std::endl
		<< date.hours   << " hora(s)"    << std::endl
		<< date.minutes << " minuto(s)"  << std::endl
		<< date.seconds << " segundo(s)" << std::endl;

	return os;
}