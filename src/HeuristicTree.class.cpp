#include "rubik.hpp"

HeuristicTree::HeuristicTree()
{
	this->maxdepth = 0;
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
		grandson->parent = parent;
	son->parent = parent->parent;
	parent->parent = son;
	if (son->parent != NULL)
	{
		if (son->parent->left == parent)
			son->parent->left = son;
		else
			son->parent->right = son;
	}
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
	if (son->parent != NULL)
	{
		if (son->parent->left == parent)
			son->parent->left = son;
		else
			son->parent->right = son;
	}
}

static void	swapcolor(Hnode *a, Hnode *b)
{
	bool tmp;

	tmp = b->color;
	b->color = a->color;
	a->color = tmp;
}

void	HeuristicTree::adjustTree(Hnode *node, Hnode *child)
{
	if (node->parent->right == node)
	{
		if (node->right == child) // RR
		{
			this->leftTreeRot(node->parent);
			swapcolor(node, node->left);
		}	
		else // RL
		{
			this->rightTreeRot(node);
			this->leftTreeRot(node->parent->parent);
			swapcolor(node->parent, node->parent->left);
		}
	}
	else
	{
		if (node->right == child) // LR
		{
			this->leftTreeRot(node);
			this->rightTreeRot(node->parent->parent);
			swapcolor(node->parent, node->parent->right);
		}	
		else // LL
		{
			this->rightTreeRot(node->parent);
			swapcolor(node, node->right);
		}
	}
}

bool	HeuristicTree::checkAndAdjustColor(Hnode *node)
{
	if (node->parent->right == node
			&& node->parent->left != NULL	
			&& node->parent->left->color == TRED)
	{
		node->color = TBLACK;
		node->parent->left->color = TBLACK;
		while (this->base->parent != NULL)
			this->base = this->base->parent;
		if (node->parent != this->base)
			node->parent->color = TRED;

		if (node->parent->parent != NULL
				&& node->parent->parent->color == TRED
				&& !this->checkAndAdjustColor(node->parent->parent))
			this->adjustTree(node->parent->parent, node->parent);
		return (true);
	}

	else if (node->parent->left == node
			&& node->parent->right != NULL	
			&& node->parent->right->color == TRED)
	{
		node->color = TBLACK;
		node->parent->right->color = TBLACK;
		while (this->base->parent != NULL)
			this->base = this->base->parent;
		if (node->parent != this->base)
			node->parent->color = TRED;

		if (node->parent->parent != NULL
				&& node->parent->parent->color == TRED
				&& !this->checkAndAdjustColor(node->parent->parent))
			this->adjustTree(node->parent->parent, node->parent);
		return (true);
	}
	return (false);
}

bool	HeuristicTree::insert(int *cube, int moves)
{
	int depth = 0;
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
		depth++;
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
			if (!this->checkAndAdjustColor(prev))
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
		if (!this->checkAndAdjustColor(prev))
			// if the uncle is red adjust it but if not
			// call the big complicated function (TM)
			this->adjustTree(prev, newnode);
	}
	if (depth > this->maxdepth)
	{
		dprintf(2, "new maxdepth is %d\n", depth);
		this->maxdepth = depth;
	}
	while (this->base->parent != NULL)
		base = base->parent;

	return true;
}

static void rec_print(Hnode *node, int count, int spacing, int depth)
{
	if (node == NULL)
		return ;	

	string color = (node->color == TRED) ? CRED : CBLUE;
	dprintf(2, "%s%c[%02d](%02d)%s", color.c_str(),
			(node->color == TRED) ? 'R' : 'B', node->moves, depth, CWHITE);
	if (node->right != NULL)
		dprintf(2, "-->");
	rec_print(node->right, count + 1, spacing, depth + 1);

	dprintf(2, "\n");
	for (int i = 0; i <= count; ++i)
	{
		if (node->left != NULL && i == count)
			dprintf(2, "   '->      ");
		else
			dprintf(2, "            ");
	}
	rec_print(node->left, count + 1, spacing, depth + 1);
}

void	HeuristicTree::print_tree()
{
	dprintf(2, "................\n");
	rec_print(this->base, 0, 12, 0);
	dprintf(2, "\n````````````````\n");
}

Hnode	*HeuristicTree::search(int *cube)
{

	Hnode newnode = Hnode(cube, -1, NULL, NULL, NULL, TRED);
	Hnode *current = this->base;
	Hnode *prev;

	while (current != NULL)
	{
		prev = current;
		int comp = this->compare(current, &newnode);
		if (comp == 0)
			return current;
		else if (comp > 0)
			current = current->right;
		else
			current = current->left;
	}
	return NULL;
}

