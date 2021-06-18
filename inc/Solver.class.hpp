#ifndef SOLVER_CLASS_HPP
# define SOLVER_CLASS_HPP

#include "rubik.hpp"

typedef struct single_rot single_rot;
struct single_rot
{
	int		*cube;
	int		value;
	string		rot;
	single_rot	*last;
};

struct CustomCompare
{
    int operator()(const sinlge_rot*& lhs, const single_rot*& rhs)
    {
        return lhs->value < rhs->value;
    }
};

class Solver
{
	private:
		int		compare(single_rot *
		std::priority_queue<single_rot*, std::vector<single_rot*>,
			CustomCompare> open_list;
		std::vector<single_rot*> closed_list;

	public:
		Solver();
		~Solver();

		single_rot	*solve(int *cube, Rotate r);
		bool		check_solved(int *cube);
		int		heuristic(int *cube, string heuristic);

};



#endif
