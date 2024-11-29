#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#ifndef MYEXCEPTION_
#define MYEXCEPTION_

class exception
{
	const char* message_; // сообщение.
	char* string_; // строка - информация об ошибке.
	int number_; // число - информация об ошибке.
	unsigned char status_; // статус ошибки: 0 - без информации, 1 - есть строка-информация, 2 - есть число-информация.

public:
	exception (const char*);
	exception (const char*, const char*);
	exception (const char*, int);

	const char* mes () const;
	const char* str () const;
	int num () const;
	unsigned char st () const;

	~exception ();
};

std::ostream& operator<< (std::ostream&, const exception&);

#endif //MYEXCEPTION_
