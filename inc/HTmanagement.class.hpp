#ifndef HTMANAGEMENT_HPP
# define HTMANAGEMENT_HPP

#include "rubik.hpp"

typedef struct compactcorner ccorners;
struct compactcorner
{
	int		data;
	int		value;
};

class HTmanagement
{
	private:
		//char	table[90000000]; // index is 1112 2233 3444 5556 6677 7888

	public:

		bool	insert(int *cube);
		void	*writeTree();
		void	*readTree();
		int		searchData(void *data, int *cube);

		HTmanagement();
		~HTmanagement();

};

#endif
