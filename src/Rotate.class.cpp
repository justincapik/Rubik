#include "rubik.hpp"


Rotate::Rotate()
{
	for (int i = 0; i < table_size; ++i)
		this->table[i] = NULL;
	possible_rot = new string[table_size];
	for (int i = 0; i < table_size; ++i)
		this->possible_rot[i] = "";
	this->poss_it = 0;
}
Rotate::~Rotate()
{
	//delete possible_rot;
}

bool    Rotate::AddFunction(string dir, int *(*foo)(int *))
{
	int index = 0;

	for (int i = 0; i < dir.size(); ++i)
		index += (int)dir[i];
	printf("for %s the index is %d\n", dir.c_str(), index);

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
	this->possible_rot[this->poss_it++] = dir;
	this->table[index] = foo;

	return true;
}

int	*Rotate::ApplyRotation(string dir, int *cube)
{
	int index = 0;

	for (int i = 0; i < dir.size(); ++i)
		index += (int)dir[i];
	if (index == 0 || this->table[index] == NULL)
	{
		std::cerr << "invalide string query to rotate table\n";
		return NULL;
	}
	return this->table[index](cube);
}

int	Rotate::get_poss_it()
{
	return this->poss_it;
}

string	*Rotate::get_poss_rot()
{
	return this->possible_rot;
}
