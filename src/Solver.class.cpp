#include "rubik.hpp"

GraphSolver::GraphSolver()
{
	this->open_list = {};
	this->closed_list = {};
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
	for (int i = 0; i < 8 * 4; ++i)
	{
		sum += (v & 1);
		v = v >> 1;
	}
		+ cube[5] ^ 0x55555555;

	return sum;
}

int		GraphSolver::manhattanHeuristic(int *cube)
{
	return (0);
}

bool		GraphSolver::check_admissible_cube(int *cube, single_rot *current)
{	
	//if (
	// BINARY TREE FOR CLOSED LIST
	return true;
}

single_rot	*GraphSolver::solve(int *cube, Rotate r)
{
	BitCube creator;
	single_rot		*current = new (single_rot){cube,
		this->simpleHeuristic(cube), "ORIGINAL", NULL};

	this->open_list.push(current);

	int states = 0;

	while (this->check_solved(current->cube) != true)
	//for (int j = 0; j < 5; ++j)
	{
		current = this->open_list.top();
		this->open_list.pop();
		string *poss_rots = r.get_poss_rot();
		
		for (int i = 0; i < r.get_poss_it() - 1; ++i)
			// -1 because the last entry doesn't work
		{
			int *newcube = r.ApplyRotation(poss_rots[i], current->cube);
			if (this->closed_list.search(newcube) == NULL)
			{
				printf("-----------------------------------\n");
				printf("-----------IT WORKED---------------\n");
				printf("-----------------------------------\n");
				continue;
			}
			this->open_list.push(new (single_rot)
				{newcube, this->simpleHeuristic(newcube), poss_rots[i], current});
		}

		this->closed_list.insert(current->cube);
		states++;
		//printf("current's value = %d\n", current->value);
		//creator.print_cube(current->cube);
		//getchar();
	}

	printQueue(this->open_list);
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
