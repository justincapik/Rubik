#include "rubik.hpp"

HTmanagement::HTmanagement()
{
	this->biggestdistance = 0;
	this->biggestvalue = 0;
	this->elementsadded = 0;
	this->table = new long[TABLESIZE];
}

HTmanagement::~HTmanagement() {}

int				HTmanagement::hash(long corners)
{
	return (corners % TABLESIZE);
}

bool			HTmanagement::addTable(long elem, int value)
{
	//dprintf(2, "adding %ld of value %d\n", elem, value);

	// index is 1111 1222 2233 ... 8888 VVVV VVNN NNNN NNNN NNNN
	// first 40 bits are for the data, the next 4 are for the value,
	// and the last 20 are for the pointer to the next one in case of copies
	int		hash = this->hash(elem);

	if (value > this->biggestvalue)
	{
		dprintf(2, "biggest value is now %d\n", value);
		this->biggestvalue = value;
	}
	if (value > 16)
	{
		dprintf(2, "v bad, the value is bigger than 16 (%d)\n", 
				this->elementsadded);
		exit(-1);
	}
	if (this->table[hash] == 0)
	{
		this->table[hash] = (elem << ELEMSHIFT) | (value << VALUESHIFT);
		return (true);
	}
	else // if there's a hash double
	{
		if (this->table[hash] >> ELEMSHIFT == elem
				&& ((this->table[hash] >> VALUESHIFT) & 0xf) >= value) // in case it the same but worst
			return (false);
		if (this->table[hash] >> ELEMSHIFT == elem
				&& ((this->table[hash] >> VALUESHIFT) & 0xf) > value) // check if this one is better
		{
			this->table[hash] = (elem << ELEMSHIFT) | (value << VALUESHIFT) | (this->table[hash] & 0xfffff);
			return (true);
		}
		else
		{
			while ((this->table[hash] & 0xfffff) != 0) // go through them until the last one
			{
				hash = (hash + (this->table[hash] & 0xfffff)) % TABLESIZE;
				if (this->table[hash] >> ELEMSHIFT == elem && ((this->table[hash] >> VALUESHIFT) & 0xf) >= value)
					// in case it the same but worst
					return (false);
				if (this->table[hash] >> ELEMSHIFT == elem && ((this->table[hash] >> VALUESHIFT) & 0xf) > value)
					// check if this one is better
				{
					this->table[hash] = (elem << ELEMSHIFT) | (value << VALUESHIFT) | (this->table[hash] & 0xfffff);
					return (true);
				}
			}
			int i = 1;
			while (this->table[(hash + i) % TABLESIZE] != 0)
			{
				if ((hash + i) % TABLESIZE == hash)
				{
					dprintf(2, "hey not that bad the this->table needs to be bigger (%d)\n",
						this->elementsadded);
					exit(-1);
				}
				++i;
			}
			if (i > this->biggestdistance)
			{
				dprintf(2, "biggest distance is now %d (%d added)\n", i, this->elementsadded);
				this->biggestdistance = i;
			}
			this->table[(hash + i) % TABLESIZE] = (elem << ELEMSHIFT) | (value << VALUESHIFT);
			if (i > 1048576)
			{
				dprintf(2, "yo this is bad, they're too far apart in the hash table (%d)\n",
						this->elementsadded);
				exit(-1);
			}
			this->table[hash] |= i;
			return (true);
		}
	}
}

void			*HTmanagement::writeTree(Rotate r)
{
	BitCube			creator;
	BlockBitCube	converter;
	int				*cube;

	cube = creator.create_cube();
	this->to_visit.push(new hash_elem(cube, 0));

	//for (int i = 0; i < 1000000; ++i)
	while (this->to_visit.empty() != true)
	{
		string		*poss_rots = r.get_poss_rot();
		hash_elem	*current = this->to_visit.top();
		this->to_visit.pop();

		for (int i = 0; i < r.get_poss_it() - 1; ++i)
			// -1 because the last entry doesn't work
		{
			int			*newcube = r.ApplyRotation(poss_rots[i], current->cube);
			if (addTable(converter.bitToBlockCorner(newcube), current->value + 1) == true)
			{
				this->to_visit.push(new hash_elem(newcube, current->value + 1)); 
				this->elementsadded++;
			}
		}
		delete current;
	}
	dprintf(2, "HOLY SHIT\n");

	FILE* pFile;
    pFile = fopen("HeuristicData.txt", "wb");

	fwrite(this->table, 1, TABLESIZE * sizeof(long), pFile);
   	fclose(pFile);	

	return (NULL);
}

long		*getData()
{
	
}
