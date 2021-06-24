#ifndef SOLVER_CLASS_HPP
# define SOLVER_CLASS_HPP

#include "rubik.hpp"
#include "BinaryTree.class.hpp"

struct CustomCompare
{
    int operator()(const single_rot* lhs, const single_rot* rhs)
    {
        return lhs->value > rhs->value;
    }
};

class GraphSolver
{
	private:

	public:
		std::priority_queue<single_rot*, std::vector<single_rot*>,
			CustomCompare> open_list;
		BinaryTree closed_list;
		
		GraphSolver();
		~GraphSolver();

		single_rot	*solve(int *cube, Rotate r);
		bool		check_solved(int *cube);
		bool		check_admissible_cube(int *cube, single_rot *state);
		int		simpleHeuristic(int *cube);
		int		manhattanHeuristic(int *cube);

};



#endif
