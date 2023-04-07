#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<ctime>
#include <vector>
#include <string>
#include <iomanip>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;
	short _Hour;
	short _Minute;
	short _Second;
public:

	clsDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
		_Hour = now->tm_hour;
		_Minute = now->tm_min;
		_Second = now->tm_sec;
	}

	clsDate(string Date) {

		vector <string> vElements;
		vElements = clsString::Split(Date, "/");

		_Day = stoi(vElements[0]);
		_Month = stoi(vElements[1]);
		_Year = stoi(vElements[2]);

	}

	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}	

	clsDate(short DayOrder, short Year) {

		*this = GetDateFromDayOrder(DayOrder, Year);

	}

	void SetDay(short Day) {
		_Day = Day;
	}

	short GetDay() {
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) {
		_Month = Month;
	}
	
	short GetMonth() {
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{ _Year = Year; }
	
	short GetYear()
	{ return _Year; }

	__declspec(property(get = GetYear, put = SetYear)) short Year;
	
		
	void Print() {
		cout << DateToString() << endl;
	}

	static string DateToString(clsDate Date) {
		string StringDate = "";
		StringDate += to_string(Date._Day) + "/";
		StringDate += to_string(Date._Month) + "/";
		StringDate += to_string(Date._Year);
		StringDate += " - ";
		StringDate += to_string(Date._Hour) + ":";
		StringDate += to_string(Date._Minute) + ":";
		StringDate += to_string(Date._Second);
		return StringDate;
	}

	string DateToString() {
		return DateToString(*this);
	}

	static clsDate GetSystemDate() {
		//system date
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;
		Year = now->tm_year + 1900; 
		Month = now->tm_mon + 1;  
		Day = now->tm_mday; return clsDate(Day, Month, Year);   
	}

	static bool IsValidDate(clsDate Date) {
		return (Date._Year > 0) &&
			(Date._Month > 0 && Date._Month < 13) &&
			(Date._Day > 0 && Date._Day <= NumOfDaysInAMonth(Date._Year, Date._Month));
	}

	bool IsValid() {
		return IsValidDate(*this);
	}

	static bool IsLeapYear(short Year) {
		return (Year % 400 == 0) || ((Year % 4 == 0) && (Year % 100 != 0));
	}

	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}

	static short NumOfDaysInAMonth(short Year, short Month) {
		if (Month < 1 || Month >12) return 0;

		short Arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return Month == 2 ? IsLeapYear(Year) ? 29 : 28 : Arr[Month - 1];
	}

	short NumOfDaysInAMonth() {
		return NumOfDaysInAMonth(_Year, _Month);
	}

	static short NumberOfDaysInAYear(short Year)
	{
		return  IsLeapYear(Year) ? 365 : 364;
	}

	short NumberOfDaysInAYear() {
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year) {
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear() {
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year) {
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear() {
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year) {
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear() {
		return NumberOfSecondsInAYear(_Year);
	}

	static short NumOfHoursInAMonth(short Year, short Month) {
		return NumOfDaysInAMonth(Year, Month) * 24;
	}

	short NumOfHoursInAMonth() {
		return NumOfHoursInAMonth(_Year, _Month);
	}

	static short NumOfMinutesInAMonth(short Year, short Month) {
		return NumOfHoursInAMonth(Year, Month) * 60;
	}

	short NumOfMinutesInAMonth() {
		return NumOfMinutesInAMonth(_Year, _Month);
	}

	static short NumOfSecondsInAMonth(short Year, short Month) {
		return NumOfMinutesInAMonth(Year, Month) * 60;
	}

	short NumOfSecondsInAMonth() {
		NumOfSecondsInAMonth(_Year, _Month);
	}

	static short DayOfWeekOrder(short Year, short Month, short Day) {
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + (12 * a) - 2;
		short l = (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12));
		return l % 7;
	}

	short DayOfWeekOrder() {
		return DayOfWeekOrder(_Year, _Month, _Day);
	}

	static string DayShortName(short DayOfWeekOrder) {
		string Arr[] = { "Sunday","Monday","Tuesday","Wednesday", "Thursday", "Friday", "Saturday" };

		return Arr[DayOfWeekOrder];
	}

	static string DayShortName(short Year, short Month, short Day) {
		string Arr[] = { "Sunday","Monday","Tuesday","Wednesday", "Thursday", "Friday", "Saturday" };

		return Arr[DayOfWeekOrder(Year, Month, Day)];
	}

	string DayShortName() {
		return DayShortName(_Year, _Month, _Day);
	}

	static string MonthShortName(short Month) {
		string Months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return Months[Month - 1];
	}

	string MonthShortName() {
		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Year, short Month) {

		string Days[] = { "Sun","Mon","Tue","Wed", "Thu", "Fri", "Sat" };


		cout << setw(15) << "___________________" << MonthShortName(Month) << setw(15) << "___________________" << endl << endl;


		for (string Day : Days) cout << setw(5) << Day;
		cout << endl;

		short DayIndex = DayOfWeekOrder(Year, Month, 1);
		short NumOfDays = NumOfDaysInAMonth(Year, Month);

		int i;
		for (i = 0; i < DayIndex; i++)
			cout << setw(5) << " ";

		for (int j = 1; j <= NumOfDaysInAMonth(Year, Month); j++) {
			cout << setw(5) << j;
			if (++i == 7) {
				i = 0;
				cout << endl;
			}
		}
		cout << endl;

	}

	void PrintMonthCalendar() {
		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short Year) {
		cout << setw(35) << "____________________________________" << endl;
		cout << endl << setw(15) << Year << " Calendar" << endl;
		cout << setw(35) << "____________________________________" << endl << endl;

		for (int i = 1; i <= 12; i++) PrintMonthCalendar(Year, i);

	}

	void PrintYearCalendar() {
		PrintYearCalendar(_Year);
	}

	static short DaysFromBeginingOfYear(short Year, short Month, short Day) {

		short Order = 0;

		for (short i = 1; i < Month; i++) Order += NumOfDaysInAMonth(Year, i);
		Order += Day;

		return Order;
	}

	short DaysFromBeginingOfYear() {
		return DaysFromBeginingOfYear(_Year, _Month, _Day);
	}

	static clsDate GetDateFromDayOrder(short Order, short Year) {
		clsDate Date;
		Date._Month = 1;
		Date._Year = Year;
		while (true) {

			if (Order >= NumOfDaysInAMonth(Date._Year, Date._Month)) {
				Order -= NumOfDaysInAMonth(Date._Year, Date._Month);
				if (Date._Month == 12) {
					Date._Year += 1;
					Date._Month = 1;
				}
				else {
					Date._Month++;
				}
			}
			else {
				Date._Day = Order;
				break;
			}
		}
		return Date;
	}
	
	void AddDays(short Days) {
		short RemainingDays = Days + DaysFromBeginingOfYear(_Day, _Month, _Year);
		short MonthDays = 0;
		_Month = 1;
		while (true) {
			MonthDays = NumOfDaysInAMonth(_Month, _Year);
			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				_Month++;
				if (_Month > 12) {
					_Month = 1;
					_Year++;
				}
			}
			else {
				_Day = RemainingDays; break;
			}
		}
	}
	
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		short Order1 = DaysFromBeginingOfYear(Date1._Year, Date1._Month, Date1._Day);
		short Order2 = DaysFromBeginingOfYear(Date2._Year, Date2._Month, Date2._Day);


		if (Date1._Year == Date2._Year) return (Order1 < Order2);
		else return (Date1._Year < Date2._Year);
	}

	bool IsDateBeforeDate2(clsDate Date2) {
		return IsDate1BeforeDate2(*this, Date2);
	}
	
	static bool IsDate1EqualtoDate2(clsDate Date1, clsDate Date2) {
		return Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day;
	}

	bool IsDateEqualToDate2(clsDate Date2) {
		return IsDate1EqualtoDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return Date._Day == NumOfDaysInAMonth(Date._Year, Date._Month);
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {
		return Month == 12;
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate& Date) {
		if (IsLastDayInMonth(Date)) {

			if (IsLastMonthInYear(Date._Month)) {
				Date._Day = 1;
				Date._Month = 1;
				Date._Year += 1;
			}

			else {
				Date._Day = 1;
				Date._Month += 1;
			}

		}
		else Date._Day += 1;


		return Date;
	}

	void AddOneDay() {
		AddOneDay(*this);
	}

	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeLastDay = false) {
		int Counter = 0;
		while (IsDate1BeforeDate2(Date1, Date2)) {
			Counter++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeLastDay ? ++Counter : Counter;
	}

	short GetDifferenceInDays(clsDate Date2, bool IncludeLastDay = false) {
		return GetDifferenceInDays(*this, Date2, IncludeLastDay);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth) {
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}
	
	static clsDate AddXDaysToDate(clsDate& Date, short DaysToAdd) {
		for (short i = 0; i < DaysToAdd; i++)
			Date = AddOneDay(Date);
		return Date;
	}

	void AddXDays(short DaysToAdd) {

		AddXDaysToDate(*this, DaysToAdd);

	}

	static clsDate AddOneWeekToDate(clsDate& Date) {
		return AddXDaysToDate(Date, 7);
	}

	void AddOneWeek() {
		AddOneWeekToDate(*this);
	}

	static clsDate AddXWeeksToDate(clsDate& Date, short WeeksToAdd) {
		for (short i = 0; i < WeeksToAdd; i++) Date = AddOneWeekToDate(Date);
		return Date;
	}

	void AddXWeeks(short WeeksToAdd) {
		AddXWeeksToDate(*this, WeeksToAdd);
	}

	static clsDate AddOneMonthToDate(clsDate& Date) {
		Date = AddXDaysToDate(Date, NumOfDaysInAMonth(Date._Year, Date._Month));
		return Date;
	}

	void AddOneMonth() {
		AddOneMonthToDate(*this);
	}

	static clsDate AddXMonthsToDate(clsDate& Date, short MonthsToAdd) {
		for (short i = 0; i < MonthsToAdd; i++) Date = AddOneMonthToDate(Date);
		return Date;
	}

	void AddXMonths(short MonthsToAdd) {
		AddXMonthsToDate(*this, MonthsToAdd);
	}


	static clsDate AddOneYearToDate(clsDate& Date) {
		return AddXMonthsToDate(Date, 12);
	}

	void AddOneYear() {
		AddOneYearToDate(*this);
	}

	static clsDate AddXYearsToDate(clsDate& Date, short YearsToAdd) {
		Date._Year += YearsToAdd;
		return Date;
	}

	void AddXYears(short YearsToAdd) {
		AddXYearsToDate(*this, YearsToAdd);
	}

	static clsDate AddOneDecadeToDate(clsDate& Date) {
		return AddXYearsToDate(Date, 10);
	}

	void AddOneDecade() {
		AddOneDecadeToDate(*this);
	}

	static clsDate AddXDecadesToDate(clsDate& Date, short DecadesToAdd) {
		Date._Year += (DecadesToAdd * 10);
		return Date;
	}

	void AddXDecades(short DecadesToAdd) {
		AddXDaysToDate(*this, DecadesToAdd);
	}

	static bool IsFirstMonthInYear(short Month) {
		return Month == 1;
	}

	bool IsFirstMonthInYear() {
		return IsFirstMonthInYear(_Month);
	}

	static bool IsFirstDayInMonth(short Day) {
		return Day == 1;
	}
	
	bool IsFirstDayInMonth() {
		return  IsFirstDayInMonth(_Day);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date) {

		if (IsFirstDayInMonth(Date._Day)) {

			if (IsFirstMonthInYear(Date._Month)) {
				Date._Day = 31;
				Date._Month = 12;
				Date._Year -= 1;
			}

			else {
				Date._Month -= 1;
				Date._Day = NumOfDaysInAMonth(Date._Year, Date._Month);

			}

		}
		else Date._Day -= 1;


		return Date;
	}

	void DecreaseOneDay() {
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short DaysToDecrease) {
		for (short i = DaysToDecrease; i > 0; i--) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseXDays(short DaysToDecrease) {
		DecreaseDateByXDays(*this, DaysToDecrease);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {
		return DecreaseDateByXDays(Date, 7);
	}

	void DecreaseOneWeek() {
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, short WeeksToDecrese) {
		for (short i = WeeksToDecrese; i > 0; i--) Date = DecreaseDateByOneWeek(Date);
		return Date;
	}

	void DecreaseXWeeks(short WeeksToDecrese) {
		DecreaseDateByXWeeks(*this, WeeksToDecrese);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {

		if (IsFirstMonthInYear(Date._Month)) {
			Date._Month = 12;
			Date._Year -= 1;
		}
		else
			Date._Month -= 1;

		return Date;
	}

	void DecreaseOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, short MonthsToDecrease) {
		for (short i = MonthsToDecrease; i > 0; i--) DecreaseDateByOneMonth(Date);
		return Date;
	}

	void DecreaseXMonths(short MonthsToDecrease) {
		DecreaseDateByXMonths(*this, MonthsToDecrease);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {
		Date._Year -= 1;
		return Date;
	}

	void DecreaseOneYear() {
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short YearsToDecrease) {
		Date._Year -= YearsToDecrease;
		return Date;
	}

	void DecreaseXYears(short YearsToDecrease) {
		DecreaseDateByXYears(*this, YearsToDecrease);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {
		return DecreaseDateByXYears(Date, 10);
	}

	void DecreaseOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, short DecadesToDecrease) {
		return DecreaseDateByXYears(Date, DecadesToDecrease * 10);
	}

	void DecreaseXDecades(short DecadesToDecrease) {
		DecreaseDateByXDecades(*this, DecadesToDecrease);
	}

	static bool IsEndOfWeek(clsDate Date) {
		return DayOfWeekOrder(Date._Year, Date._Month, Date._Day) == 6;
	}

	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {
		short Order = DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
		return (Order == 5 || Order == 6);
	}

	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBuisnessDay(clsDate Date) {
		return !IsWeekEnd(Date);
	}

	bool IsBuisnessDay() {
		return IsBuisnessDay(*this);
	}

	static short DaysTillEndOfWeek(clsDate Date) {
		return 6 - DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
	}

	short DaysTillEndOfWeek() {
		return DaysTillEndOfWeek(*this);
	}
	
	static short DaysTillEndOfMonth(clsDate Date) {
		return NumOfDaysInAMonth(Date._Year, Date._Month) - Date._Day;
	}

	short DaysTillEndOfMonth() {
		return DaysTillEndOfMonth(*this);
	}

	static short DaysTillEndOfYear(clsDate Date) {
		return IsLeapYear(Date._Year) ? 366 - DaysFromBeginingOfYear(Date._Year, Date._Month, Date._Day) : 365 - DaysFromBeginingOfYear(Date._Year, Date._Month, Date._Day);
	}

	short DaysTillEndOfYear() {
		return DaysTillEndOfYear(*this);
	}

	static short VacationDays(clsDate Date1, clsDate Date2) {
		short Counter = 0;
		short NumOfCycles = GetDifferenceInDays(Date1, Date2);

		for (short i = 0; i < NumOfCycles; i++) {
			if (IsBuisnessDay(Date1)) Counter++;
			Date1 = AddOneDay(Date1);
		}

		return Counter;
	}

	static clsDate VacationEndingDate(clsDate Date1, short NumOfVacDays) {

		while (NumOfVacDays > 0) {
			if (IsWeekEnd(Date1)) {
				Date1 = AddOneDay(Date1);
			}
			else {
				Date1 = AddOneDay(Date1);
				NumOfVacDays--;
			}
		}
		return Date1;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {

		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualtoDate2(Date1, Date2);
	}

	bool IsDateAfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateState { Before = -1, Equal = 0, After = 1 };

	static enDateState CompareDates(clsDate Date1, clsDate Date2) {
		if (IsDate1BeforeDate2(Date1, Date2))	return enDateState::Before;
		else if (IsDate1EqualtoDate2(Date1, Date2)) return enDateState::Equal;
		else return enDateState::After;
	}

	enDateState CompareDate(clsDate Date2) {
		return CompareDates(*this, Date2);
	}

};

