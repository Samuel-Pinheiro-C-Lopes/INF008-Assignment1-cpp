#ifndef DATE_H
#define DATE_H

#include<string>

class Date {
public:
    // validation
    static bool validateDate(const std::string& date, const bool verbose);
    static bool validateDay(const int day, const int month, const int year);
    static bool validateMonth(const int month);
    static bool validateYear(const int year);
    // slicers
    static int sliceDayFromDate(const std::string& date);
    static int sliceDayFromDate(const Date& date);
    static int sliceMonthFromDate(const std::string& date);
    static int sliceMonthFromDate(const Date& date);
    static int sliceYearFromDate(const std::string& date);
    static int sliceYearFromDate(const Date& date);
    // assemble from numbers
    static std::string assembleDate(const int day, const int month, const int year);
    // misc utils
    static bool isLeapYear(const int year);
    static std::string getCurrentDate();
    static int getCurrentYear();
    // constructors
    Date(const std::string& value) : value(Date::validateDate(value,VERBOSE) ? value : "") {};
    Date(const int day, const int month, const int year) : value(Date::assembleDate(day, month, year)) {};
    Date() : value(Date::getCurrentDate()) {};
    const std::string& getValue() const;
    const int getDay() const;
    const int getMonth() const;
    const int getYear() const;
private:
    static constexpr bool VERBOSE = true;
    const std::string value;
    static void printInvalidDateErrorMessage(const std::string& source, const std::string& fullDate, const std::string& warning);
};

#endif
