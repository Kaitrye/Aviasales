#include "datetime.h"

DateTime::DateTime (const char* sdate, const char* stime) : day_ (-1), month_ (-1), year_ (-1), JD_ (-1), hours_ (-1), minutes_ (-1), all_ (-1)
{
	char date[3][5] = { "", "", "" };
	char time[2][3] = { "", "" };

	if (readDate (sdate, date))
	{
		day_ = atoi (date[0]);
		month_ = atoi (date[1]);
		year_ = atoi (date[2]);

		JD_ = GtoJD ();
	} else
	{
		throw exception { "Wrong date format", sdate };
	}

	if (readTime (stime, time))
	{
		strncpy (time_str_, stime, 6);
		hours_ = atoi (time[0]);
		minutes_ = atoi (time[1]);

		all_ = hours_ * 60 + minutes_;
	} else
	{
		throw exception { "Wrong time format", stime };
	}
}

int DateTime::GtoJD () const
{
	int a = (14 - month_) / 12;
	int y = year_ + 4800 - a;
	int m = month_ + 12 * a - 3;

	return day_ + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
}

void DateTime::checkDate () const
{
	int countDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeap ())
	{
		countDays[1] = 29;
	}

	if (month_ <= 0 || month_ > 12)
	{
		throw exception { "Month value is invalid", month_ };
	}

	if (day_ == 0 || day_ > countDays[month_ - 1])
	{
		throw exception { "Day value is invalid", day_ };
	}
}
bool DateTime::isRightTime () const
{
	return (hours_ >= 0 && hours_ < 24 && minutes_ >= 0 && minutes_ < 60);
}

void DateTime::checkDT () const
{
	if (!isRightTime ())
	{
		throw exception { "Time value is invalid", time_str_ };
	}

	checkDate ();
}
bool DateTime::isLeap () const
{
	return (year_ % 400 == 0 || (year_ % 4 == 0 && year_ % 100 != 0));
}

int DateTime::getJD () const
{
	return JD_;
}
int DateTime::getAll () const
{
	return all_;
}

void DateTime::printDate (std::ostream& out) const
{
	out << year_ << ".";

	if (month_ < 10)
	{
		out << 0;
	}
	out << month_ << ".";

	if (day_ < 10)
	{
		out << 0;
	}
	out << day_ << " ";
}
void DateTime::printTime (std::ostream& out) const
{
	if (hours_ < 10)
	{
		out << 0;
	}
	out << hours_ << ":";

	if (minutes_ < 10)
	{
		out << 0;
	}
	out << minutes_;
}

std::ostream& operator<< (std::ostream& out, const DateTime& dt)
{
	dt.printDate(out);
	dt.printTime(out);

	return out;
}

bool operator== (const DateTime& left, const DateTime& right)
{
	return (left.getJD () == right.getJD () && left.getAll () == right.getAll ());
}
bool operator< (const DateTime& left, const DateTime& right)
{
	return ( (left.getJD () < right.getJD ()) || (left.getJD () == right.getJD () && left.getAll () < right.getAll ()) );
}