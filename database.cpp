#include "database.h"

Database::Database () : count_ (0), ID_ (0), begin_ (nullptr), end_ (nullptr) {}

Node* Database::findRecord_byID (int ID) const
{
	Node* now = begin_;
	while (now != nullptr)
	{
		if (now->data_.getID () == ID)
		{
			return now;
		}

		now = now->next_;
	}

	return nullptr;
}
Node* Database::findRecord_sch (const char* number, const char* air_in, int time_all) const
{
	Node* now = begin_;
	while (now != nullptr)
	{
		if (strcmp(now->data_.getNumber (), number) == 0 && strcmp (now->data_.getAir_in (), air_in) == 0 && now->data_.getDT_out ().getAll() == time_all)
		{
			return now;
		}

		now = now->next_;
	}

	return nullptr;
}

void Database::push_back (Trip& tr)
{
	int ID = tr.getID();
	if (ID == -1)
	{
		tr.setID (++ID_);
	}
	else
	{
		tr.setID (ID);
	}

	Node* tmp = new Node;
	tmp->data_ = tr;

	if (begin_ != nullptr)
	{
		end_->next_ = tmp;
		tmp->prev_ = end_;
		end_ = tmp;
	} 
	else
	{
		begin_ = end_ = tmp;
	}

	++count_;
}
void Database::erase (int ID)
{
	Node* target = findRecord_byID (ID);
	if (target == nullptr)
	{
		return;
	}

	Node* parent = target->prev_;
	Node* child = target->next_;

	if (parent != nullptr)
	{
		parent->next_ = child;
		if (child != nullptr)
		{
			child->prev_ = parent;
		} else
		{
			end_ = parent;
		}
	} else
	{
		begin_ = child;
		if (child != nullptr)
		{
			child->prev_ = parent;
		} else
		{
			end_ = nullptr;
		}
	}

	delete target;
}

void Database::print_withID (std::ostream& out)
{
	sort_by_all();

	Node* now = begin_;
	while (now != nullptr)
	{
		out << now->data_.getID () << ", " << now->data_ << std::endl;
		now = now->next_;
	}
}
void Database::print (std::ostream& out)
{
	sort_by_all ();

	Node* now = begin_;
	while (now != nullptr)
	{
		out << now->data_ << std::endl;
		now = now->next_;
	}
}
void Database::print_from ()
{
	sort_by_price ();

	Node* now = begin_;
	while (now != nullptr)
	{
		std::cout << now->data_ << std::endl;
		now = now->next_;
	}
}
void Database::print_sch ()
{
	sort_by_dt ();

	Node* now = begin_;
	while (now != nullptr)
	{
		std::cout << now->data_.getNumber () << ", " << now->data_.getAir_in () << ", ";
		now->data_.getDT_out ().printTime ();
		std::cout << std::endl;

		now = now->next_;
	}
}

void Database::sort (bool (*comp)(const Trip&, const Trip&))
{
	if (begin_ == end_)
	{
		return;
	}
	bool isSorted = false;
	Database tmp[2];

	while (!isSorted)
	{
		unsigned char p = 0;
		tmp[p].begin_ = tmp[p].end_ = begin_;
		tmp[1 - p].begin_ = tmp[1 - p].end_ = nullptr;
		begin_ = begin_->next_;

		// split
		while (begin_ != nullptr)
		{
			if (comp (begin_->data_, tmp[p].end_->data_))
			{
				p = 1 - p;
			}

			if (tmp[p].begin_ != nullptr)
			{
				tmp[p].end_->next_ = begin_;
				tmp[p].end_ = begin_;
			} else
			{
				tmp[p].begin_ = tmp[p].end_ = begin_;
			}

			begin_ = begin_->next_;
		}

		if (tmp[p].end_ != nullptr)
		{
			tmp[p].end_->next_ = nullptr;
		}

		if (tmp[1 - p].end_ != nullptr)
		{
			tmp[1 - p].end_->next_ = nullptr;
		}

		// merge
		if (tmp[1 - p].begin_ != nullptr)
		{
			p = (comp (tmp[0].begin_->data_, tmp[1].begin_->data_)) ? 0 : 1;
			begin_ = end_ = tmp[p].begin_;

			tmp[p].begin_ = tmp[p].begin_->next_;

			while (tmp[p].begin_ != nullptr)
			{
				bool s1 = comp (tmp[p].begin_->data_, end_->data_);
				bool s2 = comp (tmp[1 - p].begin_->data_, end_->data_);

				if (s1 == s2)
				{
					p = (comp (tmp[0].begin_->data_, tmp[1].begin_->data_)) ? 0 : 1;
				} else
				{
					if (s1)
					{
						p = 1 - p;
					}
				}

				end_->next_ = tmp[p].begin_;
				end_ = end_->next_;
				tmp[p].begin_ = tmp[p].begin_->next_;
			}

			end_->next_ = tmp[1 - p].begin_;
			end_ = tmp[1 - p].end_;
		} else
		{
			isSorted = true;
			begin_ = tmp[p].begin_;
			end_ = tmp[p].end_;
			tmp[p].begin_ = tmp[p].end_ = nullptr;
		}
	}
}
void Database::sort_by_price ()
{
	sort (comp_by_price);
}
void Database::sort_by_dt ()
{
	sort (comp_by_dt);
}
void Database::sort_by_all ()
{
	sort (comp_by_all);
}

