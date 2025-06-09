#include "date.h"

#include<string>
#include<sstream>
#include<ctime>
#include<iostream>
#include <iomanip>

// validation
bool Date::validateDate(const std::string& date, const bool verbose) {
    // needed local variables
    std::stringstream ss(date);
    int day;
    int month;
    int year;
    char delimiter1, delimiter2;

    // take it from the accepted format
    if (!(ss >> year >> delimiter1 >> month >> delimiter2 >> day) || (delimiter1 != delimiter2) || (delimiter1 != '-' && delimiter1 != '/')) {
        if (verbose)
            printInvalidDateErrorMessage(date, date, "Check if the date is in the [yyyy/MM/dd] format. ([yyyy-MM-dd] format is also supported).");
        return false;
    }

    // validate month
    if (!Date::validateMonth(month)) {
        if (verbose)
            printInvalidDateErrorMessage(std::to_string(month), date, "Check if the month provided is a number between 1 and 12.");
        return false;
    }

    // validate year
    if (!Date::validateYear(year)) {
        if (verbose)
            printInvalidDateErrorMessage(std::to_string(year), date, "Check if the year provided is valid. It shouldn't be higher than the current year [" + std::to_string(Date::getCurrentYear()) + "] neither lower than 1900.");
        return false;
     }

    // validate day
    if (!Date::validateDay(day, month, year)) {
        if (verbose)
            printInvalidDateErrorMessage(std::to_string(day), date, "Check if the provided day is valid for the month and year provided.");
        return false;
    }

    return true;
}

bool Date::isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::validateDay(const int day, const int month, const int year) {
    // max days in months that don't depend on the leap year
    static const int daysInMonth[12] = { 31, -1, 31, 30, 31, 30,
                                   31, 31, 30, 31, 30, 31 };
    // special case for february
    if (month == 2) {
        if (Date::isLeapYear(year))
            return day <= 29;
        return day <= 28;
    }
    // else, proceed normally
    return (day <= daysInMonth[month - 1]) && (day >= 1);
}

bool Date::validateMonth(const int month) {
    return (month <= 12 && month >= 1);
}

bool Date::validateYear(const int year) {
    return (year >= 1900) && (year <= Date::getCurrentYear());
}

// slicers
int Date::sliceYearFromDate(const std::string& date) {
    std::stringstream ss(date);
    int year;
    ss >> year;
    return year;
}

int Date::sliceYearFromDate(const Date& date) {
    std::stringstream ss(date.getValue());
    int year;
    ss >> year;
    return year;
}

int Date::sliceMonthFromDate(const std::string& date) {
    std::stringstream ss(date);
    int month;
    int intThrash;
    char delimiter;
    ss >> intThrash >> delimiter >> month;
    return month;
}

int Date::sliceMonthFromDate(const Date& date) {
    std::stringstream ss(date.getValue());
    int month;
    int intThrash;
    char delimiter;
    ss >> intThrash >> delimiter >> month;
    return month;
}

int Date::sliceDayFromDate(const std::string& date) {
    std::stringstream ss(date);
    int day;
    int intThrash;
    char delimiter;
    ss >> intThrash >> delimiter >> intThrash >> delimiter >> day;
    return day;
}

int Date::sliceDayFromDate(const Date& date) {
    std::stringstream ss(date.getValue());
    int day;
    int intThrash;
    char delimiter;
    ss >> intThrash >> delimiter >> intThrash >> delimiter >> day;
    return day;
}

// assemble from numbers
std::string Date::assembleDate(const int day, const int month, const int year) {
    std::string date;
    date = year + '/' + month + '/' + day;
    return date;
}

// error message

void Date::printInvalidDateErrorMessage(const std::string& source, const std::string& fullDate, const std::string& warning) {
    std::cout << "The date [" << fullDate << "] isn't valid. Found error in [" << source << "]. Warning: " << warning << "." << std::endl;
}

// helper function to get the current year

int Date::getCurrentYear() {
    std::time_t now = std::time(nullptr);
    return std::localtime(&now)->tm_year + 1900;
}

std::string Date::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* localTimeNow = std::localtime(&now);

    std::stringstream ss;
    ss << std::setfill('0')
    << std::setw(4) << (localTimeNow->tm_year + 1900) << "/"
    << std::setw(2) << (localTimeNow->tm_mon + 1) << "/"
    << std::setw(2) << (localTimeNow->tm_mday);
    /*
    ss << std::setfill('0') << std::setw(2) << localTimeNow->tm_mday << "/" << std::setw(2) << localTimeNow << (localTimeNow->tm_mon + 1) << "/" << std::setw(4) << (localTimeNow->tm_year + 1900);
    */

    std::string currentDateString = ss.str();
    return currentDateString;
}

// getter

const std::string& Date::getValue() const {
    return this->value;
}

const int Date::getDay() const {
    return Date::sliceDayFromDate(this->getValue());
}

const int Date::getMonth() const {
    return Date::sliceMonthFromDate(this->getValue());
}

const int Date::getYear() const {
    return Date::sliceYearFromDate(this->getValue());
}
