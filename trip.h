#include "datetime.h"

#ifndef MYTRIP_
#define MYTRIP_

class Trip
{
	int ID_; // номер записи в базе данных, присваивается автоматически.
	char number_[8]; // номер рейса.
	char air_out_[4]; // аэропорт вылета.
	char air_in_[4]; // аэропорт прибытия.
	DateTime out_; // дата и время вылета.
	DateTime in_; // дата и время прибытия.
	int count_; // количество билетов.
	double price_; // цена одного билета.

public:
	Trip (const char* number = "", const char* air_out = "", const char* air_in = "", 
		  const char* d_out = "", const char* t_out = "", const char* d_in = "", const char* t_in = "",
		  int count = 0, double price = 0);

	int getID () const;
	void setID (int);
	const char* getNumber () const;
	const char* getAir_out () const;
	const char* getAir_in () const;
	const DateTime& getDT_out () const;
	const DateTime& getDT_in () const;
	int getCount () const;
	void setCount (int);
	double getPrice () const;
};

std::ostream& operator<< (std::ostream& out, const Trip& A);

bool comp_by_price (const Trip&, const Trip&);
bool comp_by_dt (const Trip&, const Trip&);
bool comp_by_all (const Trip&, const Trip&);

#endif //MYTRIP_