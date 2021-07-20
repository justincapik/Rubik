#include "rubik.hpp"

GraphSolver::GraphSolver()
{
	/*
	this->open_list = {};
	this->closed_list = {};
	*/
}

template<class T>
void printQueue(T& q)
{
	BitCube creator;

	cout << "-----------------PRINTING QUEUE---------------" << endl;

	int size = 0;
	
	while (!q.empty())
	{
		cout << q.top()->rot << " (" << q.top()->value << ")" << endl;
		creator.print_cube(q.top()->cube);
		q.pop();
		size++;
	}

	cout << " size is " << size << endl;
	cout << "--------------END PRINTING QUEUE--------------" << endl;
}


GraphSolver::~GraphSolver()
{
	/*
	   single_rot *rot; //TODO
	   while ((rot = this->open_list.top()) != NULL)
	   {
	   delete rot;
	   this->open_list.pop();
	   }
	 */
}


bool		GraphSolver::check_solved(int *cube)
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

int		GraphSolver::simpleHeuristic(int *cube)
{
	int sum = 0;

	int v = cube[0] ^ 0x00000000;
	for (int i = 0; i < 8 * 4; ++i)
	{
		sum += (v & 1);
		v = v >> 1;
	}
	v = cube[1] ^ 0x11111111;
	for (int i = 0; i < 8 * 4; ++i)
	{
		sum += (v & 1);
		v = v >> 1;
	}
	v = cube[2] ^ 0x22222222;
	for (int i = 0; i < 8 * 4; ++i)
	{
		sum += (v & 1);
		v = v >> 1;
	}
	v = cube[3] ^ 0x33333333;
	for (int i = 0; i < 8 * 4; ++i)
	{
		sum += (v & 1);
		v = v >> 1;
	}
	v = cube[4] ^ 0x44444444;
	for (int i = 0; i < 8 * 4; ++i)
	{
		sum += (v & 1);
		v = v >> 1;
	}
	v = cube[5] ^ 0x55555555;
	for (int i = 0; i < 8 * 4; ++i)
	{
		sum += (v & 1);
		v = v >> 1;
	}

	return sum;
}

static int poopcolordistance(int a, int b)
{
	if ((0x0000000f & a) == (0x0000000f & b))
		return (0);
	if (((0x0000000f & a) == RED && (0x00000000f & b) == ORANGE)
			|| ((0x0000000f & a) == ORANGE && (0x00000000f & b) == RED)
			|| ((0x0000000f & a) == BLUE && (0x00000000f & b) == GREEN)
			|| ((0x0000000f & a) == GREEN && (0x00000000f & b) == BLUE)
			|| ((0x0000000f & a) == YELLOW && (0x00000000f & b) == WHITE)
			|| ((0x0000000f & a) == WHITE && (0x00000000f & b) == YELLOW))
		return (2);
	else
		return (1);
}

int		GraphSolver::poopManhattanHeuristic(int *cube)
{
	int sum = 0;
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 8; ++j)
			sum += poopcolordistance(cube[i] >> j, i);
	}
	return (sum);
}



int		GraphSolver::halfManhattanHeuristic(int *cube)
{
	return (0);
}

int		GraphSolver::manhattanHeuristic(int *cube)
{
	BlockBitCube	b;
	block_bits		*bcube = b.bitToBlockCube(cube);

	//printf("----\n");
	int value = b.manhattanHeuristic(bcube);
	
	BitCube			creator;
	//printf("value => %d\n", value);
	//creator.print_cube(cube);
	//printf("----\n");

	delete bcube;

	return (value);
}

bool		GraphSolver::check_admissible_cube(int *cube, single_rot *current)
{	
	if (this->closed_list.search(cube) == NULL)
		return false;
	return true;
}

single_rot	*GraphSolver::solve(int *cube, Rotate r)
{
	BitCube			creator;
	single_rot		*current = new single_rot(cube, this->poopManhattanHeuristic(cube), "ORIGINAL", NULL);

	this->open_list.push(current);

	int states = 0;

	for (int i = 0; i < 3; ++i)
	//while (this->check_solved(current->cube) != true)
	{
		current = this->open_list.top();
		this->open_list.pop();
		string *poss_rots = r.get_poss_rot();
		
		for (int i = 0; i < r.get_poss_it() - 1; ++i)
			// -1 because the last entry doesn't work
		{
			int			*newcube = r.ApplyRotation(poss_rots[i], current->cube);
			if (check_admissible_cube(newcube, current))
			{
				single_rot	*newrot = new single_rot(newcube,
						this->manhattanHeuristic(newcube), poss_rots[i], current);
				this->open_list.push(newrot);
			}
		}

		this->closed_list.insert(current->cube);
		states++;
		if (states % 10000 == 0)
		{
			printf("current's value = %d - %d\n", current->value, states);
			creator.print_cube(current->cube);
		}
	}

	printQueue(this->open_list);
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
