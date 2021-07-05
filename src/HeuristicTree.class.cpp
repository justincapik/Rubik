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
	//return (c1->cube[0] + c1->cube[1] + c1->cube[2] + c1->cube[3] + c1->cube[4] + c1->cube[5]
	//		- (c2->cube[0] + c2->cube[1] + c2->cube[2] + c2->cube[3] + c2->cube[4] + c2->cube[5]));
	return (c2->moves - c1->moves);
}

void	HeuristicTree::leftTreeRot(Hnode *parent)
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

void	HeuristicTree::rightTreeRot(Hnode *parent)
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
			dprintf(2, "RR\n");
			this->leftTreeRot(node->parent);
			node->color = TBLACK;
			node->left->color = TRED;
			dprintf(2, "RR out\n");
		}	
		else // RL
		{
			dprintf(2, "RL\n");
			write(2, "1\n", 2);
			this->rightTreeRot(node);
			write(2, "2\n", 2);
			this->leftTreeRot(node->parent);
			write(2, "3\n", 2);
			node->color = TBLACK;
			write(2, "4\n", 2);
			node->left->color = TRED;
			write(2, "5\n", 2);
			dprintf(2, "RL out\n");
		}
	}
	else
	{
		if (node->right == child) // LR
		{
			dprintf(2, "LR\n");
			this->leftTreeRot(node);
			this->rightTreeRot(node->parent);
			node->color = TBLACK;
			node->right->color = TRED;
			dprintf(2, "LR out\n");
		}	
		else // LL
		{
			dprintf(2, "LL\n");
			this->rightTreeRot(node->parent);
			node->color = TBLACK;
			node->right->color = TRED;
			dprintf(2, "LL out\n");
		}
	}
}

bool	HeuristicTree::checkAndAdjustColor(Hnode *node)
{
	dprintf(2, "we're in uncle (not tm)\n");
	if (node->parent->right == node
			&& node->parent->left != NULL	
			&& node->parent->left->color == TRED)
	{
		dprintf(2, "numba wan\n");
		node->color = TBLACK;
		node->parent->left->color = TBLACK;
		return (true);
	}

	if (node->parent->left == node
			&& node->parent->right != NULL	
			&& node->parent->right->color == TRED)
	{
		dprintf(2, "numba twu\n");
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
		if (current != NULL && prev->color == TRED && current->color == TRED)
		{
			dprintf(2, "WE'RE IN IT BOYS (1)\n");
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

	if (prev->color == TRED && newnode->color == TRED)
	{
		dprintf(2, "WE'RE IN IT BOYS (2)\n");
		if (!this->checkAndAdjustColor(prev))
			// if the uncle is red adjust it but if not
			// call the big complicated function (TM)
			this->adjustTree(prev, newnode);
	}

	while (this->base->parent != NULL)
		base = base->parent;

	return true;
}

static void rec_print(Hnode *node, int count, int spacing, int depth)
{
	if (node == NULL)
		return ;	

	dprintf(2, "%c[%02d](%02d)", (node->color == TRED) ? 'R' : 'B', node->moves, depth);
	//for (int i = 0; i < spacing - 9; ++i)
	//	dprintf(2, " ");
	if (node->right != NULL)
		dprintf(2, "-->");
	rec_print(node->right, count + 1, spacing, depth + 1);

	dprintf(2, "\n");
	//for (int i = 0; i < count; ++i)
	//	dprintf(2, " ");
	for (int i = 0; i < count; ++i)
	{
		if (node->left != NULL)
			dprintf(2, "   '->      ");
		else
			dprintf(2, "            ");
	}
	//dprintf(2, "%c(%d)", (node->color == TRED) ? 'R' : 'B', node->moves);
	rec_print(node->left, count + 1, spacing, depth + 1);
}

void	HeuristicTree::print_tree()
{
	dprintf(2, "................\n");
	rec_print(this->base, 0, 12, 0);
	dprintf(2, "\n````````````````\n");
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

