#include "trip.h"

#ifndef MYTBASE_
#define MYTBASE_

struct Node 
{
	Trip data_; // данные о рейсе.
	Node* next_ = nullptr; // ссылка на следующий элемент.
	Node* prev_ = nullptr; // ссылка на предыдущий элемент.
};

class Database
{
	int count_; // количество записей в базе данных.
	int ID_; // внутренний ID базы данных, присваиваемый автоматически новым записям.
	Node* begin_; // ссылка на первый элемент.
	Node* end_; // ссылка на последний элемент.

	Node* findRecord_byID (int ID) const;
	Node* findRecord_sch (const char*, const char*, int) const;
	void print (std::ostream& out = std::cout);
	void print_sch ();
	void print_from ();
	void sort (bool (*comp)(const Trip&, const Trip&));

public:
	Database();

	void push_back (Trip&);
	void erase (int);

	void print_withID (std::ostream& out = std::cout);
	void export_to (const char*);

	void load (const char*);
	void save (const char*) const;

	void sort_by_price ();
	void sort_by_dt ();
	void sort_by_all ();
	
	void schedule (const char*, const DateTime&) const;
	void from_to_on (const char*, const char*, const DateTime&) const;
	void find_to(const char*, const char*) const;
	void buy (const char*, const DateTime&);

	void clear ();
	void clear_zero ();

	~Database ();
};

#endif //_MYTBASE_