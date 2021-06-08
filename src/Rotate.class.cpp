#include "rubik.hpp"


Rotate::Rotate()
{
	for(int i = 0; i < table_size; ++i)
		this->table[i] = NULL;
}
Rotate::~Rotate(){}

bool    Rotate::AddFunction(string dir, void (*foo)())
{
	int index = 0;

	for (int i = 0; i < dir.size(); ++i)
		index += (int)dir[i];
	if (index == 0)
	{
		std::cerr << "invalide string added to rotate table\n";
		return false;
	}
	if (this->table[index] != NULL)
	{
		dprintf(2, "index %d for %s in Rotate table already taken\n", index, dir.c_str());
		exit(-1);
	}
	this->table[index] = foo;
	return true;
}

bool    Rotate::ApplyRotation(string dir)
{
	int index = 0;

	for (int i = 0; i < dir.size(); ++i)
		index += (int)dir[i];

	if (index == 0 || this->table[index] == NULL)
	{
		std::cerr << "invalide string query to rotate table\n";
		return false;
	}
	this->table[index]();
	return true;
}
