#include "rubik.hpp"

BinaryTree::BinaryTree()
{
	this->base = NULL;
}

BinaryTree::~BinaryTree() {} //TODO

int	BinaryTree::compare(node *c1, node *c2)
{
	/*
	if (c1->hash == c2->hash)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (c1->cube[i] != c2->cube[i])
			{
				dprintf(2, "----------------------------------------------------------------------\n");
				BitCube creator;
				dprintf(2, "found the same hash but different\n");
				dprintf(2, "c1 hash = %d\n", c1->hash);
				creator.print_cube(c1->cube);
				dprintf(2, "c2 hash = %d\n", c2->hash);
				creator.print_cube(c2->cube);
				dprintf(2, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
				*/
				return (c1->cube[0] + c1->cube[1] + c1->cube[2] + c1->cube[3] + c1->cube[4] + c1->cube[5]
					- (c2->cube[0] + c2->cube[1] + c2->cube[2] + c2->cube[3] + c2->cube[4] + c2->cube[5]));
	/*	
}
		}
		return (0);
	}
	return (c1->hash - c2->hash);
*/
}

size_t	BinaryTree::cubehasher(int *cube)
{
	size_t sum = 0;

	for (int i = 0; i < 6; ++i)
		sum += this->cubehash(cube[0]);
	return sum;
}

bool	BinaryTree::insert(int *cube)
{
	node *newnode = new node(cube, this->cubehasher(cube), NULL, NULL);

	if (this->base == NULL)
	{
		this->base = newnode;
		return (true);
	}

	node *current = this->base;
	node *prev;

	while (current != NULL)
	{
		prev = current;
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

node	*BinaryTree::search(int *cube)
{
	node newnode = node(cube, this->cubehasher(cube), NULL, NULL);
	node *current = this->base;
	node *prev;

	while (current != NULL)
	{
		prev = current;	
		int comp = this->compare(current, &newnode);
		if (comp == 0)
			return NULL;
		else if (comp > 0)
			current = current->right;
		else
			current = current->left;
	}
	return prev;
}
