#include "exception.h"

exception::exception (const char* message) : message_ (message), string_ (nullptr), number_ (0), status_ (0) {}
exception::exception (const char* message, const char* string) : message_ (message), number_ (0), status_ (1)
{
	size_t size = strlen (string) + 1;
	string_ = new char[size];
	strncpy (string_, string, size);
}
exception::exception (const char* message, int number) : message_ (message), string_ (nullptr), number_ (number), status_ (2) {}

const char* exception::mes () const
{
	return message_;
}
const char* exception::str () const
{
	return string_;
}
int exception::num () const
{
	return number_;
}
unsigned char exception::st () const
{
	return status_;
}

std::ostream& operator<< (std::ostream& out, const exception& error)
{
	out << error.mes();

	if (error.st() == 1)
	{
		out << ": " << error.str ();
	}
	else if (error.st() == 2)
	{
		out << ": " << error.num ();
	}
	
	return out;
}

exception::~exception ()
{
	delete[] string_;
}