void Database::schedule (const char* air_out, const DateTime& dt) const
{
	Database DB;

	Node* now = begin_;
	while (now != nullptr)
	{
		if (strcmp (now->data_.getAir_out (), air_out) == 0 && now->data_.getDT_out ().getJD() == dt.getJD() && 
			DB.findRecord_sch(now->data_.getNumber(), now->data_.getAir_in (), now->data_.getDT_out ().getAll()) == nullptr)
		{
			DB.push_back(now->data_);
		}
		
		now = now->next_;
	}

	DB.print_sch();
}
void Database::from_to_on (const char* air_out, const char* air_in, const DateTime& dt) const
{
	Database DB;

	Node* now = begin_;
	while (now != nullptr)
	{
		if (strcmp (now->data_.getAir_out (), air_out) == 0 && strcmp (now->data_.getAir_in (), air_in) == 0 && 
			now->data_.getDT_out ().getJD () == dt.getJD () && now->data_.getCount () > 0)
		{
			DB.push_back(now->data_);
		}

		now = now->next_;
	}

	DB.print_from();
}
void Database::find_to (const char* air_out, const char* air_in) const 
{
	Database out_in;
	Database out;
	Database in;

	Node* now = begin_;
	while (now != nullptr)
	{
		if (now->data_.getCount () > 0)
		{
			if (strcmp (now->data_.getAir_out (), air_out) == 0)
			{
				if (strcmp (now->data_.getAir_in (), air_in) == 0)
				{
					out_in.push_back (now->data_);
				} else
				{
					out.push_back (now->data_);
				}
			} else if (strcmp (now->data_.getAir_in (), air_in) == 0)
			{
				in.push_back (now->data_);
			}
		}

		now = now->next_;
	}

	out_in.sort_by_price();
	double min = (out_in.begin_ != nullptr) ? out_in.begin_->data_.getPrice() : -1.0;

	Node* first = nullptr;
	Node* second = nullptr;

	now = out.begin_;
	while (now != nullptr)
	{
		Node* tmp = in.begin_;
		while (tmp != nullptr)
		{
			if (strcmp(tmp->data_.getAir_out (), now->data_.getAir_in ()) == 0 && now->data_.getDT_in() < tmp->data_.getDT_out ())
			{
				double sum = now->data_.getPrice () + tmp->data_.getPrice ();
				if (min == -1.0 || sum < min )
				{
					min = sum;
					first = now;
					second = tmp;
				}
			}

			tmp = tmp->next_;
		}

		now = now->next_;
	}

	if (first != nullptr)
	{
		std::cout << first->data_ << std::endl;
		std::cout << second->data_ << std::endl;
	} else if (out_in.begin_ != nullptr)
	{
		std::cout << out_in.begin_->data_ << std::endl;
	} else
	{
		throw exception{ "no tickets" };
	}
}
void Database::buy (const char* number, const DateTime& dt)
{
	Database DB;

	Node* now = begin_;
	while (now != nullptr)
	{
		if (strcmp (now->data_.getNumber (), number) == 0 && now->data_.getDT_out ().getJD () == dt.getJD () && now->data_.getCount () > 0)
		{
			DB.push_back (now->data_);
		}

		now = now->next_;
	}

	if (DB.begin_ == nullptr)
	{
		throw exception{ "no tickets" };
	}

	DB.sort_by_price ();
	now = findRecord_byID(DB.begin_->data_.getID());

	std::cout << now->data_.getPrice() << std::endl;

	int count = now->data_.getCount() - 1;
	now->data_.setCount(count);
}

void Database::export_to(const char* filename)
{
	std::ofstream outFile(filename);
	if (!outFile)
	{
		throw exception{ "Can not open file" };
	}

	print(outFile);

	outFile.close();
}

void Database::clear ()
{
	Node* now;
	while (begin_ != nullptr)
	{
		now = begin_->next_;
		delete begin_;
		begin_ = now;
	}

	end_ = nullptr;
	count_ = 0;
}
void Database::clear_zero ()
{
	Node* now = begin_;
	Node* parent;
	Node* child;

	while (now != nullptr)
	{
		parent = now->prev_;
		child = now->next_;

		if (now->data_.getCount() == 0)
		{
			if (parent != nullptr)
			{
				parent->next_ = child;
				if (child != nullptr)
				{
					child->prev_ = parent;
				} else
				{
					end_ = parent;
				}
			} else
			{
				begin_ = child;
				if (child != nullptr)
				{
					child->prev_ = parent;
				} else
				{
					end_ = nullptr;
				}
			}

			delete now;
		}

		now = child;
	}
}

void Database::load (const char* filename)
{
	std::ifstream inFile(filename, std::ios_base::binary);
	if (!inFile)
	{
		throw exception{ "Can not open database" };
	}

	clear();

	inFile.read (reinterpret_cast<char*>(&count_), sizeof(count_));
	inFile.read (reinterpret_cast<char*>(&ID_), sizeof (ID_));

	Trip tr;
	while (inFile.peek () != EOF)
	{
		inFile.read (reinterpret_cast<char*>(&tr), sizeof (tr));
		push_back(tr);
	}

	inFile.close();
}
void Database::save (const char* filename) const
{
	std::ofstream outFile (filename, std::ios_base::binary);
	if (!outFile)
	{
		throw exception{ "Can not write to file" };
	}

	outFile.write (reinterpret_cast<const char*> (&count_), sizeof (count_));
	outFile.write (reinterpret_cast<const char*> (&ID_), sizeof (ID_));

	Node* now = begin_;
	while (now != nullptr)
	{
		outFile.write (reinterpret_cast<const char*>(&(now->data_)), sizeof (now->data_));
		now = now->next_;
	}

	outFile.close();
}

Database::~Database ()
{
	clear ();
}