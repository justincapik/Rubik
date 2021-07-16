#include "rubik.hpp"

HTmanagement::HTmanagement()
{
	this->biggestdistance = 0;
	this->biggestvalue = 0;
	this->elementsadded = 0;
	this->elementsexplored = 0;
	this->table = new uint64_t[TABLESIZE];

	this->elemmask = 0xffffffffff;
	this->valuemask = 0;
	for (int i = 0; i < VALUESIZE; ++i)
		this->valuemask = (this->valuemask << 1) | 1;
	this->nextmask = 0;
	for (int i = 0; i < NEXTSIZE; ++i)
		this->nextmask = (this->nextmask << 1) | 1;

	dprintf(2, "elemmask = 0x%llx\n", this->elemmask);
	dprintf(2, "valuemask = 0x%llx\n", this->valuemask);
	dprintf(2, "nextmask = 0x%llx\n", this->nextmask);
}

HTmanagement::~HTmanagement() {}

int				HTmanagement::hash(uint64_t corners)
{
	return (corners % TABLESIZE);
}

void			HTmanagement::print_table()
{
	uint64_t	*t = this->table;
	for (int i = 0; i < TABLESIZE; ++i)
	{
		cout << bitset<ELEMSIZE>(t[i] >> ELEMSHIFT) << " ";
		cout << bitset<VALUESIZE>((t[i] >> VALUESHIFT) & this->valuemask) << " ";
		cout << bitset<NEXTSIZE>(t[i] & this->nextmask) << "\n";
	}
	cout << "\n";
}

bool			HTmanagement::addTable(uint64_t elem, int value)
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
	if (value >= pow(2.0, VALUESIZE))
	{
		dprintf(2, "v bad, the value is bigger than %f (%d/%d)\n",
				pow(2.0, VALUESIZE), this->elementsadded, this->elementsexplored);
		//this->print_table();
		exit(-1);
	}
	if (this->table[hash] == 0)
	{
		this->table[hash] = (elem << ELEMSHIFT) | (value << VALUESHIFT);
		return (true);
	}
	else // if there's a hash double
	{
		if (((this->table[hash] >> ELEMSHIFT) & this->elemmask) == elem
				&& ((this->table[hash] >> VALUESHIFT) & this->valuemask) <= value) // in case it the same but worst
			return (false);
		if (((this->table[hash] >> ELEMSHIFT) & this->elemmask) == elem
				&& ((this->table[hash] >> VALUESHIFT) & this->valuemask) > value) // check if this one is better
		{
			this->table[hash] = (elem << ELEMSHIFT) | (value << VALUESHIFT)
				| (this->table[hash] & this->nextmask);
			return (true);
		}
		else
		{
			while ((this->table[hash] & this->nextmask) != 0) // go through the chain until the last one
			{
				hash = (hash + (this->table[hash] & this->nextmask)) % TABLESIZE;
				if (((this->table[hash] >> ELEMSHIFT) & this->elemmask) == elem
						&& ((this->table[hash] >> VALUESHIFT) & this->valuemask) >= value)
					// in case it the same but worst
					return (false);
				if (((this->table[hash] >> ELEMSHIFT) & this->elemmask) == elem
						&& ((this->table[hash] >> VALUESHIFT) & this->valuemask) > value)
					// check if this one is better
				{
					this->table[hash] = (elem << ELEMSHIFT) | (value << VALUESHIFT)
						| (this->table[hash] & this->nextmask);
					return (true);
				}
			}

			/*
			cout << "new element => " << bitset<ELEMSIZE>(elem) << " " << bitset<VALUESIZE>(value) << "\n";
			cout << "otr element => " << bitset<ELEMSIZE>(this->table[hash] >> ELEMSHIFT) << " ";
			cout << bitset<VALUESIZE>((this->table[hash] >> VALUESHIFT) & this->valuemask) << " ";
			cout << bitset<NEXTSIZE>(this->table[hash] & this->nextmask) << "\n\n";
			*/

			if (((this->table[hash] >> ELEMSHIFT) & this->elemmask) == elem
					&& ((this->table[hash] >> VALUESHIFT) & this->valuemask) <= value) // in case it the same but worst
				return (false);
			if (((this->table[hash] >> ELEMSHIFT) & this->elemmask) == elem
					&& ((this->table[hash] >> VALUESHIFT) & this->valuemask) > value) // check if this one is better
			{
				this->table[hash] = (elem << ELEMSHIFT) | (value << VALUESHIFT)
					| (this->table[hash] & this->nextmask);
				return (true);
			}
			//printf("ct pa lmem\n");

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
				dprintf(2, "biggest distance is now %d (%d/%d added)\n",
						i, this->elementsadded, this->elementsexplored);
				this->biggestdistance = i;
			}
			this->table[(hash + i) % TABLESIZE] = (elem << ELEMSHIFT) | (value << VALUESHIFT);
			if (i > pow(2.0, NEXTSIZE))
			{
				dprintf(2, "yo this is bad, they're farther apart than %f in the hash table (%d)\n",
						pow(2.0, NEXTSIZE), this->elementsadded);
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

	string		*poss_rots = r.get_poss_rot();
	int			nb_poss_rots = r.get_poss_it() - 1; // -1 because the last entry doesn't work

	cube = creator.create_cube();
	this->to_visit.push(new hash_elem(cube, 0));

	for (int i = 0; i < TABLESIZE; ++i)
		this->table[i] = 0;

	//for (int i = 0; i < 1000000; ++i)
	while (this->to_visit.empty() != true)
	{
		//this->print_table();
		hash_elem	*current = this->to_visit.top();
		this->to_visit.pop();

		for (int i = 0; i < nb_poss_rots; ++i)
		{
			int			*newcube = r.ApplyRotation(poss_rots[i], current->cube);
			/*
			   printf("new cube added => ");
			   cout << bitset<40>(converter.bitToBlockCorner(newcube)) << "\n";
			   creator.print_cube(newcube);
			   */
			this->elementsexplored++;
			if (addTable(converter.bitToBlockCorner(newcube), current->value + 1) == true)
			{
				this->to_visit.push(new hash_elem(newcube, current->value + 1)); 
				this->elementsadded++;
			}
			else
				delete newcube;
		}
		delete current;
	}
	dprintf(2, "HOLY SHIT\n");

	FILE* pFile;
	pFile = fopen("HeuristicData.bits", "wb");

	fwrite(this->table, 1, TABLESIZE * sizeof(uint64_t), pFile);
	fclose(pFile);	

	return (NULL);
}

uint64_t		*HTmanagement::getData()
{
	ifstream bigFile("HeuristicData.bits");
	char *buffer = new char[TABLESIZE * sizeof(uint64_t)];

	bigFile.read(buffer, TABLESIZE);
	return (reinterpret_cast<uint64_t*>(buffer));
}

int				HTmanagement::searchData(uint64_t *data, uint64_t corners)
{
	int		hash = this->hash(corners);

	if (data[hash] == 0)
		return (-1);
	while (((data[hash] >> ELEMSHIFT) & this->elemmask) != corners
			&& (data[hash] & this->nextmask) != 0) // go through the chain until the last one
		hash = (hash + (data[hash] & this->nextmask)) % TABLESIZE;
	return ((data[hash] >> VALUESHIFT) & this->valuemask);
}










