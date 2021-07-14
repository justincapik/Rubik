#ifndef HTMANAGEMENT_HPP
# define HTMANAGEMENT_HPP

#include "rubik.hpp"

# define TABLESIZE 120000000 // multiple de 1024

# define ELEMSHIFT 24
# define VALUESHIFT 20



class hash_elem
{
	public:
		int		*cube;
		int		value;

		hash_elem(int *cube, int value)
		{
			this->cube = cube;
			this->value = value;
		}
};

struct HTCustomCompare
{
    int operator()(const hash_elem* lhs, const hash_elem* rhs)
    {
        return lhs->value > rhs->value;
    }
};

class HTmanagement
{
	private:
		int		biggestdistance;
		int		biggestvalue;
		int		elementsadded;
		long	*table; // index is 1111 1222 2233 ... 8888 VVVV VVNN NNNN NNNN NNNN
		// first 40 bits are for the data, the next 4 are for the value,
		// and the last 20 are for the pointer to the next one in case of copies
		bool	addTable(long elem, int value); // true if added, false if it's a copy
		int		hash(long corners);

		std::priority_queue<hash_elem*, std::vector<hash_elem*>, HTCustomCompare> to_visit;

	public:

		bool	insert(int *cube);
		void	*writeTree(Rotate r);
		long	*getData();
		int		searchData(void *data, int *cube);

		HTmanagement();
		~HTmanagement();

};

#endif
