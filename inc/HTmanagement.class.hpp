#ifndef HTMANAGEMENT_HPP
# define HTMANAGEMENT_HPP

#include "rubik.hpp"

# define TABLESIZE 95000000
//# define TABLESIZE 100000

# define ELEMSIZE 40
# define VALUESIZE 5
# define NEXTSIZE (64 - ELEMSIZE - VALUESIZE)

# define ELEMSHIFT (VALUESIZE + NEXTSIZE)
# define VALUESHIFT (NEXTSIZE)


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
		int		elementsexplored;

		uint64_t	elemmask;
		uint64_t	valuemask;
		uint64_t	nextmask;

		uint64_t	*table; // index is 1111 1222 2233 ... 8888 VVVV VVNN NNNN NNNN NNNN
		// first 40 bits are for the data, the next 4 are for the value,
		// and the last 20 are for the pointer to the next one in case of copies
		std::priority_queue<hash_elem*, std::vector<hash_elem*>, HTCustomCompare> to_visit;

		bool	addTable(uint64_t elem, int value); // true if added, false if it's a copy
		int		hash(uint64_t corners);

		void	print_table();

	public:

		bool	insert(int *cube);
		void	*writeTree(Rotate r);
		uint64_t	*getData();
		int		searchData(uint64_t *data, uint64_t	corners);

		HTmanagement();
		~HTmanagement();

};

#endif
