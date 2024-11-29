#include "exception.h"

#ifndef MYDATE_
#define MYDATE_

class DateTime
{
	int day_; // день.
	int month_; // месяц.
	int year_; // год.
	
	int JD_; // Юлианский день.

	int hours_; // часы.
	int minutes_; // минуты.

	int all_; // все время в минутах.
	char time_str_[6]; // время-строка, введенная пользователем.

	static bool readDate (const char* str, char date[3][5])
	{
		int countDot = 0;
		int countNum = 0;

		for (int i = 0; str[i] != '\0'; ++i)
		{
			if (str[i] == '.' && ++countDot < 3 && countNum > 0)
			{
				countNum = 0;
				continue;
			}

			if (isdigit (str[i]) != 0 && ((countDot < 2 && countNum < 2) || (countDot == 2 && countNum < 4)))
			{
				date[countDot][countNum++] = static_cast<char>(str[i]);
				continue;
			}

			return false;
		}

		return true;
	}
	static bool readTime (const char* str, char time[2][3])
	{
		int countDot = 0;
		int countNum = 0;

		for (int i = 0; str[i] != '\0'; ++i)
		{
			if (str[i] == ':' && ++countDot < 2 && countNum > 0)
			{
				countNum = 0;
				continue;
			}

			if (isdigit (str[i]) != 0 && (countDot < 2 && countNum < 2))
			{
				time[countDot][countNum++] = static_cast<char>(str[i]);
				continue;
			}

			return false;
		}

		return true;
	}

	int GtoJD () const;

	void checkDate () const;
	bool isRightTime () const;

public:
	DateTime (const char* sdate = "", const char* stime = "");

	void checkDT () const;	
	bool isLeap () const;

	void printDate (std::ostream& out = std::cout) const;
	void printTime (std::ostream& out = std::cout) const;

	int getJD () const;
	int getAll () const;

	friend std::ostream& operator<< (std::ostream&, const DateTime&);
};

bool operator== (const DateTime&, const DateTime&);
bool operator< (const DateTime&, const DateTime&);

#endif //MYDATE_