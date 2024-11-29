#include "database.h"

int main ()
{
	Database DB;

	char str[1024];
	bool action = true;

	while (action)
	{

		std::cout << "> ";
		std::cin.getline (str, 1024);

		bool new_arg = true;
		int argc = 0;
		for (int i = 0; str[i] != '\0'; ++i)
		{
			if (str[i] != ' ' && str[i] != ',' && new_arg)
			{
				++argc;
				new_arg = false;
			} else if (str[i] == ' ' || str[i] == ',')
			{
				new_arg = true;
			}
		}

		if (argc == 0)
		{
			std::cout << exception ("Unknown command") << std::endl;
			continue;
		}

		char** argv = new char* [argc];
		argv[0] = str;
		int index = 0;
		new_arg = true;

		for (int i = 0; str[i] != '\0'; ++i)
		{
			if (str[i] != ' ' && str[i] != ',' && new_arg)
			{
				argv[index++] = str + i;
				new_arg = false;
			} else if (str[i] == ' ' || str[i] == ',')
			{
				str[i] = '\0';
				new_arg = true;
			}
		}

		try
		{
			if (strcmp (argv[0], "load") == 0)
			{
				if (argc != 2)
				{
					throw exception { "Unknown command", argv[0] };
				}
				DB.load (argv[1]);
			} 
			else if (strcmp (argv[0], "save") == 0)
			{
				if (argc != 2)
				{
					throw exception { "Unknown command" };
				}
				DB.save (argv[1]);
			} 
			else if (strcmp (argv[0], "add") == 0)
			{
				if (argc != 10)
				{
					throw exception { "Unknown command" };
				}
				Trip tr (argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], atoi (argv[8]), atof (argv[9]));
				tr.getDT_out ().checkDT ();
				tr.getDT_in ().checkDT ();
				if (tr.getDT_in () < tr.getDT_out ())
				{
					throw exception { "Wrong arrival time" };
				}
				DB.push_back (tr);
			} 
			else if (strcmp (argv[0], "delete") == 0)
			{
				if (argc != 2)
				{
					throw exception { "Unknown command" };
				}
				DB.erase (atoi (argv[1]));
			} 
			else if (strcmp (argv[0], "clear") == 0)
			{
				if (argc != 1)
				{
					throw exception { "Unknown command" };
				}
				DB.clear_zero ();
			} 
			else if (strcmp (argv[0], "print") == 0)
			{
				if (argc != 1)
				{
					throw exception { "Unknown command" };
				}
				DB.print_withID ();
			} 
			else if (strcmp (argv[0], "schedule") == 0)
			{
				if (argc != 3)
				{
					throw exception { "Unknown command" };
				}
				DB.schedule (argv[1], argv[2]);
			} 
			else if (strcmp (argv[0], "from") == 0)
			{
				if (argc != 6)
				{
					throw exception { "Unknown command" };
				}
				DB.from_to_on (argv[1], argv[3], argv[5]);
			} 
			else if (strcmp (argv[0], "find") == 0)
			{
				if (argc != 4)
				{
					throw exception { "Unknown command" };
				}
				DB.find_to (argv[1], argv[3]);
			} 
			else if (strcmp (argv[0], "buy") == 0)
			{
				if (argc != 3)
				{
					throw exception { "Unknown command" };
				}
				DB.buy (argv[1], argv[2]);
			} 
			else if (strcmp (argv[0], "export") == 0)
			{
				if (argc != 2)
				{
					throw exception { "Unknown command" };
				}
				DB.export_to (argv[1]);
			} 
			else if (strcmp (argv[0], "quit") == 0)
			{
				if (argc != 1)
				{
					throw exception { "Unknown command" };
				}
				action = false;
			} 
			else
			{
				throw exception { "Unknown command", argv[0] };
			}
		} catch (const exception& error)
		{
			std::cout << error << std::endl;
		} catch (...)
		{
		}

		delete[] argv;
	}

	return 0;
}