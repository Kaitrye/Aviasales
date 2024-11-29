#include "trip.h"

Trip::Trip (const char* number, const char* air_out, const char* air_in,
	  const char* d_out, const char* t_out, const char* d_in, const char* t_in,
	  int count, double price) : ID_ (-1), count_ (count), price_ (price)
{
	strncpy (number_, number, 8);
	strncpy (air_out_, air_out, 4);
	strncpy (air_in_, air_in, 4);

	out_ = DateTime { d_out, t_out };
	in_ = DateTime { d_in, t_in };
}

int Trip::getID () const
{
	return ID_;
}
void Trip::setID (int ID)
{
	ID_ = ID;
}
const char* Trip::getNumber () const
{
	return number_;
}
const char* Trip::getAir_out () const
{
	return air_out_;
}
const char* Trip::getAir_in () const
{
	return air_in_;
}
const DateTime& Trip::getDT_out () const
{
	return out_;
}
const DateTime& Trip::getDT_in () const
{
	return in_;
}
int Trip::getCount () const
{
	return count_;
}
void Trip::setCount (int count)
{
	count_ = count;
}
double Trip::getPrice () const
{
	return price_;
}

std::ostream& operator<< (std::ostream& out, const Trip& A)
{
	out << A.getNumber() << ", " << A.getAir_out() << ", " << A.getAir_in() << ", "
		<< A.getDT_out() << ", " << A.getDT_in() << ", " << A.getCount() << ", " << std::fixed << std::setprecision(2) << A.getPrice();

	return out;
}

bool comp_by_price (const Trip& left, const Trip& right)
{
	return ((left.getPrice () < right.getPrice ()) || (left.getPrice () == right.getPrice () && left.getDT_out () < right.getDT_out ()));
}
bool comp_by_dt (const Trip& left, const Trip& right)
{
	return (left.getDT_out() < right.getDT_out());
}
bool comp_by_all (const Trip& left, const Trip& right)
{
	return ((left.getDT_out () < right.getDT_out ()) || (left.getDT_out () == right.getDT_out () && strcmp(left.getNumber (), right.getNumber ()) < 0)
			|| (left.getDT_out () == right.getDT_out () && strcmp (left.getNumber (), right.getNumber ()) == 0 && left.getPrice() < right.getPrice()));
}