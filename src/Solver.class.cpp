#include "rubik.hpp"

Solver::Solver()
{
	this->open_list = {};
	this->closed_list = {};
}

Solver::~Solver()
{
	for (std::vector<single_rot*>::iterator it = this->closed_list.begin();
		it != this->closed_list.end(); ++it)
	{
		delete *it;
	}
	for (std::vector<single_rot*>::iterator it = this->open_list.begin();
		it != this->open_list.end(); ++it)
	{
		delete *it;
	}
}


bool		Solver::check_solved(int *cube)
{
	if (cube[0] == 0x00000000
		&& cube[1] == 0x11111111
		&& cube[2] == 0x22222222
		&& cube[3] == 0x33333333
		&& cube[4] == 0x44444444
		&& cube[5] == 0x55555555)
		return (true);
	else
		return (false);
}

int		Solver::heuristic(int *cube, string heuristic)
{
	(void)heuristic;

	int h = cube[0] ^ 0x00000000
		+ cube[1] ^ 0x11111111
		+ cube[2] ^ 0x22222222
		+ cube[3] ^ 0x33333333
		+ cube[4] ^ 0x44444444
		+ cube[5] ^ 0x55555555;

	return h;
}

single_rot	*Solver::solve(int *cube, Rotate r)
{
	BitCube creator;
	single_rot		*current = new (single_rot){cube, "ORIGINAL",
		this->heuristic(cube, ""), NULL};

	this->open_list.push_back(current);

	int states = 0;

	while (this->check_solved(current->cube) != true)
	{
		current = this->open_list.front();
		string *poss_rots = r.get_poss_rot();
		for (int i = 0; i < r.get_poss_it() - 1; ++i)
		// -1 because the last entry doesn't work
		{
			int *newcube = r.ApplyRotation(poss_rots[i], current->cube);
			this->open_list.push_back(new (single_rot)
			{newcube, poss_rots[i], this->heuristic(newcube, ""), current});
		}

		this->closed_list.push_back(current);
		this->open_list.erase(open_list.begin());
		states++;
	}


	//creator.print_cube(current->cube);
	printf("SOLUTION\n");
	single_rot *t;
	for (t = current; t->last != NULL; t = t->last)
	{
		printf("%s rotation\n", t->rot.c_str());
		creator.print_cube(t->cube);
	}
	printf("%s rotation\n", t->rot.c_str());
	creator.print_cube(t->cube);
	
	printf("%d states explored\n", states);

	return current;



	
}
