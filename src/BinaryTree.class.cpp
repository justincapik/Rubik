#include "rubik.hpp"

BinaryTree::BinaryTree()
{
	this->base = NULL;
}

BinaryTree::~BinaryTree() {} //TODO

int	BinaryTree::compare(node *c1, node *c2)
{
	if (c1->hash == c2->hash)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (c1->cube[i] != c2->cube[i])
				return (c1->cube[i] - c2->cube[i]);
		}
		return (0);
	}
	return (c1->hash - c2->hash);
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
	node *newnode = new (node){cube, this->cubehasher(cube), NULL, NULL};

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
	node newnode = {cube, this->cubehasher(cube), NULL, NULL};
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
