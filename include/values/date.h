#ifndef DATE_H
#define DATE_H

#include"alias.h"

#include<string>

using namespace alias;

class Date {
public:
    // validation
    static bool validateDate(const String& date, const bool verbose);
    static bool validateDay(const int day, const int month, const int year);
    static bool validateMonth(const int month);
    static bool validateYear(const int year);
    // slicers
    static int sliceDayFromDate(const String& date);
    static int sliceDayFromDate(const Date& date);
    static int sliceMonthFromDate(const String& date);
    static int sliceMonthFromDate(const Date& date);
    static int sliceYearFromDate(const String& date);
    static int sliceYearFromDate(const Date& date);
    // assemble from numbers
    static String assembleDate(const int day, const int month, const int year);
    // misc utils
    static bool isLeapYear(const int year);
    static String getCurrentDate();
    static int getCurrentYear();
    // constructors
    Date(
        const String& value
    ) : value(Date::validateDate(value,VERBOSE) ? value : "") {};

    Date(
        const int day,
        const int month,
        const int year
    ) : value(Date::assembleDate(day, month, year)) {};

    Date() : value(Date::getCurrentDate()) {};

    const String& getValue() const;
    const int getDay() const;
    const int getMonth() const;
    const int getYear() const;
private:
    static constexpr bool VERBOSE = true;
    const String value;

    static void printInvalidDateErrorMessage(
        const String& source,
        const String& fullDate,
        const String& warning
    );
};

#endif
