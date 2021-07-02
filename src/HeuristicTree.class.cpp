#include "rubik.hpp"

HeuristicTree::HeuristicTree()
{
	this->base = NULL;
}

static void	recursive_delete(Hnode *base)
{
	if (base == NULL)
		return ;
	Hnode right = base->right;
	Hnode left = base->left;

	recursive_delete(right);
	recursive_delete(left);
}

HeuristicTree::~HeuristicTree()
{
	recurive_delete(this->base);	
}

int		compare(Hnode *c1, Hnode *c2)
{
	return (c1->cube[0] + c1->cube[1] + c1->cube[2] + c1->cube[3] + c1->cube[4] + c1->cube[5]
			- (c2->cube[0] + c2->cube[1] + c2->cube[2] + c2->cube[3] + c2->cube[4] + c2->cube[5]));
}

Hnode	*HeuristicTree::rightTreeRot(Hnode *parent)
{
		Hnode	*son = parent->right;
		Hnode	*grandson = son->left;
		son->left = parent;
		parent->right = grandson;
		if (grandson != NULL)
			grandon->parent = son;
		son->parent = parent->parent;
		parent->parent = son;
		return (son);
}

Hnode	*HeuristicTree::leftTreeRot(Hnode *parent)
{
		Hnode	*son = parent->left;
		Hnode	*grandson = son->right;
		son->right = parent;
		parent->left = grandson;
		if (grandson != NULL)
			grandon->parent = son;
		son->parent = parent->parent;
		parent->parent = son;
		return (son);
}

bool	HeuristicTree::insert(int *cube, int moves)
{
	Hnode *newnode = new Hnode(cube, moves, NULL, NULL, NULL, TRED);

	if (this->base == NULL)
	{
		this->base = newnode;
		this->base->color = TBLACK;
		return (true);
	}

	Hnode *current = this->base;

	while (current != NULL)
	{
		int comp = this->compare(current, newnode);
		if (comp == 0)
			return false;
		else if (comp > 0)
			current = current->right;
		else
			current = current->left;
	}
	int comp = this->compare(prev, newnode);
	if (comp == 0)
		return false;
	else if (comp > 0)
		prev->right = newnode;
	else
		prev->left = newnode;
	return true;
}

int		HeuristicTree::search(int *cube)
{
	Hnode newnode = node(cube, this->cubehasher(cube), NULL, NULL);
	Hnode *current = this->base;
	Hnode *prev;

	while (current != NULL)
	{
		prev = current;
		int comp = this->compare(current, &newnode);
		if (comp == 0)
			return ;
		else if (comp > 0)
			current = current->right;
		else
			current = current->left;
	}
	return prev;
}


