#include "rubik.hpp"

HeuristicTree::HeuristicTree()
{
	this->base = NULL;
}

static void	recursive_delete(Hnode *base)
{
	if (base == NULL)
		return ;
	Hnode *right = base->right;
	Hnode *left = base->left;

	recursive_delete(right);
	recursive_delete(left);
}

HeuristicTree::~HeuristicTree()
{
	recursive_delete(this->base);	
}

int		HeuristicTree::compare(Hnode *c1, Hnode *c2)
{
	return (c1->cube[0] + c1->cube[1] + c1->cube[2] + c1->cube[3] + c1->cube[4] + c1->cube[5]
			- (c2->cube[0] + c2->cube[1] + c2->cube[2] + c2->cube[3] + c2->cube[4] + c2->cube[5]));
}

void	HeuristicTree::rightTreeRot(Hnode *parent)
{
	Hnode	*son = parent->right;
	Hnode	*grandson = son->left;
	son->left = parent;
	parent->right = grandson;
	if (grandson != NULL)
		grandson->parent = son;
	son->parent = parent->parent;
	parent->parent = son;
}

void	HeuristicTree::leftTreeRot(Hnode *parent)
{
	Hnode	*son = parent->left;
	Hnode	*grandson = son->right;
	son->right = parent;
	parent->left = grandson;
	if (grandson != NULL)
		grandson->parent = son;
	son->parent = parent->parent;
	parent->parent = son;
}

void	HeuristicTree::adjustTree(Hnode *node, Hnode *child)
{
	if (node->parent->right == node)
	{
		if (node->right == child) // RR
		{
			this->leftTreeRot(node->parent);
			node->color = TBLACK;
			node->right->color = TBLACK;
		}	
		else // RL
		{
			this->rightTreeRot(node);
			this->leftTreeRot(node->parent);
			node->color = TBLACK;
			node->right->color = TBLACK;
		}
	}
	else
	{
		if (node->right == child) // LR
		{
			this->leftTreeRot(node);
			this->rightTreeRot(node->parent);
			node->color = TBLACK;
			node->right->color = TBLACK;
		}	
		else // LL
		{
			this->rightTreeRot(node->parent);
			node->color = TBLACK;
			node->right->color = TBLACK;
		}
	}
}

bool	HeuristicTree::checkAndAdjustColor(Hnode *node)
{
	if (node->parent->right == node
			&& node->parent->left->color == TRED)
	{
		node->color = TBLACK;
		node->parent->left->color = TBLACK;
		return (true);
	}
	if (node->parent->left == node
			&& node->parent->right->color == TRED)
	{
		node->color = TBLACK;
		node->parent->right->color = TBLACK;
		return (true);
	}
	return (false);
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
	Hnode *prev;

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

		// adjusting while inserting
		if (prev->color == TRED && current->color == TRED)
		{
			if (this->checkAndAdjustColor(prev))
				continue;
			this->adjustTree(prev, current);
		}
	}
	int comp = this->compare(prev, newnode);
	if (comp == 0)
		return false;
	else if (comp > 0)
		prev->right = newnode;
	else
		prev->left = newnode;
	newnode->parent = prev;

	return true;
}

/*
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
*/

